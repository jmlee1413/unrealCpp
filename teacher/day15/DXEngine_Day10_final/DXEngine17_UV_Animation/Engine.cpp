#include "Engine.h"

Engine::Engine(HINSTANCE hinstance) 
	: DXApp(hinstance)
{

}

Engine::~Engine()
{

}

bool Engine::Init()
{
	if (DXApp::Init() == false) 
		return false;

	InitUVTime();

	return true;
}

void Engine::Update()
{
	SetUVTime();
}

void Engine::InitUVTime()
{
	CBPerFrame cData;
	ZeroMemory(&cData, sizeof(CBPerFrame));
	cData.time.x = GetTickCount() / 1000.0f;

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.ByteWidth = sizeof(CBPerFrame);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA timeData;
	ZeroMemory(&timeData, sizeof(D3D11_SUBRESOURCE_DATA));
	timeData.pSysMem = &cData;

	// 버퍼 생성.
	pDevice->CreateBuffer(&cbDesc, &timeData, &cBufferFrame);

	// 바인딩.
	pDeviceContext->VSSetConstantBuffers(1, 1, &cBufferFrame);
}

void Engine::SetUVTime()
{
	CBPerFrame cData;
	ZeroMemory(&cData, sizeof(CBPerFrame));
	cData.time.x = GetTickCount() / 1000.0f;

	pDeviceContext->UpdateSubresource(cBufferFrame,
		0, 0, &cData, 0, 0);
}

void Engine::Render()
{
	// 색상 설정.
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

	// 화면 칠하기.
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// 정점 그리기. (Draw Call. 드로우 콜).
	//pDeviceContext->Draw(nVertices, 0);
	pDeviceContext->DrawIndexed(nIndices, 0, 0);

	// 스왑체인 교체.
	pSwapChain->Present(0, 0);
}