#pragma once

#include <map>
#include "SkTexture.h"
#include "SkNonCopyable.h"

namespace ske
{
	class D3D9Device;

	class TextureManager : private NonCopyable
	{
	public:
		TextureManager(D3D9Device& device);
		~TextureManager();

		TexturePtr Load(const std::wstring& fileName);

	private:
		D3D9Device& m_device;
		typedef std::map<std::wstring, TexturePtr> TextureMap;
		TextureMap m_textures;
	};
}