#include "Pch.h"
#include "SkD3DMapping.h"
#include "SkMatrix4.h"
#include "SkVector4.h"

using namespace ske;

TEST(D3DMappingTest, MatrixTest)
{
	const Matrix4 m(0,  4,  8, 12,
					1,  5,  9, 13,
					2,  6, 10, 14,
					3,  7, 11, 15);
	D3DXMATRIXA16 d3dm;
	D3DMapping::ToD3DXMatrixA16(m, d3dm);

	// D3D9 and we use column vectors
	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t col = 0; col < 4; ++col)
		{
			EXPECT_EQ(m[row][col], d3dm.m[row][col]);
		}
	}

	Matrix4 m2;
	D3DMapping::ToMatrix4(d3dm, m2);
	EXPECT_EQ(m, m2);
}

TEST(D3DMappingTest, Vector4Test)
{
	const Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);
	D3DXVECTOR4 d3dv;
	D3DMapping::ToD3DXVector4(v, d3dv);

	EXPECT_EQ(v.x, d3dv.x);
	EXPECT_EQ(v.y, d3dv.y);
	EXPECT_EQ(v.z, d3dv.z);
	EXPECT_EQ(v.w, d3dv.w);
}