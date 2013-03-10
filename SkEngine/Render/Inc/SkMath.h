#pragma once

namespace ske
{
	class Math
	{
	public:
		static const float PI;

		static bool IsNearZero(float val, float tolerance = 1e-6f)
		{
			return fabs(val) <= tolerance;
		}
	};
}