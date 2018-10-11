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
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// 설정한 컬러로 지워라
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// 뎁스/스텐실 뷰 지우기.
	pDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	DrawMesh();

	//스왑체인 교체
	pSwapChain->Present(0, 0);
}

void Engine::DrawMesh()
{
	for (int ix = 0; ix < meshes.size(); ++ix)
	{
		Mesh* mesh = &meshes[ix];

		BindShader(mesh);
		BindVertexBuffer(mesh);
		BindIndexBuffer(mesh);
		BindInputLayout(mesh);

		pDeviceContext->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mesh->BindTextures(pDeviceContext);
		mesh->BindSamplerState(pDeviceContext);

		UpdateWVPBuffer(mesh);
		UpdateLightCB(mesh);

		mesh->DrawMesh(pDeviceContext);
	}
}
