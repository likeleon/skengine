#pragma once

#include "SkNonCopyable.h"
#include "SkVector3.h"
#include "SkMatrix4.h"
#include "SkRadian.h"

namespace ske
{
	class Camera : private NonCopyable
	{
	public:
		Camera();

		// View matrix
		void SetEyePos(const Vector3& eyePos);
		const Vector3& GetEyePos() const { return m_eyePos; }

		void SetLookAt(const Vector3& lookAtPos);
		const Vector3& GetLookAt() const { return m_lookAtPos; }

		void SetUpVec(const Vector3& upVec);
		const Vector3& GetUpVec() const { return m_upVec; }

		const Matrix4& GetViewMatrix() const;

		// Projection matrix
		bool SetFovY(const Radian& fovY);
		const Radian& GetFovY() const { return m_fovY; }

		bool SetAspectRatio(float aspect);
		float GetAspectRatio() const { return m_aspectRatio; }

		bool SetPlaneDistance(float nearDistance, float farDistance);
		float GetNearPlaneDistance() const { return m_nearPlaneDistance; }
		float GetFarPlaneDistance() const { return m_farPlaneDistance; }

		const Matrix4& GetProjectionMatrix() const;

	private:
		Vector3 m_eyePos;
		Vector3 m_lookAtPos;
		Vector3 m_upVec;
		mutable bool	m_viewMatIsDirty;
		mutable Matrix4 m_viewMat;

		Radian	m_fovY;
		float	m_aspectRatio;
		float	m_nearPlaneDistance;
		float	m_farPlaneDistance;
		mutable bool	m_projMatIsDirty;
		mutable Matrix4 m_projMat;
	};
}