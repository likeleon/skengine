#pragma once

#include "SkTexture.h"
#include "SkShaderBase.h"

namespace ske
{
	class Matrix4;

	class IRenderable
	{
	public:
		virtual bool Render() = 0;
		virtual ShaderBasePtr GetShader() = 0;
		virtual TexturePtr GetTexture() = 0;
		virtual const Matrix4& GetWorldMatrix() = 0;

		virtual ~IRenderable() {}
	};
}