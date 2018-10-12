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


void Engine::ProcessInput(double deltaTime)
{
	if (input.DetectKeyboard(DIK_ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}

	if (input.DetectKeyboard(DIK_RIGHT)
		|| input.DetectKeyboard(DIK_D))
	{
		camera.MoveRight(deltaTime);
	} // right
	if (input.DetectKeyboard(DIK_LEFT)
		|| input.DetectKeyboard(DIK_A))
	{
		camera.MoveRight(-deltaTime);
	} // left
	if (input.DetectKeyboard(DIK_UP)
		|| input.DetectKeyboard(DIK_W))
	{
		camera.MoveForward(deltaTime);
	} // front
	if (input.DetectKeyboard(DIK_DOWN)
		|| input.DetectKeyboard(DIK_S))
	{
		camera.MoveForward(-deltaTime);
	} // back
	if (input.DetectKeyboard(DIK_Q))
	{
		camera.MoveUp(deltaTime);
	} // up
	if (input.DetectKeyboard(DIK_E))
	{
		camera.MoveUp(-deltaTime);
	} // down

	if (input.DetectMouse(currentMouseState))
	{
		// 카메라 회전
		// 화면상 상하: 피치
		// 화면상 좌우: 요
		camera.Yaw(currentMouseState.lX * deltaTime);
		camera.Pitch(currentMouseState.lY * deltaTime);
	}

}

void Engine::Update(double deltaTIme)
{
	camera.UpdateCamera();

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

		UpdateWVPBuffer(mesh, &camera);
		UpdateLightCB(mesh);

		mesh->DrawMesh(pDeviceContext);
	}
}
