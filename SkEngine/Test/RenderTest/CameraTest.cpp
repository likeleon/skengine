#include "Pch.h"
#include "SkCamera.h"
#include "SkVector3.h"
#include "SkMath.h"

using namespace ske;

TEST(CameraTest, PositionTest)
{
	Camera camera;
	EXPECT_EQ(Vector3::Zero, camera.GetEyePos());

	const Vector3 pos(1.0f, 2.0f, 3.0f);
	camera.SetEyePos(pos);
	EXPECT_EQ(pos, camera.GetEyePos());
}

TEST(CameraTest, LookAtTest)
{
	Camera camera;
	EXPECT_EQ(Vector3::Zero, camera.GetLookAt());

	const Vector3 lookAtPos(1.0f, 2.0f, 3.0f);
	camera.SetLookAt(lookAtPos);
	EXPECT_EQ(lookAtPos, camera.GetLookAt());
}

TEST(CameraTest, UpVecTest)
{
	Camera camera;
	EXPECT_EQ(Vector3::UnitY, camera.GetUpVec());

	const Vector3 upVec(1.0f, 3.0f, 3.0f);
	camera.SetUpVec(upVec);
	EXPECT_EQ(upVec, camera.GetUpVec());
}

TEST(CameraTest, GetViewMatrixTest)
{
	Camera camera;
	camera.SetEyePos(Vector3(1.0f, 2.0f, 3.0f));
	camera.SetLookAt(Vector3(0.0f, 0.0f, 0.0f));
	camera.SetUpVec(Vector3(2.0f, 3.0f, 4.0f));
	
	const Vector3 zaxis = Vector3::Normalize(camera.GetLookAt() - camera.GetEyePos());
	const Vector3 xaxis = Vector3::Normalize(Vector3::Cross(camera.GetUpVec(), zaxis));
	const Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
	const Vector4 col0(xaxis, -Vector3::Dot(xaxis, camera.GetEyePos()));
	const Vector4 col1(yaxis, -Vector3::Dot(yaxis, camera.GetEyePos()));
	const Vector4 col2(zaxis, -Vector3::Dot(zaxis, camera.GetEyePos()));
	const Matrix4 expected(col0, col1, col2, Vector4(0, 0, 0, 1));
	
	EXPECT_EQ(expected, camera.GetViewMatrix());
}

TEST(CameraTest, FovYTest)
{
	Camera camera;
	EXPECT_EQ(Radian(Math::PI / 4.0f), camera.GetFovY());

	EXPECT_TRUE(camera.SetFovY(Radian(2.0f)));
	EXPECT_EQ(Radian(2.0f), camera.GetFovY());

	// FieldOfView is between 0 and pi (180 degrees)
	EXPECT_TRUE(camera.SetFovY(Radian(0.0f)));
	EXPECT_FALSE(camera.SetFovY(Radian(-0.1f)));
	EXPECT_TRUE(camera.SetFovY(Radian(Math::PI)));
	EXPECT_FALSE(camera.SetFovY(Radian(Math::PI * 1.1f)));
}

TEST(CameraTest, AspectRatioTest)
{
	Camera camera;
	EXPECT_EQ(1.0f / 3, camera.GetAspectRatio());

	EXPECT_TRUE(camera.SetAspectRatio(800 / 600));
	EXPECT_EQ(800 / 600, camera.GetAspectRatio());

	EXPECT_FALSE(camera.SetAspectRatio(0.0f));
	EXPECT_FALSE(camera.SetAspectRatio(-1.0f));
}

TEST(CameraTest, PlaneDistanceTest)
{
	Camera camera;
	EXPECT_EQ(100.0f, camera.GetNearPlaneDistance());
	EXPECT_EQ(100000.0f, camera.GetFarPlaneDistance());

	EXPECT_TRUE(camera.SetPlaneDistance(200.0f, 50000.0f));
	EXPECT_EQ(200.0f, camera.GetNearPlaneDistance());
	EXPECT_EQ(50000.0f, camera.GetFarPlaneDistance());

	// NearPlaneDistance and FarPlaneDistance should be positive value
	EXPECT_FALSE(camera.SetPlaneDistance(0.0f, 100.0f));
	EXPECT_FALSE(camera.SetPlaneDistance(-200.0f, 100.0f));
	EXPECT_FALSE(camera.SetPlaneDistance(-100.0f, 0.0f));
	EXPECT_FALSE(camera.SetPlaneDistance(-200.0f, -100.0f));

	// FarPlaneDistance should be larger than NearPlaneDistance
	EXPECT_FALSE(camera.SetPlaneDistance(200.0f, 100.0f));
	EXPECT_FALSE(camera.SetPlaneDistance(100.0f, 100.0f));
}

TEST(CameraTest, GetProjectionMatrixTest)
{
	Camera camera;
	const Matrix4 projMat = camera.GetProjectionMatrix();

	// FovY change -> Projection matrix change
	const Radian oldFovY = camera.GetFovY();
	camera.SetFovY(oldFovY / 2);
	EXPECT_NE(projMat, camera.GetProjectionMatrix());
	camera.SetFovY(oldFovY);	// restore
	EXPECT_EQ(projMat, camera.GetProjectionMatrix());

	// Aspect ratio change -> Projection matrix change
	const float oldAspect = camera.GetAspectRatio();
	camera.SetAspectRatio(oldAspect * 2);
	EXPECT_NE(projMat, camera.GetProjectionMatrix());
	camera.SetAspectRatio(oldAspect);	// restore
	EXPECT_EQ(projMat, camera.GetProjectionMatrix());

	// Plane distance change -> Projection matrix change
	const float oldNearDistance = camera.GetNearPlaneDistance();
	const float oldFarDistance = camera.GetFarPlaneDistance();
	camera.SetPlaneDistance(oldNearDistance * 2, oldFarDistance * 2);
	EXPECT_NE(projMat, camera.GetProjectionMatrix());
	camera.SetPlaneDistance(oldNearDistance, oldFarDistance);	// restore
	EXPECT_EQ(projMat, camera.GetProjectionMatrix());
}