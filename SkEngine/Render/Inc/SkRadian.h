#pragma once

#include <ostream>

namespace ske
{
	class Radian
	{
	public:
		explicit Radian(float rad = 0.0f)
		: m_radian(rad)
		{}

		Radian(const Radian& r)
		{
			m_radian = r.m_radian;
		}

		Radian& operator=(const Radian& r)
		{
			if (&r == this)
				return *this;
			m_radian = r.m_radian;
			return *this;
		}

		float GetRadian() const { return m_radian; }

		const Radian& operator+() const { return *this; }
		Radian operator+(const Radian& r) const { return Radian(m_radian + r.m_radian); }
		Radian& operator+=(const Radian& r) { m_radian += r.m_radian; return *this; }
		Radian operator-() const { return Radian(-m_radian); }
		Radian operator-(const Radian& r) const { return Radian(m_radian - r.m_radian); }
		Radian& operator-=(const Radian& r) { m_radian -= r.m_radian; return *this; }
		Radian operator*(float scalar) const { return Radian(m_radian * scalar); }
		friend Radian operator*(float scalar, const Radian& r) { return Radian(scalar * r.m_radian); } 
		Radian operator*(const Radian& r) const { return Radian(m_radian * r.m_radian); }
		Radian& operator*=(float scalar) { m_radian *= scalar; return *this; }
		Radian operator/(float scalar) const { return Radian(m_radian / scalar); }
		Radian& operator/=(float scalar) { m_radian /= scalar; return *this; }

		bool operator<(const Radian& r)	const  { return m_radian <  r.m_radian; }
		bool operator<=(const Radian& r) const { return m_radian <= r.m_radian; }
		bool operator==(const Radian& r) const { return m_radian == r.m_radian; }
		bool operator!=(const Radian& r) const { return m_radian != r.m_radian; }
		bool operator>=(const Radian& r) const { return m_radian >= r.m_radian; }
		bool operator>(const Radian& r) const  { return m_radian >  r.m_radian; }

		inline friend std::ostream& operator<<(std::ostream& os, const Radian& r)
		{
			os << "Radian(" << r.GetRadian() << ")";
			return os;
		}

	private:
		float m_radian;
	};
}