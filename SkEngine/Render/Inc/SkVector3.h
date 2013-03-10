#pragma once

#include "SkAssert.h"

namespace ske
{
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3()
		{}

		Vector3(float x_, float y_, float z_)
		: x(x_), y(y_), z(z_)
		{}

		float Length() const
		{
			return std::sqrt(SquaredLength());
		}

		float SquaredLength() const
		{
			return x * x + y * y + z * z;
		}

		void Normalize()
		{
			if (Length() <= 0.0f)
				return;

			const float inv = 1.0f / Length();
			if (inv > 0.0f)
			{
				x *= inv;
				y *= inv;
				z *= inv;
			}
		}

		static Vector3 Normalize(const Vector3& v)
		{
			Vector3 ret(v);
			ret.Normalize();
			return ret;
		}

		static float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x);
		}

		Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		Vector3& operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3 operator+(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3& operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3 operator-(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3 operator*(float scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		friend Vector3 operator*(float scalar, const Vector3& v)
		{
			return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
		}

		Vector3& operator/=(float scalar)
		{
			SK_REQUIRE(scalar != 0.0f);
			
			const float inv = 1.0f / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			
			return *this;
		}

		Vector3 operator/(float scalar) const
		{
			SK_REQUIRE(scalar != 0.0f);
			const float inv = 1.0f / scalar;
			return Vector3(x * inv, y * inv, z * inv);
		}

		bool operator==(const Vector3& other) const
		{
			return (x == other.x &&	y == other.y &&	z == other.z);
		}

		bool operator!=(const Vector3& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

		Vector3& operator=(const Vector3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
		{
			os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
			return os;
		}

		// Special vectors
		static const Vector3 Zero;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
	};
}
