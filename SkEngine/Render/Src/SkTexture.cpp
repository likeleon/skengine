#include "Pch.h"
#include "SkTexture.h"
#include "SkD3D9Device.h"
#include "SkUtilities.h"

namespace ske
{
	Texture::Texture()
	: m_texture(nullptr)
	{
	}

	Texture::~Texture()
	{
		Destroy();
	}

	bool Texture::CreateFromFile(D3D9Device& device, const std::wstring& fileName)
	{
		if (fileName.empty())
			return false;

		if (IsCreated())
			return false;

		if (!device.CreateTextureFromFile(fileName, &m_texture))
			return false;

		SK_ENSURE(IsCreated());
		return true;
	}

	void Texture::Destroy()
	{
		SafeRelease(m_texture);
	}

	bool Texture::IsCreated() const
	{
		return (m_texture != nullptr);
	}
}