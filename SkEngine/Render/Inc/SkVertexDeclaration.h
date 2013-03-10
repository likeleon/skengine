#pragma once

#include <vector>
#include <d3d9.h>
#include "SkNonCopyable.h"
#include "SkIntrusivePtr.h"

namespace ske
{
	class D3D9Device;

	class VertexDeclaration : public IntrusiveSharedObject<size_t>, private NonCopyable
	{
	public:
		VertexDeclaration();
		virtual ~VertexDeclaration();

		bool AddVertexElement(WORD stream, WORD offset, BYTE type, BYTE method, BYTE usage, BYTE usageIndex);
		bool Create(D3D9Device& device);
		void Destroy();
		bool IsCreated() const;

		LPDIRECT3DVERTEXDECLARATION9 GetD3DDecl() { return m_vdecl; }

	private:

		typedef std::vector<D3DVERTEXELEMENT9> VertexLayout;
		VertexLayout m_vlayout;
		
		LPDIRECT3DVERTEXDECLARATION9 m_vdecl;
	};

	typedef IntrusivePtr<VertexDeclaration> VertexDeclarationPtr;
}