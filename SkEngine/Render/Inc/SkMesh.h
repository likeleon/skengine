#pragma once

#include <string>
#include <d3dx9.h>
#include "SkNonCopyable.h"
#include "SkIRenderable.h"
#include "SkTexture.h"
#include "SkVertexBuffer.h"
#include "SkVertexDeclaration.h"
#include "SkIndexBuffer.h"
#include "SkMatrix4.h"

namespace ske
{
	class D3D9Device;
	class TextureManager;

	class Mesh : public IRenderable, private NonCopyable
	{
	public:
		Mesh(ShaderBasePtr shader);
		virtual ~Mesh();

		bool CreateFromXFile(D3D9Device& device, TextureManager& textureMgr, const std::wstring& fileName);
		bool IsCreated() const { return m_isCreated; }
		void Destroy();

	private:
		// Implements IRenderable
		virtual bool Render();
		virtual ShaderBasePtr GetShader();
		virtual TexturePtr GetTexture();
		virtual const Matrix4& GetWorldMatrix();

		// DirectX .x
		bool LoadVertices(D3D9Device& device, LPD3DXMESH mesh);
		bool LoadIndices(D3D9Device& device, LPD3DXMESH mesh);

		ShaderBasePtr		m_shader;
		TexturePtr			m_texture;
		VertexBuffer		m_vertexBuff;
		VertexDeclarationPtr	m_vertexDecl;
		IndexBuffer			m_indexBuff;
		D3D9Device*			m_device;
		Matrix4				m_worldMat;
		bool				m_isCreated;
	};
}