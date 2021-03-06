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

void Engine::Update()
{
}

void Engine::Render()
{
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
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
