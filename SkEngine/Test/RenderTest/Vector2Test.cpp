#include "Pch.h"
#include "SkVector2.h"

using namespace ske;

TEST(Vector2Test, ConstructTest)
{
	const Vector2 a;

	const Vector2 b(1.0f, 1.0f);
	EXPECT_EQ(1.0f, b.x);
	EXPECT_EQ(1.0f, b.y);
}

TEST(Vector2Test, EqualityTest)
{
	const Vector2 a(1.0f, 1.0f);
	const Vector2 b(1.0f, 1.0f);
	EXPECT_TRUE(a == b);

	const Vector2 c(0.0f, 0.0f);
	EXPECT_TRUE(a != c);
}

TEST(Vector2Test, UnaryTest)
{
	const Vector2 a(1.0f, 2.0f);

	EXPECT_EQ(-1.0f, (-a).x);
	EXPECT_EQ(-2.0f, (-a).y);
}

TEST(Vector2Test, AssignmentTest)
{
	const Vector2 a(2.0f, 3.0f);

	Vector2 b;	
	b = a;
	EXPECT_TRUE(b == a);

	Vector2 c;
	c = (b = a);
	EXPECT_TRUE(c == a);
}

TEST(Vector2Test, AdditionTest)
{
	const Vector2 a(1.0f, 1.0f);
	const Vector2 b(1.0f, 2.0f);

	// operator +
	Vector2 c = a + b;
	EXPECT_EQ(2.0f, c.x);
	EXPECT_EQ(3.0f, c.y);

	Vector2 c2 = a + b + c;
	EXPECT_EQ(4.0f, c2.x);
	EXPECT_EQ(6.0f, c2.y);

	// operator +=
	Vector2 d(1.0f, 3.0f);
	d += a;
	EXPECT_EQ(2.0f, d.x);
	EXPECT_EQ(4.0f, d.y);

	d = (c += b);
	EXPECT_TRUE(d == c);
}

TEST(Vector2Test, SubtractionTest)
{
	const Vector2 a(1.0f, 1.0f);
	const Vector2 b(1.0f, 2.0f);

	// operator -
	Vector2 c = a - b;
	EXPECT_EQ(0.0f, c.x);
	EXPECT_EQ(-1.0f, c.y);

	Vector2 c2 = a - b - c;
	EXPECT_EQ(0.0f, c2.x);
	EXPECT_EQ(0.0f, c2.y);

	// operator -=
	Vector2 d(1.0f, 3.0f);
	d -= a;
	EXPECT_EQ(0.0f, d.x);
	EXPECT_EQ(2.0f, d.y);

	d = (c -= b);
	EXPECT_TRUE(d == c);
}

TEST(Vector2Test, MultiplicationByScalarTest)
{
	const Vector2 a(1.0f, 2.0f);

	// operator *
	Vector2 b = a * 2.0f;
	EXPECT_EQ(2.0f, b.x);
	EXPECT_EQ(4.0f, b.y);

	b = 2.0f * a;
	EXPECT_EQ(2.0f, b.x);
	EXPECT_EQ(4.0f, b.y);

	Vector2 b2 = a * 2.0f * 3.0f;
	EXPECT_EQ(6.0f, b2.x);
	EXPECT_EQ(12.0f, b2.y);

	// operator *=
	Vector2 c(1.0f, 3.0f);
	c *= 2;
	EXPECT_EQ(2.0f, c.x);
	EXPECT_EQ(6.0f, c.y);

	c = (b *= 2);
	EXPECT_TRUE(c == b);
}

TEST(Vector2Test, DivisionTest)
{
	const Vector2 a(1.0f, 2.0f);

	// operator /
	Vector2 b = a / 2.0f;
	EXPECT_EQ(0.5f, b.x);
	EXPECT_EQ(1.0f, b.y);

	Vector2 b2 = a / 2.0f / 0.5f;
	EXPECT_EQ(1.0f, b2.x);
	EXPECT_EQ(2.0f, b2.y);

	// operator /=
	Vector2 c(1.0f, 3.0f);
	c /= 2.0f;
	EXPECT_EQ(0.5f, c.x);
	EXPECT_EQ(1.5f, c.y);

	// TODO: Division by zero
}

TEST(Vector2Test, MagnitudeTest)
{
	const Vector2 a(3.0f, 4.0f);

	EXPECT_EQ(5.0f, a.Length());
	EXPECT_EQ(25.0f, a.SquaredLength());

	const Vector2 b(0.0f, 0.0f);
	EXPECT_EQ(0.0f, b.Length());
	EXPECT_EQ(0.0f, b.SquaredLength());
}

TEST(Vector2Test, NormalizationTest)
{
	Vector2 a(3.0f, 4.0f);
	a.Normalize();
	EXPECT_EQ(1.0f, a.Length());

	Vector2 b(0.0f, 0.0f);
	b.Normalize();
	EXPECT_EQ(0.0f, b.Length());
}

TEST(Vector2Test, DotProductTest)
{
	const Vector2 a(1.0f, 2.0f);
	const Vector2 b(3.0f, 4.0f);

	EXPECT_EQ(11.0f, Vector2::Dot(a, b));

	// Commutative
	EXPECT_EQ(Vector2::Dot(a, b), Vector2::Dot(b, a));

	// Distributive over addition
	const Vector2 c(-1.0f, 1.0f);
	EXPECT_EQ(Vector2::Dot(c, a + b),
			  Vector2::Dot(c, a) + Vector2::Dot(c, b));

	// Combines with scalar multiplication
	const float s = 2.0f;
	EXPECT_EQ(Vector2::Dot(s * a, b), Vector2::Dot(a, s * b));
	EXPECT_EQ(Vector2::Dot(s * a, b), s * Vector2::Dot(a, b));
}

TEST(Vector2Test, WriteToStreamTest)
{
	std::ostringstream ost;
	const Vector2 v(1.0f, 2.2f);
	ost << v;
	EXPECT_EQ("Vector2(1, 2.2)", ost.str());
}