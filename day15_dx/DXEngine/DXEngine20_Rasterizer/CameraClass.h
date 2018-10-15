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
	void SetAspectRatio(UINT width, UINT height); // â���鶧 uint

	void GetPlaneDistance(float& zN, float& zF);
	void SetPlaneDistance(float zN, float zF);

	// �������� wvp�� ���
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

	// ���� �ۿ��� ������Ʈ ȣ�����Ͼ��
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:

	float fovY; // �þ߰�
	float aspectRatio; // ��Ⱦ��
	float nearZ;
	float farZ;

	float pitch = 0.f;
	float yaw = 0.f;

	float moveSpeed = 200.f;
	float rotationSpeed = 30.f;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	// ����� ���鋚
	XMVECTOR cameraPosition;
	XMVECTOR cameraLook;

	// �̵���
	XMVECTOR cameraUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XMVECTOR cameraRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XMVECTOR cameraForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	XMVECTOR defaultUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XMVECTOR defaultRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XMVECTOR defaultForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);

};

