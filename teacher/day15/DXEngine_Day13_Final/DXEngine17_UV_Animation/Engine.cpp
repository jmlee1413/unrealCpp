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

	// ���� ����.
	pDevice->CreateBuffer(&cbDesc, &timeData, &cBufferFrame);

	// ���ε�.
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
	// ���� ����.
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

	// ȭ�� ĥ�ϱ�.
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���� �׸���. (Draw Call. ��ο� ��).
	//pDeviceContext->Draw(nVertices, 0);
	pDeviceContext->DrawIndexed(nIndices, 0, 0);

	// ����ü�� ��ü.
	pSwapChain->Present(0, 0);
}