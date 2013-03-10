#include "Pch.h"
#include "SkD3DMapping.h"
#include "SkMatrix4.h"
#include "SkVector4.h"

namespace ske
{
	void D3DMapping::ToD3DXMatrixA16(const Matrix4& m, D3DXMATRIXA16& out)
	{
		out.m[0][0] = m[0][0]; 
		out.m[0][1] = m[0][1]; 
		out.m[0][2] = m[0][2]; 
		out.m[0][3] = m[0][3];
		
		out.m[1][0] = m[1][0]; 
		out.m[1][1] = m[1][1]; 
		out.m[1][2] = m[1][2];
		out.m[1][3] = m[1][3];
		
		out.m[2][0] = m[2][0]; 
		out.m[2][1] = m[2][1]; 
		out.m[2][2] = m[2][2];
		out.m[2][3] = m[2][3];
		
		out.m[3][0] = m[3][0]; 
		out.m[3][1] = m[3][1]; 
		out.m[3][2] = m[3][2];
		out.m[3][3] = m[3][3];
	}

	void D3DMapping::ToMatrix4(const D3DXMATRIXA16& d3dxm, Matrix4& out)
	{
		out[0][0] = d3dxm.m[0][0];
		out[0][1] = d3dxm.m[0][1];
		out[0][2] = d3dxm.m[0][2];
		out[0][3] = d3dxm.m[0][3];

		out[1][0] = d3dxm.m[1][0]; 
		out[1][1] = d3dxm.m[1][1]; 
		out[1][2] = d3dxm.m[1][2];
		out[1][3] = d3dxm.m[1][3];
		
		out[2][0] = d3dxm.m[2][0]; 
		out[2][1] = d3dxm.m[2][1]; 
		out[2][2] = d3dxm.m[2][2];
		out[2][3] = d3dxm.m[2][3];
		
		out[3][0] = d3dxm.m[3][0]; 
		out[3][1] = d3dxm.m[3][1]; 
		out[3][2] = d3dxm.m[3][2];
		out[3][3] = d3dxm.m[3][3];
	}

	void D3DMapping::ToD3DXVector4(const Vector4& v, D3DXVECTOR4& out)
	{
		out.x = v.x;
		out.y = v.y;
		out.z = v.z;
		out.w = v.w;
	}
}
