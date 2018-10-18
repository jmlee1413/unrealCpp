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

	// rasterizer state //
	// ���������� wireframe, solid �� �� �����ΰ� �ٲ�ġ�⸸��
	if (input.DetectKeyboard(DIK_1))
	{
		for (int ix=0; ix < meshes.size(); ++ix)
		{
			meshes[ix].CreateRasterizerState(pDevice, 
				D3D11_FILL_SOLID, D3D11_CULL_BACK);
		}
	} // solid

	if (input.DetectKeyboard(DIK_2))
	{
		for (int ix=0; ix < meshes.size(); ++ix)
		{
			meshes[ix].CreateRasterizerState(pDevice, 
				D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);
		}
	} // wireframe

	if (input.DetectMouse(currentMouseState))
	{
		// ī�޶� ȸ��
		// ȭ��� ����: ��ġ
		// ȭ��� �¿�: ��
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
	// ������ �÷��� ������
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ����/���ٽ� �� �����.
	pDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	DrawMesh();

	//����ü�� ��ü
	pSwapChain->Present(1, 0);
}

void Engine::DrawMesh()
{
	UpdateMesh(&skySphere);
	skySphere.DrawMesh(pDeviceContext);

	UpdateMesh(&fbxPlane);
	fbxPlane.DrawMesh(pDeviceContext);

	for (int ix = 0; ix < meshes.size(); ++ix)
	{
		Mesh* mesh = &meshes[ix];
		UpdateMesh(mesh);
		mesh->DrawMesh(pDeviceContext);
	}
}

void Engine::UpdateMesh(Mesh * mesh)
{
	BindShader(mesh);
	BindVertexBuffer(mesh);
	BindIndexBuffer(mesh);
	BindInputLayout(mesh);

	// rasterizer state
	mesh->BindRasterizerState(pDeviceContext);

	pDeviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mesh->BindTextures(pDeviceContext);
	mesh->BindSamplerState(pDeviceContext);

	UpdateWVPBuffer(mesh, &camera);
	UpdateLightCB(mesh);
}
