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

	return true;
}

void Engine::Update()
{

}

void Engine::Render()
{
	// ���� ����.
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

	// ȭ�� ĥ�ϱ�.
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���� �׸���.
	pDeviceContext->Draw(3, 0);

	// ����ü�� ��ü.
	pSwapChain->Present(1, 0);
}