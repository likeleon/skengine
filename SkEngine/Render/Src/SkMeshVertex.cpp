#include "Pch.h"
#include "SkMeshVertex.h"

namespace ske
{
	const size_t MeshVertex::VertexSize = sizeof(MeshVertex);
	SK_COMPILE_ASSERT(MeshVertex::VertexSize == sizeof(float) * 8)

	VertexDeclarationPtr MeshVertex::CreateDeclaration(D3D9Device& device)
	{
		VertexDeclaration* const decl = new VertexDeclaration();

		decl->AddVertexElement(0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		decl->AddVertexElement(0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		decl->AddVertexElement(0, 20, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		
		if (!decl->Create(device))
		{
			delete decl;
			return nullptr;
		}

		return decl;
	}
}
