#include "Pch.h"
#include "SkIndexBuffer.h"
#include "SkD3D9Device.h"
#include "SkUtilities.h"
#include "SkLog.h"

namespace ske
{
	IndexBuffer::IndexBuffer()
	: m_indexBuff(nullptr), m_numIndice(0)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		Destroy();
	}

	bool IndexBuffer::Create(D3D9Device& device, const void* src, size_t srcSize)
	{
		if (!src || srcSize <= 0)
			return false;

		if (IsCreated())
			return false;

		if (!device.CreateIndexBuffer(srcSize, &m_indexBuff))
			return false;

		void* pIndices = nullptr;
		const HRESULT hr = m_indexBuff->Lock(0, srcSize, (void **)&pIndices, 0);
		if (FAILED(hr))
		{
			Log::Error(L"LPDIRECT3DINDEXBUFFER9::lock failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			Destroy();
			return false;
		}
		memcpy_s(pIndices, srcSize, src, srcSize);
		m_indexBuff->Unlock();

		m_numIndice = srcSize / sizeof(short);
		SK_ENSURE(IsCreated());
		return true;
	}

	void IndexBuffer::Destroy()
	{
		SafeRelease(m_indexBuff);
		m_numIndice = 0;
		SK_ENSURE(!IsCreated());
	}
}