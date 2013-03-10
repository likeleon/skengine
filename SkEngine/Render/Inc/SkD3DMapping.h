#pragma once

#include <d3dx9.h>

namespace ske
{
	class Matrix4;
	class Vector4;

	class D3DMapping
	{
	public:
		static void ToD3DXMatrixA16(const Matrix4& m, D3DXMATRIXA16& out);
		static void ToMatrix4(const D3DXMATRIXA16& d3dxm, Matrix4& out);
		static void ToD3DXVector4(const Vector4& v, D3DXVECTOR4& out);
	};
}