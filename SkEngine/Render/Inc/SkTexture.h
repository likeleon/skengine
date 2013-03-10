#pragma once

#include <string>
#include <d3dx9.h>
#include "SkNonCopyable.h"
#include "SkIntrusivePtr.h"

namespace ske
{
	class D3D9Device;

	class Texture : public IntrusiveSharedObject<size_t>, private NonCopyable
	{
	public:
		Texture();
		~Texture();

		bool CreateFromFile(D3D9Device& device, const std::wstring& fileName);
		void Destroy();
		bool IsCreated() const;

		LPDIRECT3DTEXTURE9 GetD3D9Texture() const { return m_texture; }

	private:
		LPDIRECT3DTEXTURE9 m_texture;
	};

	typedef IntrusivePtr<Texture> TexturePtr;
}