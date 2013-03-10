#include "Pch.h"
#include "SkAssert.h"
#include "SkVector3.h"

using namespace ske;

TEST(Vector3Test, ConstructTest)
{
	const Vector3 a;

	const Vector3 b(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(1.0f, b.x);
	EXPECT_EQ(2.0f, b.y);
	EXPECT_EQ(3.0f, b.z);
}

TEST(Vector3Test, EqualityTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);
	const Vector3 b(1.0f, 2.0f, 3.0f);
	EXPECT_TRUE(a == b);

	const Vector3 c(1.0f, 2.0f, 0.0f);
	EXPECT_TRUE(a != c);
}

TEST(Vector3Test, UnaryTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);

	EXPECT_EQ(-1.0f, (-a).x);
	EXPECT_EQ(-2.0f, (-a).y);
	EXPECT_EQ(-3.0f, (-a).z);
}

TEST(Vector3Test, AssignmentTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);

	Vector3 b;
	b = a;
	EXPECT_TRUE(b == a);

	Vector3 c;
	c = (b = a);
	EXPECT_TRUE(c == a);
}

TEST(Vector3Test, AdditionTest)
{
	const Vector3 a(1.0f, 1.0f, 1.0f);
	const Vector3 b(1.0f, 2.0f, 3.0f);

	// operator +
	Vector3 c = a + b;
	EXPECT_EQ(2.0f, c.x);
	EXPECT_EQ(3.0f, c.y);
	EXPECT_EQ(4.0f, c.z);

	Vector3 c2 = a + b + c;
	EXPECT_EQ(4.0f, c2.x);
	EXPECT_EQ(6.0f, c2.y);
	EXPECT_EQ(8.0f, c2.z);

	// operator +=
	Vector3 d(1.0f, 3.0f, 5.0f);
	d += a;
	EXPECT_EQ(2.0f, d.x);
	EXPECT_EQ(4.0f, d.y);
	EXPECT_EQ(6.0f, d.z);

	d = (c += b);
	EXPECT_TRUE(d == c);
}

TEST(Vector3Test, SubtractionTest)
{
	const Vector3 a(1.0f, 1.0f, 1.0f);
	const Vector3 b(1.0f, 2.0f, 3.0f);

	// operator -
	Vector3 c = a - b;
	EXPECT_EQ(0.0f, c.x);
	EXPECT_EQ(-1.0f, c.y);
	EXPECT_EQ(-2.0f, c.z);

	Vector3 c2 = a - b - c;
	EXPECT_EQ(0.0f, c2.x);
	EXPECT_EQ(0.0f, c2.y);
	EXPECT_EQ(0.0f, c2.z);

	// operator -=
	Vector3 d(1.0f, 3.0f, 5.0f);
	d -= a;
	EXPECT_EQ(0.0f, d.x);
	EXPECT_EQ(2.0f, d.y);
	EXPECT_EQ(4.0f, d.z);

	d = (c -= b);
	EXPECT_TRUE(d == c);
}

TEST(Vector3Test, MultiplicationByScalarTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);

	// operator *
	Vector3 b = a * 2.0f;
	EXPECT_EQ(2.0f, b.x);
	EXPECT_EQ(4.0f, b.y);
	EXPECT_EQ(6.0f, b.z);

	b = 2.0f * a;
	EXPECT_EQ(2.0f, b.x);
	EXPECT_EQ(4.0f, b.y);
	EXPECT_EQ(6.0f, b.z);

	Vector3 b2 = a * 2.0f * 3.0f;
	EXPECT_EQ(6.0f, b2.x);
	EXPECT_EQ(12.0f, b2.y);
	EXPECT_EQ(18.0f, b2.z);

	// operator *=
	Vector3 c(1.0f, 3.0f, 5.0f);
	c *= 2;
	EXPECT_EQ(2.0f, c.x);
	EXPECT_EQ(6.0f, c.y);
	EXPECT_EQ(10.0f, c.z);

	c = (b *= 2);
	EXPECT_TRUE(c == b);
}

TEST(Vector3Test, DivisionTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);

	// operator /
	Vector3 b = a / 2.0f;
	EXPECT_EQ(0.5f, b.x);
	EXPECT_EQ(1.0f, b.y);
	EXPECT_EQ(1.5f, b.z);

	Vector3 b2 = a / 2.0f / 0.5f;
	EXPECT_EQ(1.0f, b2.x);
	EXPECT_EQ(2.0f, b2.y);
	EXPECT_EQ(3.0f, b2.z);

	// operator /=
	Vector3 c(1.0f, 3.0f, 5.0f);
	c /= 2.0f;
	EXPECT_EQ(0.5f, c.x);
	EXPECT_EQ(1.5f, c.y);
	EXPECT_EQ(2.5f, c.z);

	// TODO: Division by zero
}

TEST(Vector3Test, MagnitudeTest)
{
	const Vector3 a(3.0f, 4.0f, 5.0f);

	const float len = (float)(std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
	EXPECT_EQ(len, a.Length());
	EXPECT_EQ(len * len, a.SquaredLength());

	const Vector3 b(0.0f, 0.0f, 0.0f);
	EXPECT_EQ(0.0f, b.Length());
	EXPECT_EQ(0.0f, b.SquaredLength());
}

TEST(Vector3Test, NormalizationTest)
{
	Vector3 a(3.0f, 4.0f, 5.0f);
	const Vector3 b(a);
	a.Normalize();
	EXPECT_EQ(a, Vector3::Normalize(b));
	EXPECT_EQ(1.0f, a.Length());

	Vector3 c(0.0f, 0.0f, 0.0f);
	c.Normalize();
	EXPECT_EQ(0.0f, c.Length());
}

TEST(Vector3Test, DotProductTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);
	const Vector3 b(3.0f, 4.0f, 5.0f);

	EXPECT_EQ(26.0f, Vector3::Dot(a, b));

	// Commutative
	EXPECT_EQ(Vector3::Dot(a, b), Vector3::Dot(b, a));

	// Distributive over addition
	const Vector3 c(-1.0f, 1.0f, 3.0f);
	EXPECT_EQ(Vector3::Dot(c, a + b),
			  Vector3::Dot(c, a) + Vector3::Dot(c, b));

	// Combines with scalar multiplication
	const float s = 2.0f;
	EXPECT_EQ(Vector3::Dot(s * a, b), Vector3::Dot(a, s * b));
	EXPECT_EQ(Vector3::Dot(s * a, b), s * Vector3::Dot(a, b));
}

TEST(Vector3Test, CrossProductTest)
{
	const Vector3 a(1.0f, 2.0f, 3.0f);
	const Vector3 b(3.0f, 4.0f, 5.0f);

	const Vector3 c = Vector3::Cross(a, b);
	EXPECT_EQ(a.y * b.z - a.z * b.y, c.x);
	EXPECT_EQ(a.z * b.x - a.x * b.z, c.y);
	EXPECT_EQ(a.x * b.y - a.y * b.x, c.z);

	// Anticommutative: a x b = -b x a
	EXPECT_TRUE(Vector3::Cross(a, b) == Vector3::Cross(-b, a));

	// Distributive over addition: a x (b + c) = (a x b) + (a x c)
	EXPECT_TRUE(Vector3::Cross(a, b + c) == Vector3::Cross(a, b) + Vector3::Cross(a, c));

	// Scalar multiplication: (ra) x b = a x (rb) = r(a x b)
	const float mult = 1.5f;
	EXPECT_TRUE(Vector3::Cross(mult * a, b) == Vector3::Cross(a, mult * b));
	EXPECT_TRUE(Vector3::Cross(mult * a, b) == mult * Vector3::Cross(a, b));
}

TEST(Vector3Test, WriteToStreamTest)
{
	std::ostringstream ost;
	const Vector3 v(1.0f, 2.2f, 3.33f);
	ost << v;
	EXPECT_EQ("Vector3(1, 2.2, 3.33)", ost.str());
}

TEST(Vector3Test, SpecialVectorsTest)
{
	const Vector3 zero(0.0f, 0.0f, 0.0f);
	EXPECT_EQ(zero, Vector3::Zero);

	const Vector3 unitx(1.0f, 0.0f, 0.0f);
	EXPECT_EQ(unitx, Vector3::UnitX);

	const Vector3 unity(0.0f, 1.0f, 0.0f);
	EXPECT_EQ(unity, Vector3::UnitY);

	const Vector3 unitz(0.0f, 0.0f, 1.0f);
	EXPECT_EQ(unitz, Vector3::UnitZ);
}