#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SkNonCopyable.h"

namespace ske
{
	class Camera;
	class IRenderable;

	class D3D9Device : private NonCopyable
	{
	public:
		D3D9Device();
		~D3D9Device();

		bool Create(HWND hWnd);
		void Destroy();
		bool IsCreated() const;

		enum CullMode
		{
			Cull_None				= D3DCULL_NONE,
			Cull_ClockWise			= D3DCULL_CW,
			Cull_CounterClockWise	= D3DCULL_CCW,
			Cull_Max
		};
		bool SetCullMode(CullMode mode);

		enum DepthBufferMode
		{
			Depth_Disable			= D3DZB_FALSE,
			Depth_ZBuffer			= D3DZB_TRUE,
			Depth_WBuffer			= D3DZB_USEW,
			Depth_Max
		};
		bool SetDepthBufferMode(DepthBufferMode mode);

		// Simple Direct3DDevice9 wrapping functions
		bool CreateEffectFromFile(const std::wstring& srcFile,
								  LPD3DXEFFECT *ppEffect);
		bool CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements,
									 IDirect3DVertexDeclaration9 **ppDecl);
		bool CreateVertexBuffer(unsigned int length, 
								IDirect3DVertexBuffer9 **ppVertexBuffer);
		bool CreateIndexBuffer(unsigned int length, IDirect3DIndexBuffer9 **ppIndexBuffer);
		bool CreateFont(int height, 
						const std::wstring& faceName, 
						LPD3DXFONT *ppFont);
		bool CreateTextureFromFile(const std::wstring& srcFile,
								   LPDIRECT3DTEXTURE9 *ppTexture);
		bool LoadMeshFromX(const std::wstring& fileName, LPD3DXBUFFER *ppMaterials, DWORD *pNumMaterials, LPD3DXMESH *ppMesh);

		bool Clear();
		bool BeginScene();
		bool EndScene();
		bool Present();

		bool SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl);
		bool SetStreamSource(IDirect3DVertexBuffer9 *pStreamData, unsigned int stride);
		bool SetIndices(IDirect3DIndexBuffer9* pIndexData);
		bool DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int primitiveCount);
		bool DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, 
								  unsigned int numVertices, 
								  unsigned int startIndex,
								  unsigned int primitiveCount);

	private:
		LPDIRECT3D9 m_d3d;
		LPDIRECT3DDEVICE9 m_d3dDevice;
		bool m_beginScene;
	};
}
