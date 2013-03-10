#include "Pch.h"
#include "CommonFixtures.h"
#include "SkManualRenderable.h"
#include "SkLambertShader.h"
#include "SkTexture.h"
#include "SkTextureManager.h"
#include "SkUtilities.h"

using namespace ske;

class ManualRenderableTest : public RendererCreation 
{
protected:
	ManualRenderableTest()
	: pos(MeshVertex::Position(0.0f, 1.0f, 0.0f)),
	  uv(MeshVertex::UV(1.0f, 1.0f)),
	  normal(MeshVertex::Normal(1.0f, 0.0f, 0.0f))
	{
	}

	virtual void SetUp()
	{
		RendererCreation::SetUp();
		shader = new LambertShader();
		shader->Create(renderer.GetDevice());
		textureMgr = new TextureManager(renderer.GetDevice());
		texture = textureMgr->Load(L"../../Media/Textures/Default_color.dds");
	}

	virtual void TearDown()
	{
		texture = nullptr;
		SafeDelete(textureMgr);
		shader = nullptr;
		RendererCreation::TearDown();
	}

	LambertShaderPtr shader;
	TexturePtr texture;
	const MeshVertex::Position pos;
	const MeshVertex::UV uv;
	const MeshVertex::Normal normal;
	TextureManager* textureMgr;

	// Helper methods
	void Add3Vertices(ManualRenderable& manual)
	{
		MeshVertex vertex(pos, uv, normal);
		manual.AddVertex(vertex);
		manual.AddVertex(vertex);
		manual.AddVertex(vertex);
	}
};

TEST_F(ManualRenderableTest, AddVertexTest)
{
	ManualRenderable manual(shader, texture);
	EXPECT_TRUE(manual.AddVertex(pos, uv, normal));

	MeshVertex vertex(pos, uv, normal);
	EXPECT_TRUE(manual.AddVertex(vertex));

	// Adding vertex after created is not allowed
	manual.Create(renderer.GetDevice());
	EXPECT_FALSE(manual.AddVertex(vertex));
}

TEST_F(ManualRenderableTest, CreateWithoutIndicesTest)
{
	ManualRenderable manual(shader, texture);
	Add3Vertices(manual);

	EXPECT_TRUE(manual.Create(renderer.GetDevice()));
	EXPECT_FALSE(manual.Create(renderer.GetDevice()));
}

TEST_F(ManualRenderableTest, CreateWithIndicesTest)
{
	ManualRenderable manual(shader, texture);
	Add3Vertices(manual);

	manual.AddIndex(0, 1, 2);
	EXPECT_TRUE(manual.Create(renderer.GetDevice()));
	EXPECT_FALSE(manual.Create(renderer.GetDevice()));
}

TEST_F(ManualRenderableTest, CreateFailTest)
{
	ManualRenderable manual(shader, texture);

	// Fail: Create with no vertex
	EXPECT_FALSE(manual.Create(renderer.GetDevice()));
}

TEST_F(ManualRenderableTest, RenderWithoutIndicesTest)
{
	std::auto_ptr<ManualRenderable> manual(new ManualRenderable(shader, texture));
	Add3Vertices(*manual);
	manual->Create(renderer.GetDevice());

	renderer.AddRenderable(*manual);
	EXPECT_TRUE(renderer.Render(camera));

	manual.release();
}

TEST_F(ManualRenderableTest, RenderWithIndicesTest)
{
	std::auto_ptr<ManualRenderable> manual(new ManualRenderable(shader, texture));
	Add3Vertices(*manual);
	manual->AddIndex(0, 1, 2);
	manual->Create(renderer.GetDevice());

	renderer.AddRenderable(*manual);
	EXPECT_TRUE(renderer.Render(camera));

	manual.release();
}

TEST_F(ManualRenderableTest, RenderFailTest)
{
	// FAIL: render without creation
	std::auto_ptr<ManualRenderable> manual(new ManualRenderable(shader, texture));
	renderer.AddRenderable(*manual);
	EXPECT_FALSE(renderer.Render(camera));

	manual.release();
}