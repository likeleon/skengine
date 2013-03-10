#pragma once

#include "SkAssert.h"

namespace ske
{
	class Vector2
	{
	public:
		float x;
		float y;

	public:
		Vector2()
		{}

		Vector2(float x_, float y_)
		: x(x_), y(y_) 
		{}

		float Length() const
		{
			return std::sqrt(SquaredLength());
		}

		float SquaredLength() const
		{
			return x * x + y * y;
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
			}
		}

		static float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}

		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2 operator+(const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

	
		Vector2 operator*(float scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		friend Vector2 operator*(float scalar, const Vector2& other)
		{
			return Vector2(other.x * scalar, other.y * scalar);
		}

		Vector2& operator/=(float scalar)
		{
			SK_REQUIRE(scalar != 0.0f);
			
			const float inv = 1.0f / scalar;
			x *= inv;
			y *= inv;

			return *this;
		}

		Vector2 operator/(float scalar) const
		{
			SK_REQUIRE(scalar != 0.0f);
			const float inv = 1.0f / scalar;
			return Vector2(x * inv, y * inv);
		}

		bool operator==(const Vector2& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2& other) const
		{
			return (x != other.x || y != other.y);
		}

		Vector2& operator=(const Vector2& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
		{
			os << "Vector2(" << v.x << ", " << v.y << ")";
			return os;
		}
	};
}