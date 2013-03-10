#pragma once

#include "SkNonCopyable.h"
#include "SkD3D9Device.h"
#include <list>

namespace ske
{
	class Renderer : private NonCopyable
	{
	public:
		Renderer();
		~Renderer();

		bool Create(HWND hWnd);
		void Destroy();
		bool IsCreated() const;

		void AddRenderable(IRenderable& renderable);
		bool Render(const Camera& camera);

		D3D9Device& GetDevice() { return m_device; }
		const D3D9Device& GetDevice() const { return m_device; }

	private:
		D3D9Device m_device;

		typedef std::list<IRenderable*> Renderables;
		Renderables m_renderables;
	};
}