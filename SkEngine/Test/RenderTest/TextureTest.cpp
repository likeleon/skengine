#include "Pch.h"
#include "SkTexture.h"
#include "CommonFixtures.h"

using namespace ske;

class TextureTest : public RendererCreation 
{
protected:
	bool CreateTextureFromFile(Texture& texture, const std::wstring& fileName = L"../../Media/Textures/Default_color.dds")
	{
		return texture.CreateFromFile(renderer.GetDevice(), fileName);
	}
};

TEST_F(TextureTest, CreateFromFileTest)
{
	Texture texture;
	EXPECT_FALSE(texture.IsCreated());

	EXPECT_TRUE(CreateTextureFromFile(texture));
	EXPECT_FALSE(CreateTextureFromFile(texture));
	EXPECT_TRUE(texture.IsCreated());

	texture.Destroy();
	EXPECT_FALSE(texture.IsCreated());
}

TEST_F(TextureTest, CreateFailTest)
{
	Texture texture;
	EXPECT_FALSE(CreateTextureFromFile(texture, L""));
	EXPECT_FALSE(CreateTextureFromFile(texture, L"./NonExistingFile.dds"));
}

TEST_F(TextureTest, GetD3D9TextureTest)
{
	Texture texture;
	EXPECT_TRUE(nullptr == texture.GetD3D9Texture());
	
	CreateTextureFromFile(texture);
	EXPECT_TRUE(nullptr != texture.GetD3D9Texture());

	texture.Destroy();
	EXPECT_TRUE(nullptr == texture.GetD3D9Texture());
}