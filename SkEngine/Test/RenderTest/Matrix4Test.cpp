#include "Pch.h"
#include "SkMatrix4.h"
#include "SkVector4.h"

using namespace ske;

TEST(Matrix4Test, CreateFromElementsTest)
{
	const Matrix4 m(0,  4,  8,  12, 
					1,  5,  9,  13, 
					2,  6,  10, 14,
					3,  7,  11, 15);
	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t col = 0; col < 4; ++col)
		{
			EXPECT_EQ(col * 4 + row, m[row][col]);
		}
	}
}

TEST(Matrix4Test, CreateFromVectorsTest)
{
	const Vector4 v1(0, 1, 2, 3);
	const Vector4 v2(4, 5, 6, 7);
	const Vector4 v3(8, 9, 10, 11);
	const Vector4 v4(12, 13, 14, 15);

	const Matrix4 m(v1, v2, v3, v4);
	const Matrix4 expected(v1.x, v2.x, v3.x, v4.x, 
						   v1.y, v2.y, v3.y, v4.y, 
						   v1.z, v2.z, v3.z, v4.z,
						   v1.w, v2.w, v3.w, v4.w);
	EXPECT_EQ(expected, m);
}

TEST(Matrix4Test, EqualityTest)
{
	const Matrix4 a(0,  4,  8,  12, 
					1,  5,  9,  13, 
					2,  6,  10, 14,
					3,  7,  11, 15);
	const Matrix4 b(0,  4,  8,  12, 
					1,  5,  9,  13, 
					2,  6,  10, 14,
					3,  7,  11, 15);
	EXPECT_TRUE(a == b);

	const Matrix4 c(0, 0, 0, 0,
					1, 1, 1, 1,
					2, 2, 2, 2,
					3, 3, 3, 3);
	EXPECT_TRUE(a != c);
}

TEST(Matrix4Test, MultiplicationTest)
{
	const Matrix4 m1(0,  4,  8,  12, 
					 1,  5,  9,  13, 
					 2,  6,  10, 14,
					 3,  7,  11, 15);
	const Matrix4 m2(16, 20, 24, 28,
					 17, 21, 25, 29,
					 18, 22, 26, 30,
					 19, 23, 27, 31);
	Matrix4 res = m1 * m2;
	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t col = 0; col < 4; ++col)
		{
			const Vector4 rowv(m1[row][0], m1[row][1], m1[row][2], m1[row][3]);
			const Vector4 colv(m2[0][col], m2[1][col], m2[2][col], m2[3][col]);
			EXPECT_EQ(Vector4::Dot(rowv, colv), res[row][col]);
		}
	}

	// Not commutative (AB != BA)
	EXPECT_NE(m1 * m2, m2 * m1);
}

TEST(Matrix4Test, InvertTest)
{
	const Matrix4 a(1, 2, 2, 2,
				    2, 2, 1, 1,
					1, 2, 1, 0,
					1, 2, 2, 1);

	const Matrix4 b(-1,     1,   -1,     1,
					 1, -0.5f, 1.5f, -1.5f,
					-1,     0,   -1,     2,
					 1,     0,    0,    -1);

	EXPECT_EQ(b, a.Invert());

	Matrix4 ai;
	a.Invert(ai);
	EXPECT_EQ(b, ai);

	// A(A-1) = (A-1)A = I
	EXPECT_EQ(Matrix4::Identity, a * a.Invert());
	EXPECT_EQ(Matrix4::Identity, a.Invert() * a);

	// (AB)-1 = B-1A-1
	const Matrix4 c(2, 3, 2, 2,
					3, 3, 3, 3,
					3, 2, 2, 3,
					3, 2, 1, 2);
	EXPECT_EQ((a * c).Invert(), c.Invert() * a.Invert());

	// (M-1)-1 = M
	EXPECT_EQ(a, a.Invert().Invert());

	// I-1 = I
	EXPECT_EQ(Matrix4::Identity, Matrix4::Identity.Invert());

	// (MT)-1 = (M-1)T
	EXPECT_EQ(a.Transpose().Invert(), a.Invert().Transpose());
}

TEST(Matrix4Test, TransposeTest)
{
	const Matrix4 a(0, 1, 2, 3,
				    4, 5, 6, 7,
					8, 9, 10, 11,
					12, 13, 14, 15);
	EXPECT_EQ(Matrix4(0, 4, 8, 12,
					  1, 5, 9, 13,
					  2, 6, 10, 14,
					  3, 7, 11, 15), a.Transpose());

	Matrix4 at;
	a.Transpose(at);
	EXPECT_EQ(a.Transpose(), at);

	// (ABC)T = CT*BT*CT
	const Matrix4 b(16, 17, 18, 19,
					20, 21, 22, 23,
					24, 25, 26, 27,
					28, 29, 30, 31);
	const Matrix4 c(32, 33, 34, 35,
					36, 37, 38, 39,
					40, 41, 42, 43,
					44, 45, 46, 47);
	EXPECT_EQ((a * b * c).Transpose(),
			  c.Transpose() * b.Transpose() * a.Transpose()); 
}

TEST(Matrix4Test, SpecialMatricesTest)
{
	// Zero matrix
	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t col = 0; col < 4; ++col)
		{
			EXPECT_EQ(0, Matrix4::Zero[row][col]);
		}
	}

	// Identity matrix
	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t col = 0; col < 4; ++col)
		{
			if (row == col)
				EXPECT_EQ(1, Matrix4::Identity[row][col]);
			else
				EXPECT_EQ(0, Matrix4::Identity[row][col]);
		}
	}
}

TEST(Matrix4Test, WriteToStreamTest)
{
	std::ostringstream os;
	os << Matrix4::Identity;
	EXPECT_EQ("Matrix4( col0{1 0 0 0 } col1{0 1 0 0 } col2{0 0 1 0 } col3{0 0 0 1 })", os.str());
}