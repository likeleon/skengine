#pragma once

#include "SkShaderBase.h"
#include "SkMatrix4.h"
#include "SkIntrusivePtr.h"

namespace ske
{
	class D3D9Device;

	class LambertShader : public ShaderBase
	{
	public:
		LambertShader();
		bool Create(D3D9Device& device);

	private:
		// Implements ShaderBase
		virtual bool OnUpdateShaderParameters(unsigned int pass, IRenderable& renderable, const Camera& camera);

		// Overrides ShaderBase
		virtual void OnDestroy();

	private:
		D3DEffect::Parameter* m_paramTexture;
		D3DEffect::Parameter* m_paramWorld;
		D3DEffect::Parameter* m_paramWorldInvTrans;
		D3DEffect::Parameter* m_paramWorldViewProj;
	};

	typedef IntrusivePtr<LambertShader> LambertShaderPtr;
}