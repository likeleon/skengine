#include "Pch.h"
#include "SkColor.h"

using namespace ske;

TEST(ColorTest, ConstructTest)
{
	const Color a;
	EXPECT_EQ(1.0f, a.r);
	EXPECT_EQ(1.0f, a.g);
	EXPECT_EQ(1.0f, a.b);
	EXPECT_EQ(1.0f, a.a);

	const Color b(0.0f, 0.4f, 0.8f, 1.0f);
	EXPECT_EQ(0.0f, b.r);
	EXPECT_EQ(0.4f, b.g);
	EXPECT_EQ(0.8f, b.b);
	EXPECT_EQ(1.0f, b.a);
}

TEST(ColorTest, EqualityTest)
{
	const Color a(1.0f, 1.0f, 1.0f, 1.0f);
	const Color b(1.0f, 1.0f, 1.0f, 1.0f);
	EXPECT_EQ(b, a);

	const Color c(0.0f, 1.0f, 1.0f, 1.0f);
	EXPECT_NE(c, a);
}

TEST(ColorTest, WriteToStreamTest)
{
	const Color color(0.0f, 0.1f, 0.22f, 0.333f);
	std::stringstream os;
	os << color;
	EXPECT_EQ("Color(0, 0.1, 0.22, 0.333)", os.str());
}