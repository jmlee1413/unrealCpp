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
	// 매프레임 버퍼 만들고 바인드
	SetUVTime();
}

void Engine::Render()
{
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
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

void Engine::SetUVTime()
{
	CBPerFrame cData;
	ZeroMemory(&cData, sizeof(cData));
	cData.time.x = GetTickCount() / 1000.f; // 1/1000 초 : 1ms 
	//60프레임이라면 1/60초

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
	// 메모리해제가 안돼서 꺼질것이다
	// updateSubresource 함수로 바꿔줘야됨

	ID3D11Buffer* cBuffer;

	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &cBuffer);
	if (FAILED(hr))
	{
		return;
	}

	pDeviceContext->VSSetConstantBuffers(1, 1, &cBuffer);

}
