#include "Pch.h"
#include "CommonFixtures.h"
#include "SkIndexBuffer.h"

using namespace ske;

class IndexBufferTest : public RendererCreation 
{
protected:
	bool CreateIBuf(IndexBuffer& ibuf, const short* src, size_t srcSize)
	{
		return ibuf.Create(renderer.GetDevice(), src, srcSize);
	}
};

TEST_F(IndexBufferTest, CreateDestroyTest)
{
	IndexBuffer ibuf;
	EXPECT_FALSE(ibuf.IsCreated());
	EXPECT_TRUE(nullptr == ibuf.GetIndexBuffer());
	EXPECT_EQ(0, ibuf.GetNumIndices());

	const short src[12] = {0};
	EXPECT_TRUE(CreateIBuf(ibuf, src, sizeof(src)));
	EXPECT_FALSE(CreateIBuf(ibuf, src, sizeof(src)));
	EXPECT_TRUE(ibuf.IsCreated());
	EXPECT_TRUE(nullptr != ibuf.GetIndexBuffer());
	EXPECT_EQ(sizeof(src) / sizeof(short), ibuf.GetNumIndices());

	ibuf.Destroy();
	EXPECT_FALSE(ibuf.IsCreated());
	EXPECT_TRUE(nullptr == ibuf.GetIndexBuffer());
	EXPECT_EQ(0, ibuf.GetNumIndices());
}

TEST_F(IndexBufferTest, CreateFailTest)
{
	IndexBuffer ibuf;
	const short src[12] = {0};

	EXPECT_FALSE(CreateIBuf(ibuf, src, 0));
	EXPECT_FALSE(CreateIBuf(ibuf, nullptr, sizeof(src)));
}