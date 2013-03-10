#pragma once

#include "SkShaderBase.h"
#include "SkLambertShader.h"

namespace ske
{
	class ShaderManager : private NonCopyable
	{
	public:
		ShaderManager(D3D9Device& device);
		~ShaderManager();

		LambertShaderPtr GetLambertShader();

	private:
		D3D9Device& m_device;
		LambertShaderPtr m_lambertShader;
	};
}