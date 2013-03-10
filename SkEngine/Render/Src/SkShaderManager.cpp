#include "Pch.h"
#include "SkShaderManager.h"
#include "SkD3D9Device.h"

namespace ske
{
	ShaderManager::ShaderManager(D3D9Device& device)
		: m_device(device), m_lambertShader(nullptr)
	{
	}

	ShaderManager::~ShaderManager()
	{
		m_lambertShader = nullptr;
	}

	LambertShaderPtr ShaderManager::GetLambertShader()
	{
		if (!m_lambertShader)
		{
			m_lambertShader = new LambertShader();
			m_lambertShader->Create(m_device);
		}
		return m_lambertShader;
	}
}