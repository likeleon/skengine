#include "Pch.h"
#include "SkD3DEffect.h"
#include "SkD3D9Device.h"
#include "SkUtilities.h"
#include "SkLog.h"
#include "SkStringUtil.h"
#include "SkD3DMapping.h"
#include "SkVector4.h"
#include "SkTexture.h"

namespace ske
{
	bool D3DEffect::Create(D3D9Device &device, const std::wstring& effectFile)
	{
		if (IsCreated())
			return false;

		if (effectFile.empty())
			return false;

		if (!device.CreateEffectFromFile(effectFile, &m_effect))
			return false;

		SK_ENSURE(IsCreated());
		return true;
	}

	void D3DEffect::Destroy()
	{
		if (m_techBegun)
		{
			End();
			m_techBegun = false;
		}
		m_params.clear();
		SafeRelease(m_effect);
		SK_ENSURE(!IsCreated());
	}

	bool D3DEffect::IsCreated() const 
	{
		return (m_effect != nullptr);
	}

	bool D3DEffect::SetTechnique(const std::string& techName)
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_effect->SetTechnique(techName.c_str());
		if (FAILED(hr))
		{
			Log::Error(L"SetTechnique with %s failed, hr=%s, desc=%s", 
				techName.c_str(), DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3DEffect::Begin(unsigned int &numPass)
	{
		if (!IsCreated() || m_techBegun)
			return false;

		const HRESULT hr = m_effect->Begin(&numPass, 0);
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::Begin failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		m_techBegun = true;
		return true;
	}

	bool D3DEffect::End()
	{
		if (!IsCreated() || !m_techBegun)
			return false;

		const HRESULT hr = m_effect->End();
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::End failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		m_techBegun = false;
		return true;
	}

	bool D3DEffect::BeginPass(unsigned int pass)
	{
		if (!IsCreated())
			return false;
		
		const HRESULT hr = m_effect->BeginPass(pass);
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::BeginPass with pass=%u failed, hr=%s, desc=%s", 
				pass, DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3DEffect::EndPass()
	{
		if (!IsCreated())
			return false;

		const HRESULT hr = m_effect->EndPass();
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::EndPass failed, hr=%s, desc=%s", 
				DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	D3DEffect::Parameter* D3DEffect::GetParameter(const std::string& paramName)
	{
		if (!IsCreated())
			return nullptr;

		Parameters::iterator it = m_params.find(paramName);
		if (it != m_params.end())
			return &(it->second);

		const D3DXHANDLE hParam = m_effect->GetParameterByName(nullptr, paramName.c_str());
		if (hParam == nullptr)
		{
			Log::Error(L"ID3DXEffect::GetParameterByName with name:%s failed", paramName.c_str());
			return nullptr;
		}

		m_params[paramName].m_d3dEffect = this;
		m_params[paramName].m_handle = hParam;

		return &m_params[paramName];
	}

	D3DEffect::Parameter::Parameter()
	: m_d3dEffect(nullptr), m_handle(nullptr)
	{
	}

	bool D3DEffect::Parameter::SetValue(const Matrix4& m)
	{
		SK_REQUIRE(m_d3dEffect && m_handle);

		if (!m_d3dEffect->IsCreated())
			return false;

		D3DXMATRIXA16 d3dm;
		D3DMapping::ToD3DXMatrixA16(m, d3dm);
		const HRESULT hr = m_d3dEffect->m_effect->SetMatrix(m_handle, &d3dm);
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::SetMatrix failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}
		return true;
	}

	bool D3DEffect::Parameter::SetValue(const Vector4& v)
	{
		SK_REQUIRE(m_d3dEffect && m_handle);

		if (!m_d3dEffect->IsCreated())
			return false;

		D3DXVECTOR4 d3dv;
		D3DMapping::ToD3DXVector4(v, d3dv);
		const HRESULT hr = m_d3dEffect->m_effect->SetVector(m_handle, &d3dv);
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::SetVector failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}

	bool D3DEffect::Parameter::SetValue(const Texture& texture)
	{
		SK_REQUIRE(m_d3dEffect && m_handle);

		if (!m_d3dEffect->IsCreated())
			return false;

		const HRESULT hr = m_d3dEffect->m_effect->SetTexture(m_handle, texture.GetD3D9Texture());
		if (FAILED(hr))
		{
			Log::Error(L"ID3DXEffect::SetTexture failed, hr=%s, desc=%s", DXGetErrorString(hr), DXGetErrorDescription(hr));
			return false;
		}

		return true;
	}
}