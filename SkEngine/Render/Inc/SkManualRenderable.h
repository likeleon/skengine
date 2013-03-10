#pragma once

#include <vector>
#include "SkNonCopyable.h"
#include "SkVertexBuffer.h"
#include "SkVertexDeclaration.h"
#include "SkIRenderable.h"
#include "SkMatrix4.h"
#include "SkShaderBase.h"
#include "SkIndexBuffer.h"
#include "SkMeshVertex.h"
#include "SkTexture.h"

namespace ske
{
	class ManualRenderable : public IRenderable, private NonCopyable
	{
	public:
		ManualRenderable(ShaderBasePtr shader, TexturePtr texture);
		virtual ~ManualRenderable();

		bool AddVertex(const MeshVertex& vertex);
		bool AddVertex(const MeshVertex::Position& pos, const MeshVertex::UV& uv, const MeshVertex::Normal& normal);
		bool AddIndex(short i1, short i2, short i3);
		bool Create(D3D9Device& device);
		void Destroy();

		static const unsigned int VertexSize = sizeof(MeshVertex);

	private:
		// Implements IRenderable
		virtual bool Render();
		virtual ShaderBasePtr GetShader() { return m_shader; }
		virtual TexturePtr GetTexture() { return m_texture; }
		virtual const Matrix4& GetWorldMatrix();

	private:
		bool IsCreated() const;

		std::vector<MeshVertex> m_vertices;
		VertexBuffer		m_vertexBuff;
		std::vector<short>	m_indices;
		IndexBuffer			m_indexBuff;
		VertexDeclarationPtr	m_vertexDecl;
		D3D9Device*			m_device;
		ShaderBasePtr		m_shader;
		TexturePtr			m_texture;
		Matrix4				m_worldMat;
	};
}