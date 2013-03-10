#include "Pch.h"
#include "SkMesh.h"
#include "CommonFixtures.h"
#include "SkLambertShader.h"
#include "SkTextureManager.h"
#include "SkUtilities.h"

using namespace ske;

class MeshTest : public RendererCreation 
{
protected:
	bool CreateMeshFromXFile(Mesh& mesh, const std::wstring& xFile = L"../../Media/Models/tiger.x")
	{
		return mesh.CreateFromXFile(renderer.GetDevice(), *textureMgr, xFile);
	}

	virtual void SetUp()
	{
		RendererCreation::SetUp();
		shader = new LambertShader();
		shader->Create(renderer.GetDevice());
		textureMgr = new TextureManager(renderer.GetDevice());
	}

	virtual void TearDown()
	{
		shader = nullptr;
		RendererCreation::TearDown();
		SafeDelete(textureMgr);
	}

	LambertShaderPtr shader;
	TextureManager* textureMgr;
};

TEST_F(MeshTest, CreateFromXFileTest)
{
	Mesh mesh(shader);
	EXPECT_FALSE(mesh.IsCreated());

	EXPECT_TRUE(CreateMeshFromXFile(mesh));
	EXPECT_FALSE(CreateMeshFromXFile(mesh));
	EXPECT_TRUE(mesh.IsCreated());

	mesh.Destroy();
	EXPECT_FALSE(mesh.IsCreated());
}

TEST_F(MeshTest, CreateFailTest)
{
	Mesh mesh(shader);
	EXPECT_FALSE(CreateMeshFromXFile(mesh, L""));
	EXPECT_FALSE(CreateMeshFromXFile(mesh, L"NonExistingFile.x"));
}

TEST_F(MeshTest, RenderTest)
{
	std::auto_ptr<Mesh> mesh(new Mesh(shader));
	CreateMeshFromXFile(*mesh);

	renderer.AddRenderable(*mesh);
	EXPECT_TRUE(renderer.Render(camera));

	mesh.release();
}