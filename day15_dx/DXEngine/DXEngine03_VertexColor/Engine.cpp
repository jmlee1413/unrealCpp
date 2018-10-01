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

void Engine::Update()
{
}

void Engine::Render()
{
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
	// ������ �÷��� ������
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���ؽ� �׸���
	pDeviceContext->Draw(nVertices, 0);

	//����ü�� ��ü
	pSwapChain->Present(0, 0);
}
