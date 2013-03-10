#include "Pch.h"
#include "SkD3D9Device.h"
#include "SkLog.h"
#include "SkUtilities.h"
#include "SkShaderBase.h"
#include "SkStringUtil.h"

namespace ske
{
	D3D9Device::D3D9Device()
	: m_d3d(nullptr), m_d3dDevice(nullptr), m_beginScene(false)
	{
	}

	D3D9Device::~D3D9Device()
	{
		Destroy();
	}

	bool D3D9Device::Create(HWND hWnd)
	{
		if (!hWnd)
			return false;

		if (IsCreated())
			return false;

		m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!m_d3d)
		{
			Log::Error(L"%s Direct3DCreate9 failed", __FUNCTIONW__);
			goto LOCAL_EXIT_FAIL;
		}

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_d3dDevice)))
		{
			Log::Error(L"%s CreateDevice failed", __FUNCTIONW__);
			goto LOCAL_EXIT_FAIL;
		}

		SK_ENSURE(IsCreated());
		return true;

LOCAL_EXIT_FAIL:
		Destroy();
		return false;
	}

	void D3D9Device::Destroy()
	{
		m_beginScene = false;
		SafeRelease(m_d3dDevice);
		SafeRelease(m_d3d);
		SK_ENSURE(!IsCreated());
	}

	bool D3D9Device::IsCreated() const
	{
		return (m_d3dDevice != nullptr);
	}

	bool D3D9Device::Clear()
	{
		return SUCCEEDED(m_d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));
	}

	bool D3D9Device::BeginScene()
	{
		if (m_beginScene)
			return false;

		const HRESULT hr = m_d3dDevice->BeginScene();
		if (FAILED(hr))
		{
			Log::Error(L"BeginScene failed with, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		
		m_beginScene = true;
		return true;
	}

	bool D3D9Device::EndScene()
	{
		if (!m_beginScene)
			return false;
		
		const HRESULT hr = m_d3dDevice->EndScene();
		if (FAILED(hr))
		{
			Log::Error(L"EndScene failed with, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		m_beginScene = false;
		return true;
	}

	bool D3D9Device::Present()
	{
		if (m_beginScene)
			return false;
		
		const HRESULT hr = m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
		if (FAILED(hr))
		{
			Log::Error(L"Present failed with, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::CreateEffectFromFile(const std::wstring& srcFile,
							 		  LPD3DXEFFECT *ppEffect)
	{
		if (!IsCreated())
			return false;

		LPD3DXBUFFER compileErr = nullptr;
		const HRESULT hr = D3DXCreateEffectFromFile(m_d3dDevice,
			srcFile.c_str(), nullptr, nullptr, D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
			nullptr, ppEffect, &compileErr);
		if (FAILED(hr))
		{
			Log::Error(L"D3DXCreateEffectFromFile failed, hr=%s, desc=%s (detailed:%s)", 
				DXGetErrorString(hr), DXGetErrorDescription(hr), 
				compileErr? StringUtil::ToWide((LPCSTR)compileErr->GetBufferPointer()).c_str():L"");
			SafeRelease(compileErr);
			return false;
		}

		return true;
	}

	bool D3D9Device::CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements,
									 IDirect3DVertexDeclaration9 **ppDecl)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_d3dDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
		if (FAILED(hr))
		{
			Log::Error(L"CreateVertexDeclaration failed, hr=%d desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::CreateVertexBuffer(unsigned int length, 
									IDirect3DVertexBuffer9 **ppVertexBuffer)
	{
		if (!IsCreated())
			return false;
		const HRESULT hr = m_d3dDevice->CreateVertexBuffer(length, 0, 0, D3DPOOL_DEFAULT, ppVertexBuffer, nullptr);
		if (FAILED(hr))
		{
			Log::Error(L"CreateVertexBuffer failed with length=%u, hr=%s, desc=%s", 
				length, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::CreateIndexBuffer(unsigned int length, IDirect3DIndexBuffer9 **ppIndexBuffer)
	{
		if (!IsCreated())
			return false;
		const HRESULT hr = m_d3dDevice->CreateIndexBuffer(length, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED,
			ppIndexBuffer, nullptr);
		if (FAILED(hr))
		{
			Log::Error(L"CreateIndexBuffer failed with length=%u, hr=%s, desc=%s",
				length, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::CreateFont(int height, 
							const std::wstring& faceName, 
							LPD3DXFONT *ppFont)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = D3DXCreateFont(m_d3dDevice, height, 0, FW_BOLD, 1, FALSE, 
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
							    DEFAULT_PITCH | FF_DONTCARE, faceName.c_str(), ppFont);
		if (FAILED(hr))
		{
			Log::Error(L"%s D3DXCreateFont failed with height=%d faceName=%s, hr=%s, desc=%s",
				height, faceName.c_str(), DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl)
	{
		if (!IsCreated())
			return false;
		
		const HRESULT hr = m_d3dDevice->SetVertexDeclaration(pDecl);
		if (FAILED(hr))
		{
			Log::Error(L"SetVertexDeclaration failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::SetStreamSource(IDirect3DVertexBuffer9 *pStreamData, unsigned int stride)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_d3dDevice->SetStreamSource(0, pStreamData, 0, stride);
		if (FAILED(hr))
		{
			Log::Error(L"SetStreamSource failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::SetIndices(IDirect3DIndexBuffer9* pIndexData)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_d3dDevice->SetIndices(pIndexData);
		if (FAILED(hr))
		{
			Log::Error(L"SetIndices failed with index=0x%x, hr=%s, desc=%s", 
				pIndexData, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int primitiveCount)
	{
		if (!IsCreated())
			return false;
		
		const HRESULT hr = m_d3dDevice->DrawPrimitive(PrimitiveType, 0, primitiveCount);
		if (FAILED(hr))
		{
			Log::Error(L"DrawPrimitive failed with #primitive=%u, hr=%s, desc=%s", 
				primitiveCount, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int numVertices, 
		unsigned int startIndex, unsigned int primitiveCount)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_d3dDevice->DrawIndexedPrimitive(PrimitiveType, 0, 0, numVertices, startIndex, primitiveCount);
		if (FAILED(hr))
		{
			Log::Error(L"DrawIndexedPrimitive failed with #vertex=%u startIndex=%u #primitive=%u, hr=%s, desc=%s", 
				numVertices, startIndex, primitiveCount, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3D9Device::SetCullMode(D3D9Device::CullMode cullMode)
	{
		if (!IsCreated())
			return false;
		const HRESULT hr = m_d3dDevice->SetRenderState(D3DRS_CULLMODE, cullMode);
		if (FAILED(hr))
		{
			Log::Error(L"SetRenderState D3DRS_CULLMODE failed with mode=%d, hr=%s, desc=%s",
				cullMode, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::SetDepthBufferMode(D3D9Device::DepthBufferMode mode)
	{
		if (!IsCreated())
			return false;
		const HRESULT hr = m_d3dDevice->SetRenderState(D3DRS_ZENABLE, mode);
		if (FAILED(hr))
		{
			Log::Error(L"SetRenderState D3DRS_ZENABLE failed with mode=%d, hr=%s, desc=%s",
				mode, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::CreateTextureFromFile(const std::wstring& srcFile, LPDIRECT3DTEXTURE9 *ppTexture)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = D3DXCreateTextureFromFile(m_d3dDevice, srcFile.c_str(), ppTexture);
		if (FAILED(hr))
		{
			Log::Error(L"D3DXCreateTextureFromFile with file=%d, hr=%s, desc=%s",
				srcFile.c_str(), DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3D9Device::LoadMeshFromX(const std::wstring& fileName, LPD3DXBUFFER *ppMaterials, DWORD *pNumMaterials, LPD3DXMESH *ppMesh)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = D3DXLoadMeshFromX(fileName.c_str(), D3DXMESH_SYSTEMMEM, m_d3dDevice,
			nullptr, ppMaterials, nullptr, pNumMaterials, ppMesh);
		if (FAILED(hr))
		{
			Log::Error(L"D3DXLoadMeshFromX with file=%s, hr=%s, desc=%s",
				fileName.c_str(), DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}
}