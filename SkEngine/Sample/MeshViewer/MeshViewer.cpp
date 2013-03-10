#include <Windows.h>
#include <cassert>
#include "SkFramework.h"
#include "SkManualRenderable.h"
#include "SkCamera.h"
#include "SkMath.h"
#include "SkLambertShader.h"
#include "SkMesh.h"
#include "SkUtilities.h"
#include "SkTextureManager.h"

using namespace ske;

static IRenderable* CreateCylinder(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr);
static IRenderable* CreateBox(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr);
static IRenderable* CreateMesh(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr);

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	(void)hInst;

	Framework framework;
	
	if (!framework.Init(L"Mesh Viewer", 640, 480, true))
		return -1;

	TextureManager* const textureMgr = framework.GetTextureManager();
	SK_ASSERT(textureMgr);

	ShaderManager* const shaderMgr = framework.GetShaderManager();
	SK_ASSERT(shaderMgr);

	IRenderable* const cylinder = CreateCylinder(framework.GetRenderer().GetDevice(), *textureMgr, *shaderMgr);
	if (!cylinder)
	{
		MessageBox(nullptr, L"Failed create Cylinder", L"Error", MB_ICONERROR);
		return -1;
	}
	//framework.GetRenderer().AddRenderable(*cylinder);

	IRenderable* const box = CreateBox(framework.GetRenderer().GetDevice(), *textureMgr, *shaderMgr);
	if (!box)
	{
		MessageBox(nullptr, L"Failed create Box", L"Error", MB_ICONERROR);
		return -1;
	}
	//framework.GetRenderer().AddRenderable(*box);

	IRenderable* const mesh = CreateMesh(framework.GetRenderer().GetDevice(), *textureMgr, *shaderMgr);
	if (!mesh)
	{
		MessageBox(nullptr, L"Failed create Mesh", L"Error", MB_ICONERROR);
		return -1;
	}
	framework.GetRenderer().AddRenderable(*mesh);

	// Configure camera
	Camera& camera = framework.GetCamera();
	camera.SetEyePos(Vector3(0.0f, 3.0f, -5.0f));
	camera.SetLookAt(Vector3::Zero);
	camera.SetUpVec(Vector3::UnitY);
	camera.SetFovY(Radian(Math::PI / 4));
	camera.SetAspectRatio(1.0f);
	camera.SetPlaneDistance(1.0f, 100.0f);

	bool quit = false;
	do
	{
		framework.Advance(quit);
	} while (!quit);
	framework.Cleanup();
	return 0;
}

IRenderable* CreateCylinder(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr)
{
	TexturePtr texture = textureMgr.Load(L"../../Media/Textures/Default_color.dds");
	if (!texture)
		return nullptr;
	
	// Create ManualRenderable instance
	ManualRenderable* const manual = new ManualRenderable(shaderMgr.GetLambertShader(), texture);
	typedef MeshVertex::Position Position;
	typedef MeshVertex::UV UV;
	typedef MeshVertex::Normal Normal;

	for (int i = 0; i < 50; ++i)
	{
		const float theta = (2 * D3DX_PI * i) / (50 - 1);
		manual->AddVertex(
			Position(sinf(theta), -1.0f, cosf(theta)),
			UV(static_cast<float>(i) / 49, 0.0f),
			Normal(sinf(theta), 0.0f, cosf(theta)));
		manual->AddVertex(
			Position(sinf(theta), 1.0f, cosf(theta)),
			UV(static_cast<float>(i) / 49, 1.0f),
			Normal(sinf(theta), 0.0f, cosf(theta)));
	}

	if (!manual->Create(device))
		goto LOCAL_EXIT_FAIL;
	
	return manual;

LOCAL_EXIT_FAIL:
	delete manual;
	return nullptr;
}

IRenderable* CreateBox(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr)
{
	TexturePtr texture = textureMgr.Load(L"../../Media/Textures/Default_color.dds");
	if (!texture)
		return nullptr;

	// Create ManualRenderable instance (with indices)
	ManualRenderable* const manual = new ManualRenderable(shaderMgr.GetLambertShader(), texture);
	typedef MeshVertex::Position Position;
	typedef MeshVertex::UV UV;
	typedef MeshVertex::Normal Normal;

	static const MeshVertex vertices[] = 
	{
		MeshVertex(Position(-1, 1, 1), UV(0, 0), Normal(Vector3::UnitZ)),
		MeshVertex(Position(1, 1, 1), UV(1, 0), Normal(Vector3::UnitZ)),
		MeshVertex(Position(1, 1, -1), UV(1, 1), -Normal(Vector3::UnitZ)),
		MeshVertex(Position(-1, 1, -1), UV(0, 1), -Normal(Vector3::UnitZ)),
		MeshVertex(Position(-1, -1, 1), UV(0, 0), Normal(Vector3::UnitZ)),
		MeshVertex(Position(1, -1, 1), UV(1, 0), Normal(Vector3::UnitZ)),
		MeshVertex(Position(1, -1, -1), UV(1, 1), -Normal(Vector3::UnitZ)),
		MeshVertex(Position(-1, -1, -1), UV(0, 1), -Normal(Vector3::UnitZ)),
	};
	for (size_t i = 0; i < ArrSize(vertices); ++i)
	{
		manual->AddVertex(vertices[i]);
	}

	struct TriangleIndex
	{
		short i0;
		short i1;
		short i2;
	};
	static const TriangleIndex indices[] = 
	{
		{ 0, 1, 2 }, { 0, 2, 3 },	// top
		{ 4, 6, 5 }, { 4, 7, 6 },	// bottom
		{ 0, 3, 7 }, { 0, 7, 4 },	// left
		{ 1, 5, 6 }, { 1, 6, 2 },	// right
		{ 3, 2, 6 }, { 3, 6, 7 },	// front
		{ 0, 4, 5 }, { 0, 5, 1 }	// back
	};
	for (size_t i = 0; i < ArrSize(indices); ++i)
	{
		manual->AddIndex(indices[i].i0, indices[i].i1, indices[i].i2);
	}

	if (!manual->Create(device))
		goto LOCAL_EXIT_FAIL;
	
	return manual;

LOCAL_EXIT_FAIL:
	delete manual;
	return nullptr;
}


IRenderable* CreateMesh(D3D9Device& device, TextureManager& textureMgr, ShaderManager& shaderMgr)
{
	Mesh* const mesh = new Mesh(shaderMgr.GetLambertShader());
	if (!mesh->CreateFromXFile(device, textureMgr, L"../../Media/Models/tiger.x"))
	{
		delete mesh;
		return nullptr;
	}

	return mesh;
}
