#include "Pch.h"
#include "SkRenderer.h"
#include "SkLog.h"
#include "SkUtilities.h"
#include "SkShaderBase.h"
#include "SkIRenderable.h"

namespace ske
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		Destroy();
	}

	bool Renderer::Create(HWND hWnd)
	{
		if (!hWnd)
			return false;
		if (IsCreated())
			return false;

		if (!m_device.Create(hWnd))
		{
			Destroy();
			return false;
		}

		if (!m_device.SetCullMode(D3D9Device::Cull_None) ||
			!m_device.SetDepthBufferMode(D3D9Device::Depth_ZBuffer))
		{
			Destroy();
			return false;
		}

		SK_ENSURE(IsCreated());
		return true;
	}

	void Renderer::Destroy()
	{
		std::for_each(m_renderables.begin(), m_renderables.end(), Deleter());
		m_renderables.clear();

		m_device.Destroy();

		SK_ENSURE(!IsCreated());
	}

	bool Renderer::IsCreated() const
	{
		return m_device.IsCreated();
	}

	bool Renderer::Render(const Camera& camera)
	{
		if (!IsCreated())
			return false;

		m_device.Clear();
		bool success = false;
		if (m_device.BeginScene())
		{
			for (Renderables::iterator it = m_renderables.begin(); it != m_renderables.end(); ++it)
			{
				IRenderable* renderable = *it;
				ShaderBasePtr const shader = renderable->GetShader();
				if (shader)
					success = shader->Render(*renderable, camera);
				else
					success = renderable->Render();

				if (!success)
					break;
			}

			m_device.EndScene();
			m_device.Present();
		}

		return success;
	}

	void Renderer::AddRenderable(IRenderable& renderable)
	{
		m_renderables.push_back(&renderable);
	}
}