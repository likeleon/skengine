#include "Pch.h"
#include "SkVertexBuffer.h"
#include "SkLog.h"
#include "SkUtilities.h"
#include "SkD3D9Device.h"

namespace ske
{
	VertexBuffer::VertexBuffer()
	: m_vertexBuff(nullptr), m_size(0)
	{
	}

	VertexBuffer::~VertexBuffer()
	{
		Destroy();
	}

	bool VertexBuffer::Create(D3D9Device& device, const void* src, size_t srcSize)
	{
		if (!src || srcSize == 0)
			return false;

		if (IsCreated())
			return false;

		if (!device.CreateVertexBuffer(srcSize, &m_vertexBuff))
			return false;

		void* pVertices = nullptr;
		const HRESULT hr = m_vertexBuff->Lock(0, srcSize, (void **)&pVertices, 0);
		if (FAILED(hr))
		{
			Log::Error(L"LPDIRECT3DVERTEXBUFFER9::lock failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			Destroy();
			return false;
		}
		memcpy_s(pVertices, srcSize, src, srcSize);
		m_vertexBuff->Unlock();
		m_size = srcSize;

		SK_ENSURE(IsCreated());
		return true;
	}

	void VertexBuffer::Destroy()
	{
		ske::SafeRelease(m_vertexBuff);
		m_size = 0;
		SK_ENSURE(!IsCreated());
	}

	bool VertexBuffer::IsCreated() const
	{
		return (m_vertexBuff != nullptr);
	}
}