#pragma once

#include "SkNonCopyable.h"
#include <d3d9.h>

namespace ske
{
	class D3D9Device;

	class VertexBuffer : private NonCopyable
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Create(D3D9Device& device, const void* src, size_t srcSize);
		void Destroy();
		bool IsCreated() const;

		LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() { return m_vertexBuff; }
		unsigned int GetSize() const { return m_size; }

	private:
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuff;
		unsigned int m_size;
	};
}