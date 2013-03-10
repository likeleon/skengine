#include "Pch.h"
#include "CommonFixtures.h"
#include "MockClasses.h"
#include "SkRenderer.h"
#include "SkWindow.h"
#include "SkCamera.h"

using namespace ske;

class RendererTest : public WindowCreation 
{
protected:
	Camera camera;
};

TEST_F(RendererTest, CreateDestroyTest)
{
	Renderer renderer;
	EXPECT_FALSE(renderer.IsCreated());
		
	renderer.Create(window.GetHandle());
	EXPECT_TRUE(renderer.IsCreated());

	// Init again fails
	EXPECT_FALSE(renderer.Create(window.GetHandle()));
	EXPECT_TRUE(renderer.IsCreated());

	// Destroy
	renderer.Destroy();
	EXPECT_FALSE(renderer.IsCreated());

	renderer.Destroy();	// repitition has no effect
}

TEST_F(RendererTest, CreateFailTest)
{
	Renderer renderer;
	EXPECT_FALSE(renderer.Create(nullptr));
}

TEST_F(RendererTest, RenderTest)
{
	Renderer renderer;
	renderer.Create(window.GetHandle());

	// Add Renderable instances
	RenderableMock* renderable = new RenderableMock();
	renderer.AddRenderable(*renderable);
	ShaderRenderableMock* shaderRenderable = new ShaderRenderableMock(renderer.GetDevice());
	renderer.AddRenderable(*shaderRenderable);

	// Verify Render() invokes our renderable instance's Render function
	EXPECT_TRUE(renderer.Render(camera));
	EXPECT_EQ(1, renderable->m_numRenderCalled);
	EXPECT_EQ(1, shaderRenderable->m_numRenderCalled);
}

TEST_F(RendererTest, RenderFailTest)
{
	// Render without creation
	Renderer renderer;
	EXPECT_FALSE(renderer.Render(camera));
}