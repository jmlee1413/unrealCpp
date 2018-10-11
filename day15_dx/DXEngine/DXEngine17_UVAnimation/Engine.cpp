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
	// �������� ���� ����� ���ε�
	SetUVTime();
}

void Engine::Render()
{
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// ������ �÷��� ������
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���ؽ� �׸���
	//pDeviceContext->Draw(nVertices, 0);
	// draw�ϴ°� ��ο����̶����

	// �ε����׸���
	pDeviceContext->DrawIndexed(nIndices, 0, 0); //�ڿ��� ������

	//����ü�� ��ü
	pSwapChain->Present(0, 0);
}

void Engine::SetUVTime()
{
	CBPerFrame cData;
	ZeroMemory(&cData, sizeof(cData));
	cData.time.x = GetTickCount() / 1000.f; // 1/1000 �� : 1ms 
	//60�������̶�� 1/60��

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(CBPerFrame);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(cbData));
	cbData.pSysMem = &cData;

	// buffer create
	// �޸������� �ȵż� �������̴�
	// updateSubresource �Լ��� �ٲ���ߵ�

	ID3D11Buffer* cBuffer;

	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &cBuffer);
	if (FAILED(hr))
	{
		return;
	}

	pDeviceContext->VSSetConstantBuffers(1, 1, &cBuffer);

}
