#pragma once

#include "SkIRenderable.h"
#include "SkMatrix4.h"
#include "SkShaderBase.h"

namespace ske
{
	class D3D9Device;
};

class RenderableMock : public ske::IRenderable
{
public:
	RenderableMock() : m_numRenderCalled(0) {}
		
	virtual bool Render()
	{ 
		++m_numRenderCalled;
		return true; 
	}

	virtual ske::ShaderBasePtr GetShader() 
	{ 
		return nullptr; 
	}

	virtual ske::TexturePtr GetTexture()
	{
		return nullptr;
	}
	
	virtual const ske::Matrix4& GetWorldMatrix()
	{
		return ske::Matrix4::Identity;
	}

	unsigned int m_numRenderCalled;
};

class ShaderMock : public ske::ShaderBase
{
public:
	bool Create(ske::D3D9Device &device, const std::wstring& effectFile)
	{
		return m_effect.Create(device, effectFile);
	}

private:
	virtual bool OnUpdateShaderParameters(unsigned int, ske::IRenderable&, const ske::Camera&) 
	{ 
		return true; 
	}
};

class ShaderRenderableMock : public RenderableMock
{
public:
	ShaderRenderableMock(ske::D3D9Device& device)
	{
		ShaderMock* const shader = new ShaderMock();
		shader->Create(device, L"../../Media/Shaders/Simple.fx");
		m_shader = shader;
	}

	~ShaderRenderableMock()
	{
		m_shader = nullptr;
	}

private:
	virtual ske::ShaderBasePtr GetShader()
	{
		return m_shader;
	}

	ske::ShaderBasePtr m_shader;
};
