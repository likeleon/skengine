#include "Pch.h"
#include "SkCamera.h"
#include "SkMath.h"
#include "SkD3DMapping.h"

namespace ske
{
	Camera::Camera()
	: m_eyePos(Vector3::Zero), 
	  m_lookAtPos(Vector3::Zero), 
	  m_upVec(Vector3::UnitY),
	  m_viewMatIsDirty(true),
	  m_fovY(Radian(Math::PI / 4.0f)),
	  m_aspectRatio(1.0f / 3),
	  m_nearPlaneDistance(100.0f),
	  m_farPlaneDistance(100000.0f),
	  m_projMatIsDirty(true)
	{
		SK_ENSURE(m_viewMatIsDirty);
		SK_ENSURE(m_projMatIsDirty);
	}

	void Camera::SetEyePos(const Vector3& eyePos)
	{
		if (m_eyePos == eyePos)
			return;
		m_eyePos = eyePos;
		m_viewMatIsDirty = true;
	}

	void Camera::SetLookAt(const Vector3& lookAtPos)
	{
		if (m_lookAtPos == lookAtPos)
			return;
		m_lookAtPos = lookAtPos;
		m_viewMatIsDirty = true;
	}

	void Camera::SetUpVec(const Vector3& upVec)
	{
		if (m_upVec == upVec)
			return;
		m_upVec = upVec;
		m_viewMatIsDirty = true;
	}

	const Matrix4& Camera::GetViewMatrix() const
	{
		if (m_viewMatIsDirty)
		{
			const Vector3 zaxis = Vector3::Normalize(m_lookAtPos - m_eyePos);
			const Vector3 xaxis = Vector3::Normalize(Vector3::Cross(m_upVec, zaxis));
			const Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

			m_viewMat[0][0] = xaxis.x;
			m_viewMat[1][0] = xaxis.y;
			m_viewMat[2][0] = xaxis.z;
			m_viewMat[3][0] = -Vector3::Dot(xaxis, m_eyePos);
			m_viewMat[0][1] = yaxis.x;
			m_viewMat[1][1] = yaxis.y;
			m_viewMat[2][1] = yaxis.z;
			m_viewMat[3][1] = -Vector3::Dot(yaxis, m_eyePos);
			m_viewMat[0][2] = zaxis.x;
			m_viewMat[1][2] = zaxis.y;
			m_viewMat[2][2] = zaxis.z;
			m_viewMat[3][2] = -Vector3::Dot(zaxis, m_eyePos);
			m_viewMat[0][3] = 0;
			m_viewMat[1][3] = 0;
			m_viewMat[2][3] = 0;
			m_viewMat[3][3] = 1;

			m_viewMatIsDirty = false;
		}
		return m_viewMat;
	}

	bool Camera::SetFovY(const Radian& fovY)
	{
		if (m_fovY == fovY)
			return true;

		if (fovY.GetRadian() < 0 ||
			fovY.GetRadian() > Math::PI)
		{
			return false;
		}

		m_fovY = fovY;
		m_projMatIsDirty = true;
		return true;
	}

	bool Camera::SetAspectRatio(float aspect)
	{
		if (m_aspectRatio == aspect)
			return true;

		if (aspect <= 0.0f)
			return false;

		m_aspectRatio = aspect;
		m_projMatIsDirty = true;
		return true;
	}

	bool Camera::SetPlaneDistance(float nearDistance, float farDistance)
	{
		if (m_nearPlaneDistance == nearDistance &&
			m_farPlaneDistance == farDistance)
			return true;

		if (nearDistance <= 0.0f || farDistance <= 0.0f)
			return false;

		if (nearDistance >= farDistance)
			return false;

		m_nearPlaneDistance = nearDistance;
		m_farPlaneDistance = farDistance;
		m_projMatIsDirty = true;
		return true;
	}

	const Matrix4& Camera::GetProjectionMatrix() const
	{
		if (m_projMatIsDirty)
		{
			D3DXMATRIXA16 matProj;
			D3DXMatrixPerspectiveFovLH(&matProj,
				m_fovY.GetRadian(), m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
			D3DMapping::ToMatrix4(matProj, m_projMat);

			m_projMatIsDirty = false;
		}
		return m_projMat;
	}
}