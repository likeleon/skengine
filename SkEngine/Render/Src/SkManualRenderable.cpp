#include "Pch.h"
#include "SkManualRenderable.h"
#include <MMSystem.h>
#include "SkUtilities.h"
#include "SkLog.h"
#include "SkD3DMapping.h"
#include "SkD3D9Device.h"

namespace ske
{
	ManualRenderable::ManualRenderable(ShaderBasePtr shader, TexturePtr texture)
	: m_vertexDecl(nullptr), m_device(nullptr), m_shader(shader), m_texture(texture)
	{
		SK_ASSERT(m_shader->IsCreated());
	}

	ManualRenderable::~ManualRenderable()
	{
		Destroy();
	}

	bool ManualRenderable::AddVertex(const MeshVertex& vertex)
	{
		if (IsCreated())
			return false;

		m_vertices.push_back(vertex);
		return true;
	}

	bool ManualRenderable::AddVertex(const MeshVertex::Position& pos, 
									 const MeshVertex::UV& uv,
									 const MeshVertex::Normal& normal)
	{
		if (IsCreated())
			return false;

		m_vertices.push_back(MeshVertex(pos, uv, normal));
		return true;
	}

	bool ManualRenderable::AddIndex(short i1, short i2, short i3)
	{
		if (IsCreated())
			return false;

		m_indices.push_back(i1);
		m_indices.push_back(i2);
		m_indices.push_back(i3);
		return true;
	}

	bool ManualRenderable::Create(D3D9Device& device)
	{
		if (IsCreated() || m_vertices.empty())
			return false;

		m_vertexDecl = MeshVertex::CreateDeclaration(device);
		if (!m_vertexDecl)
			goto LOCAL_EXIT_FAIL;

		if (!m_vertexBuff.Create(device, &m_vertices[0], VertexSize * m_vertices.size()))
			goto LOCAL_EXIT_FAIL;

		if (!m_indices.empty())
		{
			if (!m_indexBuff.Create(device, &m_indices[0], sizeof(short) * m_indices.size()))
				goto LOCAL_EXIT_FAIL;
		}

		m_vertices.clear();
		m_indices.clear();
		m_device = &device;

		SK_ENSURE(IsCreated());
		return true;

LOCAL_EXIT_FAIL:
		Destroy();
		return false;
	}

	void ManualRenderable::Destroy()
	{
		m_indexBuff.Destroy();
		m_vertexBuff.Destroy();
		m_vertices.clear();
		m_vertexDecl = nullptr;
		m_device = nullptr;
		m_texture = nullptr;
		SK_ENSURE(!IsCreated());
	}

	bool ManualRenderable::IsCreated() const
	{
		return m_vertexBuff.IsCreated();
	}

	bool ManualRenderable::Render()
	{
		if (!IsCreated())
			return false;

		SK_ASSERT(m_device && m_vertexDecl && m_vertexDecl->IsCreated() && m_vertexBuff.IsCreated());

		if (!m_device->SetVertexDeclaration(m_vertexDecl->GetD3DDecl()))
			return false;

		if (!m_device->SetStreamSource(m_vertexBuff.GetVertexBuffer(), VertexSize))
			return false;

		const unsigned int numVertices = m_vertexBuff.GetSize() / VertexSize;
		if (m_indexBuff.IsCreated())
		{
			if (!m_device->SetIndices(m_indexBuff.GetIndexBuffer()))
				return false;

			if (!m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, numVertices, 0, m_indexBuff.GetNumIndices() / 3))
				return false;
		}
		else
		{
			if (!m_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, max(1, numVertices - 2)))
				return false;
		}

		return true;
	}

	const Matrix4& ManualRenderable::GetWorldMatrix()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixRotationX(&matWorld, timeGetTime() / 500.0f);
		D3DMapping::ToMatrix4(matWorld, m_worldMat);
		return m_worldMat;
	}

}