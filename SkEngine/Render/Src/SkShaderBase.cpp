#include "Pch.h"
#include "SkShaderBase.h"
#include "SkD3D9Device.h"
#include "SkLog.h"
#include "SkIRenderable.h"

namespace ske
{
	ShaderBase::ShaderBase()
	{}

	ShaderBase::~ShaderBase()
	{
		Destroy();
	}

	void ShaderBase::Destroy()
	{
		OnDestroy();
		SK_ENSURE(!IsCreated());
	}

	void ShaderBase::OnDestroy()
	{
		m_effect.Destroy();
	}

	bool ShaderBase::IsCreated() const
	{
		return m_effect.IsCreated();
	}

	bool ShaderBase::Render(IRenderable& renderable, const Camera& camera)
	{
		if (!IsCreated())
			return false;

		const std::string techniqueName = "RenderTechnique";

		if (!m_effect.SetTechnique(techniqueName.c_str()))
			return false;

		unsigned int numPass = 0;
		if (!m_effect.Begin(numPass))
			return false;

		for (unsigned int pass = 0; pass < numPass; ++pass)
		{
			if (!m_effect.BeginPass(pass))
				return false;

			if (!OnUpdateShaderParameters(pass, renderable, camera))
			{
				Log::Warning(L"OnUpdateShaderParameters failed, pass=%u, instance=0x%x", pass, &renderable);
				return false;
			}

			if (!renderable.Render())
			{
				Log::Warning(L"IRenderable::render failed, instance=0x%x", &renderable);
				return false;
			}

			if (!m_effect.EndPass())
				return false;
		}

		if (!m_effect.End())
			return false;
		
		return true;
	}
}