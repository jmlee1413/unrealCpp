#pragma once
#include "DxUtil.h"

class CameraClass
{
public:
	CameraClass();
	~CameraClass();

	float GetFovY() const { return fovY * Rad2Deg; }; // degrees
	void SetFovY(float fovY);

	float GetAspectRatio() const { return aspectRatio; };
	void SetAspectRatio(UINT width, UINT height); // 창만들때 uint

	void GetPlaneDistance(float& zN, float& zF);
	void SetPlaneDistance(float zN, float zF);

	// 매프레임 wvp를 계산
	XMMATRIX GetViewMatrix() const { return viewMatrix; };
	XMMATRIX GetProjectionMatrix() const { return projectionMatrix; };

	XMVECTOR GetPosition() const { return cameraPosition; };
	void SetPosition(XMVECTOR pos);

	XMVECTOR GetRight() const { return cameraRight; };
	XMVECTOR GetLook() const { return cameraLook; };
	XMVECTOR GetUp() const { return cameraUp; };

	void MoveForward(float dir);
	void MoveRight(float dir);
	void MoveUp(float dir);

	void Yaw(float angle);
	void Pitch(float angle);

	void UpdateCamera();

private:

	// 굳이 밖에서 업데이트 호출할일없어서
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:

	float fovY; // 시야각
	float aspectRatio; // 종횡비
	float nearZ;
	float farZ;

	float pitch = 0.f;
	float yaw = 0.f;

	float moveSpeed = 200.f;
	float rotationSpeed = 30.f;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	// 뷰행렬 만들떄
	XMVECTOR cameraPosition;
	XMVECTOR cameraLook;

	// 이동용
	XMVECTOR cameraUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XMVECTOR cameraRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XMVECTOR cameraForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	XMVECTOR defaultUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XMVECTOR defaultRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XMVECTOR defaultForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);

};

