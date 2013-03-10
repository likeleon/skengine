#include "Pch.h"
#include "SkTextureManager.h"
#include "CommonFixtures.h"

using namespace ske;

class TextureManagerTest : public RendererCreation 
{
protected:
	TexturePtr LoadTexture(TextureManager& mgr, const std::wstring& fileName = L"../../Media/Textures/Default_color.dds")
	{
		return mgr.Load(fileName);
	}
};

TEST_F(TextureManagerTest, LoadTest)
{
	TextureManager mgr(renderer.GetDevice());
	const TexturePtr texture = LoadTexture(mgr);
	EXPECT_TRUE(nullptr != texture);

	EXPECT_EQ(texture, LoadTexture(mgr));
}

TEST_F(TextureManagerTest, LoadFailTest)
{
	TextureManager mgr(renderer.GetDevice());
	EXPECT_TRUE(nullptr == LoadTexture(mgr, L"./NonExistingFile.dds"));
}