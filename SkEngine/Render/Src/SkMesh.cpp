#include "Pch.h"
#include <Shlwapi.h>
#include "SkMesh.h"
#include "SkD3D9Device.h"
#include "SkUtilities.h"
#include "SkLambertShader.h"
#include "SkTexture.h"
#include "SkLog.h"
#include "SkStringUtil.h"
#include "SkD3DMapping.h"
#include "SkMeshVertex.h"
#include "SkTextureManager.h"
#include "SkStringUtil.h"

namespace ske
{
	Mesh::Mesh(ShaderBasePtr shader)
	: m_shader(shader), m_texture(nullptr), m_vertexDecl(nullptr), m_device(nullptr), m_isCreated(false)
	{
	}

	Mesh::~Mesh()
	{
		Destroy();
	}

	bool Mesh::CreateFromXFile(D3D9Device& device, TextureManager& textureMgr, const std::wstring& fileName)
	{
		if (fileName.empty())
			return false;

		if (IsCreated())
			return false;

		// Load .x file
		LPD3DXBUFFER materialBuf = nullptr;
		DWORD numMaterial = 0;

		LPD3DXMESH mesh = nullptr;
		if (!device.LoadMeshFromX(fileName, &materialBuf, &numMaterial, &mesh))
			goto LOCAL_EXIT_FAIL;

		// Create texture
		if (numMaterial > 0)
		{
			if (numMaterial > 1) {
				Log::Warning(L"Only the first of %u material will be loaded", numMaterial);
			}

			SK_ENSURE(materialBuf);
			const D3DXMATERIAL* const materials = (D3DXMATERIAL *)(materialBuf->GetBufferPointer());
			const D3DXMATERIAL& material = materials[0];

			if (material.pTextureFilename)
			{
				std::wstring texturePath = fileName;
				const std::wstring textureFilename = StringUtil::ToWide(material.pTextureFilename);
				texturePath.replace(texturePath.find_last_of('/') + 1, textureFilename.length(), textureFilename);

				m_texture = textureMgr.Load(texturePath);
				if (!m_texture)
					goto LOCAL_EXIT_FAIL;
			}
		}

		// Load geometry
		m_vertexDecl = MeshVertex::CreateDeclaration(device);
		if (!m_vertexDecl)
			goto LOCAL_EXIT_FAIL;

		if (!LoadVertices(device, mesh))
			goto LOCAL_EXIT_FAIL;

		if (!LoadIndices(device, mesh))
			goto LOCAL_EXIT_FAIL;

		m_device = &device;
		m_isCreated = true;
		SK_ENSURE(IsCreated());
		return true;

LOCAL_EXIT_FAIL:
		SafeRelease(mesh);
		Destroy();
		return false;
	}

	bool Mesh::LoadVertices(D3D9Device& device, LPD3DXMESH mesh)
	{
		SK_REQUIRE(mesh);

		//const DWORD ourFvfCode = D3DFVF_XYZ | D3DFVF_TEX0 | D3DFVF_NORMAL;
		//if (m_mesh->GetFVF() != ourFvfCode)
		//{
		//	LPD3DXMESH clonedMesh = nullptr;
		//	const HRESULT hr = m_mesh->CloneMeshFVF(D3DXMESH_VB_SYSTEMMEM, ourFvfCode, device.m_d3dDevice, &clonedMesh);
		//	if (FAILED(hr))
		//		return false;

		//	SafeRelease(m_mesh);
		//	m_mesh = clonedMesh;
		//}
		//SK_ASSERT(m_mesh->GetFVF() == ourFvfCode);

		struct DxVertex
		{
			D3DXVECTOR3 position;
			//D3DXVECTOR3 normal;
			D3DXVECTOR2 tex;
		};
		if (sizeof(DxVertex) != mesh->GetNumBytesPerVertex())
		{
			Log::Error(L"Not supported vertex, size=%u differs from our=%u", 
				mesh->GetNumBytesPerVertex(), sizeof(DxVertex));
			return false;
		}
		
		DxVertex* dxVertices = nullptr;
		const HRESULT hr = mesh->LockVertexBuffer(D3DLOCK_READONLY, (void **)&dxVertices);
		if (FAILED(hr))
		{
			Log::Error(L"LPD3DXMESH::LockVertexBuffer failed, hr=%d, desc=%s",
				DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		std::vector<MeshVertex> vertices;
		vertices.reserve(mesh->GetNumVertices());

		for (DWORD i = 0; i < mesh->GetNumVertices(); ++i)
		{
			const DxVertex& dxVertex = dxVertices[i];
			const MeshVertex::Position pos(dxVertex.position.x, dxVertex.position.y, dxVertex.position.z);
			const MeshVertex::UV uv(dxVertex.tex.x, dxVertex.tex.y);
			//const Normal normal(dxVertex.normal.x, dxVertex.normal.y, dxVertex.normal.z);
			const MeshVertex::Normal normal(-Vector3::UnitZ);
			vertices.push_back(MeshVertex(pos, uv, normal));
		}
		mesh->UnlockVertexBuffer();

		return m_vertexBuff.Create(device, &vertices[0], MeshVertex::VertexSize * vertices.size());
	}

	bool Mesh::LoadIndices(D3D9Device& device, LPD3DXMESH mesh)
	{
		SK_REQUIRE(mesh);

		short* dxIndices = nullptr;
		const HRESULT hr = mesh->LockIndexBuffer(D3DLOCK_READONLY, (void **)&dxIndices);
		if (FAILED(hr))
		{
			Log::Error(L"LPD3DXMESH::LockIndexBuffer failed, hr=%d, desc=%s",
				DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		const std::vector<short> indices(dxIndices, dxIndices + mesh->GetNumFaces() * 3);
		mesh->UnlockIndexBuffer();

		return m_indexBuff.Create(device, &indices[0], sizeof(short) * indices.size());
	}

	void Mesh::Destroy()
	{
		m_device = nullptr;
		m_indexBuff.Destroy();
		m_vertexBuff.Destroy();
		m_vertexDecl = nullptr;
		m_texture = nullptr;
		m_shader = nullptr;
		m_isCreated = false;
	}

	bool Mesh::Render()
	{
		if (!IsCreated())
			return false;

		SK_ASSERT(m_device && m_vertexDecl && m_vertexDecl->IsCreated() && m_vertexBuff.IsCreated());

		if (!m_device->SetVertexDeclaration(m_vertexDecl->GetD3DDecl()))
			return false;

		if (!m_device->SetStreamSource(m_vertexBuff.GetVertexBuffer(), MeshVertex::VertexSize))
			return false;

		if (!m_device->SetIndices(m_indexBuff.GetIndexBuffer()))
			return false;

		const unsigned int numVertices = m_vertexBuff.GetSize() / MeshVertex::VertexSize;
		if (!m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, numVertices, 0, m_indexBuff.GetNumIndices() / 3))
			return false;

		return true;
	}

	ShaderBasePtr Mesh::GetShader()
	{
		return m_shader;
	}

	TexturePtr Mesh::GetTexture()
	{
		return m_texture;
	}
		
	const Matrix4& Mesh::GetWorldMatrix()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixRotationY(&matWorld, D3DX_PI / 4.0f);
		D3DMapping::ToMatrix4(matWorld, m_worldMat);
		return m_worldMat;
	}
}