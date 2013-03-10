#pragma once

#include "SkAssert.h"
#include "SkMath.h"
#include "SkVector4.h"

// Use "row vector convention"
//   v' = (((vA)B)C)

namespace ske
{
	class Matrix4
	{
	public:
		Matrix4();

		Matrix4(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		Matrix4(const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3)
		{
			m[0][0] = col0.x;
			m[0][1] = col1.x;
			m[0][2] = col2.x;
			m[0][3] = col3.x;
			m[1][0] = col0.y;
			m[1][1] = col1.y;
			m[1][2] = col2.y;
			m[1][3] = col3.y;
			m[2][0] = col0.z;
			m[2][1] = col1.z;
			m[2][2] = col2.z;
			m[2][3] = col3.z;
			m[3][0] = col0.w;
			m[3][1] = col1.w;
			m[3][2] = col2.w;
			m[3][3] = col3.w;
		}

		float* operator[](size_t row)
		{
			SK_REQUIRE(row < 4);
			return m[row];
		}

		const float* operator[](size_t row) const
		{
			SK_REQUIRE(row < 4);
			return m[row];
		}

		bool operator==(const Matrix4& other) const
		{
			if (m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] || m[0][2] != other.m[0][2] || m[0][3] != other.m[0][3] ||
				m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] || m[1][2] != other.m[1][2] || m[1][3] != other.m[1][3] ||
				m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] || m[2][2] != other.m[2][2] || m[2][3] != other.m[2][3] ||
				m[3][0] != other.m[3][0] || m[3][1] != other.m[3][1] || m[3][2] != other.m[3][2] || m[3][3] != other.m[3][3])
			{
				return false;
			}
			return true;
		}

		bool operator!=(const Matrix4& other) const
		{
			if (m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] || m[0][2] != other.m[0][2] || m[0][3] != other.m[0][3] ||
				m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] || m[1][2] != other.m[1][2] || m[1][3] != other.m[1][3] ||
				m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] || m[2][2] != other.m[2][2] || m[2][3] != other.m[2][3] ||
				m[3][0] != other.m[3][0] || m[3][1] != other.m[3][1] || m[3][2] != other.m[3][2] || m[3][3] != other.m[3][3])
			{
				return true;
			}
			return false;
		}

		Matrix4 operator*(const Matrix4& other) const
		{
			Matrix4 result;

			result[0][0] = m[0][0] * other[0][0] + m[0][1] * other[1][0] + m[0][2] * other[2][0] + m[0][3] * other[3][0];
			result[0][1] = m[0][0] * other[0][1] + m[0][1] * other[1][1] + m[0][2] * other[2][1] + m[0][3] * other[3][1];
			result[0][2] = m[0][0] * other[0][2] + m[0][1] * other[1][2] + m[0][2] * other[2][2] + m[0][3] * other[3][2];
			result[0][3] = m[0][0] * other[0][3] + m[0][1] * other[1][3] + m[0][2] * other[2][3] + m[0][3] * other[3][3];

			result[1][0] = m[1][0] * other[0][0] + m[1][1] * other[1][0] + m[1][2] * other[2][0] + m[1][3] * other[3][0];
			result[1][1] = m[1][0] * other[0][1] + m[1][1] * other[1][1] + m[1][2] * other[2][1] + m[1][3] * other[3][1];
			result[1][2] = m[1][0] * other[0][2] + m[1][1] * other[1][2] + m[1][2] * other[2][2] + m[1][3] * other[3][2];
			result[1][3] = m[1][0] * other[0][3] + m[1][1] * other[1][3] + m[1][2] * other[2][3] + m[1][3] * other[3][3];

			result[2][0] = m[2][0] * other[0][0] + m[2][1] * other[1][0] + m[2][2] * other[2][0] + m[2][3] * other[3][0];
			result[2][1] = m[2][0] * other[0][1] + m[2][1] * other[1][1] + m[2][2] * other[2][1] + m[2][3] * other[3][1];
			result[2][2] = m[2][0] * other[0][2] + m[2][1] * other[1][2] + m[2][2] * other[2][2] + m[2][3] * other[3][2];
			result[2][3] = m[2][0] * other[0][3] + m[2][1] * other[1][3] + m[2][2] * other[2][3] + m[2][3] * other[3][3];

			result[3][0] = m[3][0] * other[0][0] + m[3][1] * other[1][0] + m[3][2] * other[2][0] + m[3][3] * other[3][0];
			result[3][1] = m[3][0] * other[0][1] + m[3][1] * other[1][1] + m[3][2] * other[2][1] + m[3][3] * other[3][1];
			result[3][2] = m[3][0] * other[0][2] + m[3][1] * other[1][2] + m[3][2] * other[2][2] + m[3][3] * other[3][2];
			result[3][3] = m[3][0] * other[0][3] + m[3][1] * other[1][3] + m[3][2] * other[2][3] + m[3][3] * other[3][3];

			return result;
		}

		inline friend std::ostream& operator<<(std::ostream& os, const Matrix4& m)
		{
			os << "Matrix4(";
			for (size_t col = 0; col < 4; ++col)
            {
                os << " col" << col << "{";
                for(size_t row = 0; row < 4; ++row)
                {
                    os << m[row][col] << " ";
                }
                os << "}";
            }
            os << ")";
            return os;
		}

		void Transpose(Matrix4& result) const
		{
			result[0][0] = m[0][0]; result[0][1] = m[1][0]; result[0][2] = m[2][0]; result[0][3] = m[3][0];
			result[1][0] = m[0][1]; result[1][1] = m[1][1]; result[1][2] = m[2][1]; result[1][3] = m[3][1];
			result[2][0] = m[0][2]; result[2][1] = m[1][2]; result[2][2] = m[2][2]; result[2][3] = m[3][2];
			result[3][0] = m[0][3]; result[3][1] = m[1][3]; result[3][2] = m[2][3]; result[3][3] = m[3][3];
		}

		Matrix4 Transpose() const
		{
			Matrix4 result;
			Transpose(result);
			return result;
		}

		bool Invert(Matrix4& result) const
		{
			const float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
			const float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
			const float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
			const float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

			float v0 = m20 * m31 - m21 * m30;
			float v1 = m20 * m32 - m22 * m30;
			float v2 = m20 * m33 - m23 * m30;
			float v3 = m21 * m32 - m22 * m31;
			float v4 = m21 * m33 - m23 * m31;
			float v5 = m22 * m33 - m23 * m32;

			const float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
			const float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
			const float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
			const float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

			const float det = t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03;

			if (Math::IsNearZero(det, 1e-20f))
				return false;

			const float invDet = 1 / det;

			const float d00 = t00 * invDet;
			const float d10 = t10 * invDet;
			const float d20 = t20 * invDet;
			const float d30 = t30 * invDet;

			const float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			const float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			const float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			const float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m10 * m31 - m11 * m30;
			v1 = m10 * m32 - m12 * m30;
			v2 = m10 * m33 - m13 * m30;
			v3 = m11 * m32 - m12 * m31;
			v4 = m11 * m33 - m13 * m31;
			v5 = m12 * m33 - m13 * m32;

			const float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			const float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			const float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			const float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m21 * m10 - m20 * m11;
			v1 = m22 * m10 - m20 * m12;
			v2 = m23 * m10 - m20 * m13;
			v3 = m22 * m11 - m21 * m12;
			v4 = m23 * m11 - m21 * m13;
			v5 = m23 * m12 - m22 * m13;

			const float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			const float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			const float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			const float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			result[0][0] = d00; result[0][1] = d01; result[0][2] = d02; result[0][3] = d03;
			result[1][0] = d10; result[1][1] = d11; result[1][2] = d12; result[1][3] = d13;
			result[2][0] = d20; result[2][1] = d21; result[2][2] = d22; result[2][3] = d23;
			result[3][0] = d30; result[3][1] = d31; result[3][2] = d32; result[3][3] = d33;
	
			return true;
		}

		Matrix4 Invert() const
		{
			Matrix4 result;
			if (Invert(result))
				return result;
			return Matrix4::Identity;
		}
		
		static const Matrix4 Zero;
		static const Matrix4 Identity;

	private:
		float m[4][4];
	};
}