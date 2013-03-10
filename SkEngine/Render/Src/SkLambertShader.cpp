#include "Pch.h"
#include "SkLambertShader.h"
#include "SkLog.h"
#include "SkCamera.h"
#include "SkD3DMapping.h"
#include "SkIRenderable.h"

namespace ske
{
	LambertShader::LambertShader()
		: m_paramWorld(nullptr), m_paramWorldInvTrans(nullptr), m_paramWorldViewProj(nullptr)
	{
	}

	bool LambertShader::Create(D3D9Device& device)
	{
		if (!m_effect.Create(device, L"../../Media/Shaders/Lambert.fx"))
			return false;

		m_paramTexture = m_effect.GetParameter("gTexture");
		m_paramWorld = m_effect.GetParameter("gWorldXf");
		m_paramWorldInvTrans = m_effect.GetParameter("gWorldITXf");
		m_paramWorldViewProj = m_effect.GetParameter("gWvpXf");
		if (!m_paramTexture || !m_paramWorld || !m_paramWorldInvTrans || !m_paramWorldViewProj)
			goto LOCAL_EXIT_FAIL;

		SK_ENSURE(IsCreated());
		return true;

LOCAL_EXIT_FAIL:
		Destroy();
		return false;
	}

	void LambertShader::OnDestroy()
	{
		m_paramTexture = nullptr;
		m_paramWorld = nullptr;
		m_paramWorldInvTrans = nullptr;
		m_paramWorldViewProj = nullptr;
		ShaderBase::OnDestroy();
	}

	bool LambertShader::OnUpdateShaderParameters(unsigned int pass, IRenderable& renderable, const Camera& camera)
	{
		(void)pass;

		// Texture
		const TexturePtr texture = renderable.GetTexture();
		if (texture)
		{
			if (!m_paramTexture->SetValue(*texture))
				return false;
		}

		// World
		const Matrix4& worldMat = renderable.GetWorldMatrix();
		if (!m_paramWorld->SetValue(worldMat))
			return false;

		// WorldInverseTranspose
		if (!m_paramWorldInvTrans->SetValue(worldMat.Invert().Transpose()))
			return false;

		// WorldViewProjection
		const Matrix4 wvpMat = worldMat * 
			camera.GetViewMatrix() *
			camera.GetProjectionMatrix();

		if (!m_paramWorldViewProj->SetValue(wvpMat))
			return false;

		return true;
	}
}