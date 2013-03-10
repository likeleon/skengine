#include "Pch.h"
#include "CommonFixtures.h"
#include "SkVertexBuffer.h"

using namespace ske;

class VertexBufferTest : public RendererCreation 
{
protected:
	bool CreateVBuf(VertexBuffer& vbuf, const float* src, size_t srcSize)
	{
		return vbuf.Create(renderer.GetDevice(), src, srcSize);
	}
};

TEST_F(VertexBufferTest, CreateDestroyTest)
{
	VertexBuffer vbuf;
	EXPECT_FALSE(vbuf.IsCreated());
	EXPECT_TRUE(nullptr == vbuf.GetVertexBuffer());
	EXPECT_TRUE(0 == vbuf.GetSize());

	const float src[12] = {0.0f};
	EXPECT_TRUE(CreateVBuf(vbuf, src, sizeof(src)));
	EXPECT_FALSE(CreateVBuf(vbuf, src, sizeof(src)));
	EXPECT_TRUE(vbuf.IsCreated());
	EXPECT_TRUE(nullptr != vbuf.GetVertexBuffer());
	EXPECT_TRUE(sizeof(src) == vbuf.GetSize());

	vbuf.Destroy();
	EXPECT_FALSE(vbuf.IsCreated());
	EXPECT_TRUE(nullptr == vbuf.GetVertexBuffer());
	EXPECT_TRUE(0 == vbuf.GetSize());
}

TEST_F(VertexBufferTest, CreateFailTest)
{
	VertexBuffer vbuf;
	const float src[12] = {0.0f};

	EXPECT_FALSE(CreateVBuf(vbuf, src, 0));
	EXPECT_FALSE(CreateVBuf(vbuf, nullptr, sizeof(src)));
}