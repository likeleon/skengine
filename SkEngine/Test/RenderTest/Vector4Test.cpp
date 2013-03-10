#include "Pch.h"
#include "SkVector4.h"

using namespace ske;

TEST(Vector4Test, ConstructTest)
{
	const Vector4 a;

	const Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_EQ(1.0f, b.x);
	EXPECT_EQ(2.0f, b.y);
	EXPECT_EQ(3.0f, b.z);
	EXPECT_EQ(4.0f, b.w);
}

TEST(Vector4Test, CreateFromVector3Test)
{
	const Vector3 v3(1.0f, 2.0f, 3.0f);
	const Vector4 v4(v3, 0.8f);
	const Vector4 expected(v3.x, v3.y, v3.z, 0.8f);
	EXPECT_EQ(expected, v4);
}

TEST(Vector4Test, EqualityTest)
{
	const Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
	const Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_TRUE(a == b);

	const Vector4 c(1.0f, 2.0f, 0.0f, -1.0f);
	EXPECT_TRUE(a != c);
}

TEST(Vector4Test, AdditionTest)
{
	const Vector4 a(1.0f, 1.0f, 1.0f, 1.0f);
	const Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);

	// operator +
	Vector4 c = a + b;
	EXPECT_EQ(2.0f, c.x);
	EXPECT_EQ(3.0f, c.y);
	EXPECT_EQ(4.0f, c.z);
	EXPECT_EQ(5.0f, c.w);
}

TEST(Vector4Test, DotProductTest)
{
	const Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
	const Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

	EXPECT_EQ(70.0f, Vector4::Dot(a, b));

	// Commutative
	EXPECT_EQ(Vector4::Dot(a, b), Vector4::Dot(b, a));

	// Distributive over addition
	const Vector4 c(-1.0f, 1.0f, 3.0f, 5.0f);
	EXPECT_EQ(Vector4::Dot(c, a + b),
			  Vector4::Dot(c, a) + Vector4::Dot(c, b));

	// Combines with scalar multiplication
	const float s = 2.0f;
	EXPECT_EQ(Vector4::Dot(s * a, b), Vector4::Dot(a, s * b));
	EXPECT_EQ(Vector4::Dot(s * a, b), s * Vector4::Dot(a, b));
}

TEST(Vector4Test, WriteToStreamTest)
{
	std::ostringstream ost;
	const Vector4 v(1.0f, 2.2f, 3.33f, 4.444f);
	ost << v;
	EXPECT_EQ("Vector4(1, 2.2, 3.33, 4.444)", ost.str());
}

TEST(Vector4Test, SpecialVectorsTest)
{
	const Vector4 zero(0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(zero, Vector4::Zero);
}