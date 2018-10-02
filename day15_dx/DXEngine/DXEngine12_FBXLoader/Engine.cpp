#include "Engine.h"


Engine::Engine(HINSTANCE hinstance)
	:DXApp(hinstance) //�θ𲬷� �ʱ�ȭ
{

}

Engine::~Engine()
{
}

bool Engine::Init()
{
	if (DXApp::Init() == false) 
		return false;

	return true;
}

void Engine::Update(double deltaTime)
{
	RotateObject(deltaTime);
}

void Engine::Render()
{
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// ������ �÷��� ������
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���ؽ� �׸���
	//pDeviceContext->Draw(nVertices, 0);
	// draw�ϴ°� ��ο����̶����

	// �ε����׸���
	pDeviceContext->DrawIndexed(nIndices, 0, 0); //�ڿ��� ������

	//����ü�� ��ü
	pSwapChain->Present(0, 0);
}

float rotX = 0.01f;
float rotY = 0.01f;
float rotZ = 90.f;
float doublePI = XM_PI * 2.f;
void Engine::RotateObject(double deltaTime)
{
	// �������� ȸ���Ѵ�
	//rotX += XMConvertToRadians(0.01f);
	//rotY += XMConvertToRadians(0.01f);
	//rotZ += XMConvertToRadians(0.01f);
	rotX += XMConvertToRadians(10.f * deltaTime);
	rotY += XMConvertToRadians(10.f * deltaTime);
	rotZ += XMConvertToRadians(10.f * deltaTime);

	if (rotY >= doublePI)
		rotY = 0.f;
	if (rotX >= doublePI)
		rotX = 0.f;
	if (rotZ >= doublePI)
		rotZ = 0.f;

	XMMATRIX rotationX = XMMatrixRotationX(rotX);
	XMMATRIX rotationY = XMMatrixRotationY(rotY);
	XMMATRIX rotationZ = XMMatrixRotationZ(rotZ);
	XMMATRIX rotation = rotationY;

	// �̵�
	XMMATRIX translation = XMMatrixTranslation(0.f, 0.f, 1.f);

	// ������
	XMMATRIX scale = XMMatrixScaling(1.f, 1.f, 1.f);

	// ���� ��� ����
	worldMatrix = XMMatrixIdentity();
	worldMatrix = scale * rotation * translation;
	// SRT

	// ���̴� ������ۿ� �����������
	CBPerObject cbData;
	ZeroMemory(&cbData, sizeof(cbData));
	cbData.world = XMMatrixTranspose(worldMatrix);
	cbData.view = XMMatrixTranspose(viewMatrix);
	cbData.projection = XMMatrixTranspose(projectionMatrix);

	// cbuffer�� �̹� ���ε�������
	pDeviceContext->UpdateSubresource(cBuffer, 0, 0, &cbData, 0, 0);


}
