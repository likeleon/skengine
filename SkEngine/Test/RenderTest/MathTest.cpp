#include "Pch.h"
#include "SkMath.h"

using namespace ske;

TEST(MathTest, ConstantsTest)
{
	EXPECT_EQ(4.0f * atan(1.0f), Math::PI);
}

TEST(MathTest, IsNearZeroTest)
{
	EXPECT_TRUE(Math::IsNearZero(0.0f));
	EXPECT_FALSE(Math::IsNearZero(0.1f));
}