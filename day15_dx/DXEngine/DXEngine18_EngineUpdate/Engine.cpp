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
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// ������ �÷��� ������
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ����/���ٽ� �� �����.
	pDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	DrawMesh();

	//����ü�� ��ü
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
