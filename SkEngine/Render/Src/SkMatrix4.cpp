#include "Pch.h"
#include "SkMatrix4.h"

namespace ske
{
	const Matrix4 Matrix4::Zero(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	const Matrix4 Matrix4::Identity(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4::Matrix4()
	{
		// No matrix initialization for efficiency
	}
}