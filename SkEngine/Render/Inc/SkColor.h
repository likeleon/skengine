#pragma once

namespace ske
{
	class Color
	{
	public:
		float r;
		float g;
		float b;
		float a;

	public:
		explicit Color(float red = 1.0f, 
					   float green = 1.0f, 
					   float blue = 1.0f, 
					   float alpha = 1.0f);

		bool operator==(const Color& other) const
		{
			return (r == other.r && 
					g == other.g &&
					b == other.b &&
					a == other.a);
		}

		bool operator!=(const Color& other) const
		{
			return (r != other.r ||
					g != other.g ||
					b != other.b ||
					a != other.a);
		}

		friend std::ostream& operator<<(std::ostream& os, const Color& color)
		{
			os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
			return os;
		}
	};
}