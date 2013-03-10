#include "Pch.h"
#include "SkRadian.h"

using namespace ske;

TEST(RadianTest, ConstructTest)
{
	Radian r;
	EXPECT_EQ(0.0f, r.GetRadian());

	Radian r2(3.14f);
	EXPECT_EQ(3.14f, r2.GetRadian());

	// Copy construct
	Radian r3(r);
	EXPECT_EQ(r.GetRadian(), r3.GetRadian());

	// Assignment
	Radian r4 = r;
	EXPECT_EQ(r.GetRadian(), r4.GetRadian());
}

TEST(RadianTest, ComparesTest)
{
	EXPECT_TRUE(Radian(1.0f) <  Radian(2.0f));
	EXPECT_TRUE(Radian(1.0f) <= Radian(1.0f));
	EXPECT_TRUE(Radian(1.0f) <= Radian(2.0f));
	EXPECT_TRUE(Radian(1.0f) == Radian(1.0f));
	EXPECT_TRUE(Radian(1.0f) != Radian(2.0f));
	EXPECT_TRUE(Radian(1.0f) >= Radian(1.0f));
	EXPECT_TRUE(Radian(2.0f) >= Radian(1.0f));
	EXPECT_TRUE(Radian(2.0f) >  Radian(1.0f));
}

TEST(RadianTest, OperatorsTest)
{
	EXPECT_EQ(Radian(1.0f),  +Radian(1.0f));
	EXPECT_EQ(Radian(3.0f),  Radian(1.0f) + Radian(2.0f));
	EXPECT_EQ(Radian(-1.0f), -Radian(1.0f));
	EXPECT_EQ(Radian(-1.0f), Radian(1.0f) - Radian(2.0f));
	EXPECT_EQ(Radian(3.0f),  Radian(1.0f) * 3);
	EXPECT_EQ(Radian(3.0f),  3 * Radian(1.0f));
	EXPECT_EQ(Radian(3.0f),  Radian(1.0f) * Radian(3.0f));
	EXPECT_EQ(Radian(1.5f),  Radian(3.0f) / 2);

	Radian r1(1.0f);
	EXPECT_EQ(Radian(3.0f), r1 += Radian(2.0f));
	EXPECT_EQ(Radian(2.0f), r1 -= Radian(1.0f));
	EXPECT_EQ(Radian(4.0f), r1 *= 2);
	EXPECT_EQ(Radian(2.0f), r1 /= 2);
}

TEST(RadianTest, WriteToStreamTest)
{
	std::ostringstream ost;
	const Radian r(-1.2f);
	ost << r;
	EXPECT_EQ("Radian(-1.2)", ost.str());
}
