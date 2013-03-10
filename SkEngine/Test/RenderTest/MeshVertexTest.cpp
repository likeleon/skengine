#include "Pch.h"
#include "SkMeshVertex.h"
#include "CommonFixtures.h"

using namespace ske;

class MeshVertexTest : public RendererCreation
{
};

TEST_F(MeshVertexTest, ConstructionTest)
{
	const MeshVertex::Position pos(1.0f, 2.0f, 3.0f);
	const MeshVertex::UV uv(0.0f, 1.0f);
	const MeshVertex::Normal normal(4.0f, 5.0f, 6.0f);

	MeshVertex meshv(pos, uv, normal);
	EXPECT_EQ(pos, meshv.pos);
	EXPECT_EQ(uv, meshv.uv);
	EXPECT_EQ(normal, meshv.normal);
}

TEST_F(MeshVertexTest, VertexSizeTest)
{
	EXPECT_EQ(sizeof(float) * 8, MeshVertex::VertexSize);
}

TEST_F(MeshVertexTest, CreateDeclarationTest)
{
	VertexDeclarationPtr decl(MeshVertex::CreateDeclaration(renderer.GetDevice()));
	EXPECT_TRUE(nullptr != decl.Get());
	EXPECT_TRUE(nullptr != decl->GetD3DDecl());
	EXPECT_TRUE(decl->IsCreated());
}