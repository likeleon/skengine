#include "Pch.h"
#include "SkD3DEffect.h"
#include "CommonFixtures.h"
#include "SkVector4.h"
#include "SkTexture.h"

using namespace ske;

class D3DEffectTest : public RendererCreation 
{
protected:
	bool CreateEffect(D3DEffect& effect, const std::wstring& fxFile = L"../../Media/Shaders/Simple.fx")
	{
		return effect.Create(renderer.GetDevice(), fxFile);
	}
};


TEST_F(D3DEffectTest, CreateDestroyTest)
{
	D3DEffect effect;
	EXPECT_FALSE(effect.IsCreated());

	EXPECT_TRUE(CreateEffect(effect));
	EXPECT_FALSE(CreateEffect(effect));	// Create again fails
	EXPECT_TRUE(effect.IsCreated());
		
	effect.Destroy();
	EXPECT_FALSE(effect.IsCreated());
}

TEST_F(D3DEffectTest, CreateFailTest)
{
	D3DEffect effect;
	EXPECT_FALSE(CreateEffect(effect, L"./NonExistingFile.fx"));
}

TEST_F(D3DEffectTest, SetTechniqueTest)
{
	const std::string techName = "RenderTechnique";

	D3DEffect effect;
	EXPECT_FALSE(effect.SetTechnique(techName));	// not created

	CreateEffect(effect);
	EXPECT_TRUE(effect.SetTechnique(techName));
	EXPECT_TRUE(effect.SetTechnique(techName));
}

TEST_F(D3DEffectTest, BeginTest)
{
	unsigned int numPass = 0;

	D3DEffect effect;
	EXPECT_FALSE(effect.Begin(numPass));	// not created

	CreateEffect(effect);
	EXPECT_TRUE(effect.Begin(numPass));
	EXPECT_FALSE(effect.Begin(numPass));
}

TEST_F(D3DEffectTest, EndTest)
{
	D3DEffect effect;
	EXPECT_FALSE(effect.End());	// not created, not begun

	CreateEffect(effect);
	EXPECT_FALSE(effect.End());	// not begun

	unsigned int numPass;
	effect.Begin(numPass);
	EXPECT_TRUE(effect.End());
	EXPECT_FALSE(effect.End());	// not begun
}

TEST_F(D3DEffectTest, BeginEndPassTest)
{
	D3DEffect effect;
	EXPECT_FALSE(effect.BeginPass(0));
	EXPECT_FALSE(effect.EndPass());

	CreateEffect(effect);
	EXPECT_FALSE(effect.BeginPass(0));
	EXPECT_FALSE(effect.EndPass());

	unsigned int numPass;
	effect.Begin(numPass);
	for (unsigned int pass = 0; pass < numPass; ++pass)
	{
		EXPECT_FALSE(effect.EndPass());
		EXPECT_TRUE(effect.BeginPass(pass));
		EXPECT_FALSE(effect.BeginPass(pass));
		EXPECT_TRUE(effect.EndPass());
	}
	EXPECT_FALSE(effect.BeginPass(numPass));
}

TEST_F(D3DEffectTest, GetParameterTest)
{
	D3DEffect effect;
	EXPECT_TRUE(nullptr == effect.GetParameter("gWorldXf"));

	CreateEffect(effect);
	D3DEffect::Parameter* param = effect.GetParameter("gWorldXf");
	EXPECT_TRUE(nullptr != param);
	EXPECT_TRUE(nullptr == effect.GetParameter("nonExistingParam"));

	// Fail if effect destroyed
	effect.Destroy();
	EXPECT_TRUE(nullptr == effect.GetParameter("gWorldXf"));
}

TEST_F(D3DEffectTest, SetMatrix4ParameterTest)
{
	D3DEffect effect;
	CreateEffect(effect);
	D3DEffect::Parameter* const param = effect.GetParameter("gWorldXf");
	EXPECT_TRUE(param->SetValue(Matrix4::Identity));
}

TEST_F(D3DEffectTest, SetVector4ParameterTest)
{
	D3DEffect effect;
	CreateEffect(effect);
	D3DEffect::Parameter* const param = effect.GetParameter("gLamp0Color");
	EXPECT_TRUE(param->SetValue(Vector4::Zero));
}

TEST_F(D3DEffectTest, SetTextureParameterTest)
{
	D3DEffect effect;
	CreateEffect(effect);
	D3DEffect::Parameter* const param = effect.GetParameter("gTexture");
	
	Texture texture;
	texture.CreateFromFile(renderer.GetDevice(), L"../../Media/Textures/Default_color.dds");
	EXPECT_TRUE(param->SetValue(texture));
}
