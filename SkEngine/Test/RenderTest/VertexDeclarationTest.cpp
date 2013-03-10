#include "Pch.h"
#include "CommonFixtures.h"
#include "SkVertexDeclaration.h"

using namespace ske;

class VertexDeclarationTest : public RendererCreation {};

TEST_F(VertexDeclarationTest, CreateDestroyTest)
{
	VertexDeclaration vdecl;
	EXPECT_FALSE(vdecl.IsCreated());
	EXPECT_TRUE(nullptr == vdecl.GetD3DDecl());

	// Build vertex layout
	EXPECT_TRUE(vdecl.AddVertexElement(0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0));
	EXPECT_TRUE(vdecl.AddVertexElement(0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0));
	
	// Create
	EXPECT_TRUE(vdecl.Create(renderer.GetDevice()));
	EXPECT_FALSE(vdecl.Create(renderer.GetDevice()));	// create again fails
	EXPECT_TRUE(nullptr != vdecl.GetD3DDecl());
	EXPECT_TRUE(vdecl.IsCreated());

	// Build layout after created fails
	EXPECT_FALSE(vdecl.AddVertexElement(0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0));

	// Destroy
	vdecl.Destroy();
	vdecl.Destroy();	// repetition has no effect
	EXPECT_FALSE(vdecl.IsCreated());
	EXPECT_TRUE(nullptr == vdecl.GetD3DDecl());
}

TEST_F(VertexDeclarationTest, CreateFailTest)
{
	VertexDeclaration vdecl;

	// Fail: create with empty layout
	EXPECT_FALSE(vdecl.Create(renderer.GetDevice()));
}