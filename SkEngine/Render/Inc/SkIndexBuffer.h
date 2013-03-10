#pragma once

#include "SkNonCopyable.h"

namespace ske
{
	class D3D9Device;

	class IndexBuffer : private NonCopyable
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		bool Create(D3D9Device& device, const void* src, size_t srcSize);
		void Destroy();
		bool IsCreated() const { return (m_indexBuff != nullptr); }

		LPDIRECT3DINDEXBUFFER9 GetIndexBuffer() { return m_indexBuff; }
		size_t GetNumIndices() const { return m_numIndice; }

	private:
		LPDIRECT3DINDEXBUFFER9 m_indexBuff;
		size_t m_numIndice;
	};
}