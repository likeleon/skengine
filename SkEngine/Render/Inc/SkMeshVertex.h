#pragma once

#include "SkVector3.h"
#include "SkVector2.h"
#include "SkVertexDeclaration.h"

namespace ske
{
	class D3D9Device;

	class MeshVertex
	{
	public:
		typedef Vector3 Position;
		typedef Vector2 UV;
		typedef Vector3 Normal; 

		MeshVertex(const Position& pos_, const UV& uv_, const Normal& normal_)
			: pos(pos_), uv(uv_), normal(normal_) {}

		Position pos;
		UV uv;
		Normal normal;

	public:
		static VertexDeclarationPtr CreateDeclaration(D3D9Device& device);
		static const size_t VertexSize;
	};
}