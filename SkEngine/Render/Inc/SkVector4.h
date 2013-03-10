#pragma once

#include "SkVector3.h"

namespace ske
{
	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vector4()
		{}

		Vector4(float x_, float y_, float z_, float w_)
		: x(x_), y(y_), z(z_), w(w_)
		{}

		Vector4(const Vector3& rhs, float w_)
		: x(rhs.x), y(rhs.y), z(rhs.z), w(w_)
		{
		}

		static float Dot(const Vector4& lhs, const Vector4& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		Vector4 operator+(const Vector4& other) const
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		friend Vector4 operator*(float scalar, const Vector4& v)
		{
			return Vector4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
		}

		bool operator==(const Vector4& other) const
		{
			return (x == other.x &&	y == other.y &&	z == other.z && w == other.w);
		}

		bool operator!=(const Vector4& other) const
		{
			return (x != other.x || y != other.y || z != other.z || w != other.w);
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector4& v)
		{
			os << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return os;
		}

		// Special vectors
		static const Vector4 Zero;
	};
}