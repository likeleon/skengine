#pragma once

#include "SkNonCopyable.h"
#include <d3dx9.h>
#include "SkD3DEffect.h"
#include "SkIntrusivePtr.h"

namespace ske
{
	class IRenderable;
	class Camera;
	class D3D9Device;

	class ShaderBase : public IntrusiveSharedObject<size_t>, private NonCopyable
	{
	public:
		ShaderBase();
		virtual ~ShaderBase();

		void Destroy();
		bool IsCreated() const;

		bool Render(IRenderable& renderable, const Camera& camera);

	protected:
		virtual void OnDestroy();
		D3DEffect m_effect;

	private:
		virtual bool OnUpdateShaderParameters(unsigned int pass, IRenderable& renderable, const Camera& camera) = 0;
	};

	typedef IntrusivePtr<ShaderBase> ShaderBasePtr;
}