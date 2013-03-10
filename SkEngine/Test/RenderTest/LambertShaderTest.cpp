#include "Pch.h"
#include "CommonFixtures.h"
#include "SkLambertShader.h"
#include "MockClasses.h"

using namespace ske;

class LambertShaderTest : public RendererCreation {};

TEST_F(LambertShaderTest, CreateDestroyTest)
{
	LambertShader shader;
	EXPECT_FALSE(shader.IsCreated());

	EXPECT_TRUE(shader.Create(renderer.GetDevice()));
	EXPECT_FALSE(shader.Create(renderer.GetDevice()));
	EXPECT_TRUE(shader.IsCreated());

	// Destroy
	shader.Destroy();
	shader.Destroy(); // repetition has no effect
	EXPECT_FALSE(shader.IsCreated());
}

TEST_F(LambertShaderTest, RenderTest)
{
	LambertShader shader;
	RenderableMock renderable;
	EXPECT_FALSE(shader.Render(renderable, camera));
	
	shader.Create(renderer.GetDevice());
	EXPECT_TRUE(shader.Render(renderable, camera));
	EXPECT_EQ(1, renderable.m_numRenderCalled);
}