#include "Pch.h"
#include "SkD3D9Device.h"
#include "CommonFixtures.h"
#include "MockClasses.h"
#include "SkUtilities.h"

using namespace ske;

class DeviceTest : public WindowCreation 
{
protected:
	virtual void SetUp()
	{
		WindowCreation::SetUp();
	}

	virtual void TearDown()
	{
		WindowCreation::TearDown();
	}

	Camera camera;
};

TEST_F(DeviceTest, CreateDestroyTest)
{
	D3D9Device d3d9Device;
	EXPECT_FALSE(d3d9Device.IsCreated());

	EXPECT_TRUE(d3d9Device.Create(window.GetHandle()));
	EXPECT_FALSE(d3d9Device.Create(window.GetHandle()));
	EXPECT_TRUE(d3d9Device.IsCreated());

	d3d9Device.Destroy();
	d3d9Device.Destroy();	// repetition has no effect
	EXPECT_FALSE(d3d9Device.IsCreated());
}

TEST_F(DeviceTest, CreateFailTest)
{
	D3D9Device d3d9Device;
	EXPECT_FALSE(d3d9Device.Create(nullptr));
}

TEST_F(DeviceTest, CullModeTest)
{
	D3D9Device d3d9Device;
	d3d9Device.Create(window.GetHandle());

	for (int cullMode = D3D9Device::Cull_None; cullMode < D3D9Device::Cull_Max; ++cullMode)
	{
		EXPECT_TRUE(d3d9Device.SetCullMode(static_cast<D3D9Device::CullMode>(cullMode)));
	}
}

TEST_F(DeviceTest, DepthBufferModeTest)
{
	D3D9Device d3d9Device;
	d3d9Device.Create(window.GetHandle());

	for (int mode = D3D9Device::Depth_Disable; mode < D3D9Device::Depth_Max; ++mode)
	{
		EXPECT_TRUE(d3d9Device.SetDepthBufferMode(static_cast<D3D9Device::DepthBufferMode>(mode)));
	}
}