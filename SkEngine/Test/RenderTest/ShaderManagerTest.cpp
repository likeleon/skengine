#include "Pch.h"
#include "SkShaderManager.h"
#include "CommonFixtures.h"

using namespace ske;

class ShaderManagerTest : public RendererCreation
{
};

TEST_F(ShaderManagerTest, GetLambertShaderTest)
{
	ShaderManager mgr(renderer.GetDevice());
	const LambertShaderPtr shader = mgr.GetLambertShader();
	EXPECT_TRUE(nullptr != shader);

	EXPECT_EQ(shader, mgr.GetLambertShader());
}