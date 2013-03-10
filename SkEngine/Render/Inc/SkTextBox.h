#pragma once

#include <string>
#include <d3dx9.h>
#include "SkIRenderable.h"
#include "SkNonCopyable.h"
#include "SkMatrix4.h"

namespace ske
{
	class D3D9Device;

	class TextBox : public IRenderable, private NonCopyable
	{
	public:
		TextBox(D3D9Device& device, const std::wstring& content, const RECT& drawRect);
		virtual ~TextBox();

	public:
		// Implements IRenderable
		virtual bool Render();
		virtual ShaderBasePtr GetShader() { return nullptr; }
		virtual TexturePtr GetTexture() { return nullptr; }
		virtual const Matrix4& GetWorldMatrix() { return Matrix4::Identity; }

	private:
		const std::wstring	m_content;
		ID3DXFont*			m_font;
		RECT				m_drawRect;
	};
}