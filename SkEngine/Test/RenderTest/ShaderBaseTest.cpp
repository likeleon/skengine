#include "Pch.h"
#include "CommonFixtures.h"
#include "MockClasses.h"
#include "SkShaderBase.h"

using namespace ske;

class ShaderBaseTest : public RendererCreation
{
protected:
	bool CreateShader(ShaderMock& shader, const std::wstring& effectFile = L"../../Media/Shaders/Simple.fx")
	{
		return shader.Create(renderer.GetDevice(), effectFile);
	}
};

TEST_F(ShaderBaseTest, CreateDestroyTest)
{
	ShaderMock shader;
	EXPECT_FALSE(shader.IsCreated());

	EXPECT_TRUE(CreateShader(shader));
	EXPECT_FALSE(CreateShader(shader));	// Create again fails
	EXPECT_TRUE(shader.IsCreated());

	// Destroy
	shader.Destroy();
	shader.Destroy(); // repetition has no effect
	EXPECT_FALSE(shader.IsCreated());
}

TEST_F(ShaderBaseTest, CreateFailTest)
{
	ShaderMock shader;

	EXPECT_FALSE(CreateShader(shader, L"./NonExistingFile.fx"));
}

TEST_F(ShaderBaseTest, RenderTest)
{
	ShaderMock shader;
	RenderableMock renderable;
	EXPECT_FALSE(shader.Render(renderable, camera));

	CreateShader(shader);
	EXPECT_TRUE(shader.Render(renderable, camera));
	EXPECT_EQ(1, renderable.m_numRenderCalled);
}

