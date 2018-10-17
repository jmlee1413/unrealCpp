#include "CameraClass.h"



CameraClass::CameraClass()
{
	//SetFovY(75.f);
	fovY = 75.f * Deg2Rad;
	nearZ = 1.f;
	farZ = 1000000.f;
}


CameraClass::~CameraClass()
{
}

void CameraClass::SetFovY(float fovY)
{
	this->fovY = fovY * Deg2Rad;
	UpdateProjectionMatrix();
}

void CameraClass::SetAspectRatio(UINT width, UINT height)
{
	this->aspectRatio = (float)width / (float)height;
}

void CameraClass::GetPlaneDistance(float & zN, float & zF)
{
	zN = nearZ;
	zF = farZ;
}

void CameraClass::SetPlaneDistance(float zN, float zF)
{
	nearZ = zN;
	farZ = zF;
}

void CameraClass::SetPosition(XMVECTOR pos)
{
	cameraPosition = pos;
	UpdateViewMatrix();
}

void CameraClass::MoveForward(float dir)
{
	// dir은 +/-
	cameraPosition += dir * moveSpeed * cameraForward;
}

void CameraClass::MoveRight(float dir)
{
	cameraPosition += dir * moveSpeed * cameraRight;
}

void CameraClass::MoveUp(float dir)
{
	cameraPosition += dir * moveSpeed * cameraUp;
}

void CameraClass::Yaw(float angle)
{
	yaw += angle * rotationSpeed * 0.001f;
}

void CameraClass::Pitch(float angle)
{
	pitch += angle * rotationSpeed * 0.001f;
}

void CameraClass::UpdateCamera()
{
	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);
	// default forward는 안바뀌고 rotationmatrix곱했을떄의 cameralook 벡터값
	cameraLook = XMVector3TransformCoord(defaultForward, rotMatrix);
	cameraLook = XMVector3Normalize(cameraLook);

	XMMATRIX rotYTemp = XMMatrixRotationY(yaw);
	// XMMATRIX rotYTemp = XMMatrixRotationY(rotMatrix); 바라보는 방향으로 이동

	cameraRight = XMVector3TransformCoord(defaultRight, rotYTemp);
	cameraForward = XMVector3TransformCoord(defaultForward, rotYTemp);
	cameraUp = XMVector3TransformCoord(defaultUp, rotYTemp);

	cameraLook = cameraPosition + cameraLook;

	UpdateViewMatrix();
}

void CameraClass::UpdateViewMatrix()
{
	viewMatrix = XMMatrixLookAtLH(cameraPosition, cameraLook, cameraUp);
}

void CameraClass::UpdateProjectionMatrix()
{
	projectionMatrix = XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
}
