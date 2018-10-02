#include "Engine.h"


Engine::Engine(HINSTANCE hinstance)
	:DXApp(hinstance) //부모껄로 초기화
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
	// 설정한 컬러로 지워라
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// 버텍스 그리기
	//pDeviceContext->Draw(nVertices, 0);
	// draw하는걸 드로우콜이라고함

	// 인덱스그리기
	pDeviceContext->DrawIndexed(nIndices, 0, 0); //뒤에껀 오프셋

	//스왑체인 교체
	pSwapChain->Present(0, 0);
}

float rotX = 0.01f;
float rotY = 0.01f;
float rotZ = 90.f;
float doublePI = XM_PI * 2.f;
void Engine::RotateObject(double deltaTime)
{
	// 매프레임 회전한다
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

	// 이동
	XMMATRIX translation = XMMatrixTranslation(0.f, 0.f, 1.f);

	// 스케일
	XMMATRIX scale = XMMatrixScaling(1.f, 1.f, 1.f);

	// 월드 행렬 갱신
	worldMatrix = XMMatrixIdentity();
	worldMatrix = scale * rotation * translation;
	// SRT

	// 셰이더 상수버퍼에 전달해줘야함
	CBPerObject cbData;
	ZeroMemory(&cbData, sizeof(cbData));
	cbData.world = XMMatrixTranspose(worldMatrix);
	cbData.view = XMMatrixTranspose(viewMatrix);
	cbData.projection = XMMatrixTranspose(projectionMatrix);

	// cbuffer는 이미 바인딩돼있음
	pDeviceContext->UpdateSubresource(cBuffer, 0, 0, &cbData, 0, 0);


}
