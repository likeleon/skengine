#include "Pch.h"
#include "SkTextureManager.h"
#include "SkD3D9Device.h"

namespace ske
{
	TextureManager::TextureManager(D3D9Device& device)
		: m_device(device)
	{
	}

	TextureManager::~TextureManager()
	{
		m_textures.clear();
	}

	TexturePtr TextureManager::Load(const std::wstring& fileName)
	{
		TextureMap::iterator iter = m_textures.find(fileName);
		if (iter != m_textures.end())
			return iter->second;

		TexturePtr texture(new Texture());
		if (!texture->CreateFromFile(m_device, fileName))
			return nullptr;

		m_textures[fileName] = texture;
		return texture;
	}
}