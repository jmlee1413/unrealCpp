#include "DXApp.h"
#include <fstream>
using namespace std;

// 콜백함수 한번 감싸줘야한다 클래스 내부에서 못불러서
// wrapper
DXApp* pApp = NULL;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	if (pApp != NULL) pApp->MSGProc(hwnd, msg, wParam, lParam);
	else  return DefWindowProc(hwnd, msg, wParam, lParam);
}

DXApp::DXApp(HINSTANCE hinstance)
{
	hwnd = NULL; //핸들은 창을 만들어야 설정할수있다
	// null이나 nullptr이나 똑같다
	this->hinstance = hinstance;
	clientWidth = 1200;
	clientHeight = 1000;
	applicationName = L"Engine18 - Engine Update";
	wndStyle = WS_OVERLAPPEDWINDOW;

	pApp = this;

	pDevice = NULL;
	pDeviceContext = NULL;
	pSwapChain = NULL;
	pRenderTargetView = NULL;
}

DXApp::~DXApp()
{
	Memory::SafeRelease(pRenderTargetView);
	Memory::SafeRelease(pSwapChain);
	Memory::SafeRelease(pDeviceContext);
	Memory::SafeRelease(pDevice);

	Memory::SafeRelease(depthStencilView);
	Memory::SafeRelease(depthStencilBuffer);

	Memory::SafeRelease(cBuffer);
	Memory::SafeRelease(lightBuffer);

	Memory::SafeRelease(pNormalTexture);

	for (int ix = 0; ix < meshes.size(); ++ix)
	{
		meshes[ix].Release();
	}
}

//메시지를 처리할 루프
int DXApp::Run()
{	
	// 메시지 처리 루프
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//메시지가 quit이 아닌경우에는 항상 실행
	while (msg.message != WM_QUIT)
	{
		// get은 메시지처리만하고 peek은 메시지받으면서 다른일도 함 (else로)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 받은메시지 지우겠니
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 엔진 없데이트, 그리기
			Update();
			Render();
		}

		//if (GetMessage(&msg, NULL, 0, 0))
		//{
		//	TranslateMessage(&msg); // 둘은 항상 쌍으로 분석
		//	DispatchMessage(&msg);  // 분석후 적절한 함수 호출 (Winproc 만든거)
		//}

	}
	return 0;
}

bool DXApp::Init()
{
	//win 32 초기화
	if (InitWindow() == false)
		return false;

	if (InitDirect3D() == false)
		return false;

	if (InitDepthStencilBuffer() == false)
		return false;

	if (InitScene() == false)
		return false;

	if (InitLightCB() == false)
		return false;

	return true;
}

LRESULT DXApp::MSGProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//메시지 처리
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// 나머지는 디폴트로 해주시오 딱히 바라는건없지만
	default:return DefWindowProc(hwnd, msg, wParam, lParam);

	}
}

bool DXApp::InitWindow()
{
	// 창을 만들어야됨
	// 윈도우 클래스 생성
	WNDCLASSEX wc;
	//초기화 하는것이 좋다 알아서 해준다
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance; //자동으로 넘어온 윈도우 핸들
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //뒤에있는것은 숫자값이다
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WindowClass";
	wc.lpfnWndProc = WinProc;

	//만든 클래스 등록해야됨
	if (!RegisterClassEx(&wc))
		return false; // 실패하는경우 프로그램 종료

	//윈도우 생성
	//처음 인자는 위에만든 클래스 이름이랑 같아야함
	hwnd = CreateWindow(L"WindowClass", applicationName,
		wndStyle, 0, 0, clientWidth, clientHeight, NULL, NULL,
		hinstance, NULL);

	// 윈도우 생성이안되면 널이 넘어오기땜에 예외처리
	if (hwnd == NULL)
		return false;

	// 창 띄우기
	ShowWindow(hwnd, SW_SHOW);
	return true;
}

bool DXApp::InitDirect3D()
{
	//결과값 받을 변수
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC SwapDesc;
	ZeroMemory(&SwapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapDesc.BufferCount = 1; // 백버퍼의 숫자. 0 은 뒷면에 그리는작업 안하겠다
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더타겟의 출력이 목적이다
	SwapDesc.OutputWindow = hwnd; //아까만든 윈도우창
	SwapDesc.Windowed = true;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 텍스처가 32비트 unorm은 unsigned normalize
	SwapDesc.BufferDesc.Width = clientWidth;
	SwapDesc.BufferDesc.Height = clientHeight;
	// 프레임
	SwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	// 샘플링
	SwapDesc.SampleDesc.Count = 1;
	SwapDesc.SampleDesc.Quality = 0;
	// 장치 및 스왑체인 생성
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &SwapDesc, &pSwapChain, &pDevice,
		NULL, &pDeviceContext); // &로 넘겨야 인자에 값이 채워진다 어떻게 매번 함수로 리턴하겠니
	
	if (FAILED(hr))
	{
		MessageBox(NULL, L"장치 생성 실패", L"오류", MB_OK);
		return false;
	}

	//백버퍼 (화면을 채울 텍스처)
	ID3D11Texture2D* pBackBufferTexture;
	hr = pSwapChain->GetBuffer(NULL, //백버퍼가 하나이상일때 쓴다 0,1,2 인덱스값
		__uuidof(ID3D11Texture2D), 
		(void**)&pBackBufferTexture);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"백버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	hr = pDevice->CreateRenderTargetView(pBackBufferTexture,
		NULL, &pRenderTargetView); // **는 보통 리턴값

	if (FAILED(hr))
	{
		MessageBox(NULL, L"렌더타겟 생성 실패", L"오류", MB_OK);
		return false;
	}

	// 렌더타겟 설정 리턴값없다
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	//백버퍼 텍스처 해제
	if (pBackBufferTexture)
	{
		pBackBufferTexture->Release();
		pBackBufferTexture = NULL;
	}


	return true;
}

bool DXApp::InitDepthStencilBuffer()
{
	//버퍼 서술자 설정
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = clientWidth;
	depthDesc.Height = clientHeight;
	depthDesc.MipLevels = 1; // 안쓰것다
	// miplevel은 뎁스에따라 텍스처 크기를 다르게 사용 LOD 기술 그래픽 라이브러리에서 자동으로 만들어줌
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0; // 깊이값인데 샘플링할이유가없음
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	HRESULT hr;
	hr = pDevice->CreateTexture2D(&depthDesc, NULL, &depthStencilBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"뎁스/스텐실버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	hr = pDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	// 위에서 pDesc 설정한거라서 nuLL로 만든다
	if (FAILED(hr))
	{
		MessageBox(NULL, L"뎁스/스텐실버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	return true;
}

bool DXApp::InitScene()
{
	InitMeshInfo();

	for (int ix = 0; ix < meshes.size(); ++ix)
	{
		Mesh* mesh = &meshes[ix];
		if (!CompileShader(mesh))
			return false;
		if (!InitVertexBuffer(mesh))
			return false;
		if (!InitIndexBuffer(mesh))
			return false;
		if (!InitInputLayout(mesh))
			return false;

		//정점을 이어서 그릴 방식 설정
		pDeviceContext->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		if (!mesh->LoadTextures(pDevice))
			return false;
		if (!mesh->CreateSamplerState(pDevice))
			return false;

		InitTransformation(mesh);
		InitLightCB();
		BindLightCB();
	}

	SetViewport();

	return true;
}

void DXApp::InitMeshInfo()
{
	LPCSTR fbxNameTPP = "Resources//Models//HeroTPP.fbx";

	Texture tppDiffuseMap;
	tppDiffuseMap.fileName = L"Resources//Textures//T_Chr_FPS_D.png";
	Texture tppNormalMap;
	tppNormalMap.fileName = L"Resources//Textures//T_Chr_FPS_N.png";
	Texture cubeMap;
	cubeMap.fileName = L"Resources//Textures//Yokohama3.dds";

	Mesh tppDiffuse(fbxNameTPP, L"Shaders//DiffuseVS.fx", L"Shaders//DiffusePS.fx");
	tppDiffuse.AddTexture(tppDiffuseMap);
	tppDiffuse.SetPosition(XMFLOAT3(-90.f, -90.f, 0.f));
	tppDiffuse.SetRotation(XMFLOAT3(-90.f, 180.f, 0.f));

	Mesh tppNormal(fbxNameTPP, L"Shaders//NormalVS.fx", L"Shaders//NormalPS.fx");
	tppNormal.AddTexture(tppDiffuseMap);
	tppNormal.AddTexture(tppNormalMap);
	tppNormal.SetPosition(XMFLOAT3(0.f, -90.f, 0.f));
	tppNormal.SetRotation(XMFLOAT3(-90.f, 180.f, 0.f));

	Mesh tppReflection(fbxNameTPP, L"Shaders//CubeVS.fx", L"Shaders//CubePS.fx");
	tppReflection.AddTexture(cubeMap);
	tppReflection.SetPosition(XMFLOAT3(90.f, -90.f, 0.f));
	tppReflection.SetRotation(XMFLOAT3(-90.f, 180.f, 0.f));

	// add to meshes
	meshes.push_back(tppDiffuse);
	meshes.push_back(tppNormal);
	meshes.push_back(tppReflection);
}

// 한번 더 랩핑해주는 이유는 함수 하나는 하나의 일만 해야된다고함 그래서 쪼갬
bool DXApp::CompileShader(Mesh * mesh)
{
	if (!mesh->CompileShaders(pDevice))
		return false;

	return true;
}

void DXApp::BindShader(Mesh * mesh)
{
	mesh->BindShaders(pDeviceContext);
}

bool DXApp::InitVertexBuffer(Mesh * mesh)
{
	HRESULT hr;
	hr = FBXLoader::LoadFBX(
		mesh->GetFBXName(), 
		mesh->GetVertexArray(),
		mesh->GetIndexArray()
	);

	if (FAILED(hr))
		return false;

	if (!mesh->CreateVertexBuffer(pDevice))
		return false;

	return true;
}

void DXApp::BindVertexBuffer(Mesh * mesh)
{
	mesh->BindVertexBuffer(pDeviceContext);
}

bool DXApp::InitIndexBuffer(Mesh * mesh)
{
	if (!mesh->CreateIndexBuffer(pDevice))
		return false;

	return true;
}

void DXApp::BindIndexBuffer(Mesh * mesh)
{
	mesh->BindIndexBuffer(pDeviceContext);
}

bool DXApp::InitInputLayout(Mesh * mesh)
{
	if (!mesh->CreateInputLayout(pDevice))
		return false;

	return true;
}

void DXApp::BindInputLayout(Mesh * mesh)
{
	mesh->BindInputLayout(pDeviceContext);
}

bool DXApp::InitTransformation()
{
	// 버퍼에 저장
	CBPerObject cData;
	ZeroMemory(&cData, sizeof(CBPerObject));
	cData.world = XMMatrixTranspose(worldMatrix);
	cData.view = XMMatrixTranspose(viewMatrix);
	cData.projection = XMMatrixTranspose(projectionMatrix);

	

	//바인딩
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	return true;
}

bool DXApp::InitTransformation(Mesh * mesh)
{
	//WVP 행렬초기화
	InitWorldMatrix(mesh);
	InitViewMatrix();
	InitProjectionMatrix();

	//행렬 설정
	mesh->SetWVPMatrices(worldMatrix, viewMatrix, projectionMatrix);

	InitWVPBuffer(mesh);
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	return true;
}

void DXApp::InitWorldMatrix(Mesh * mesh)
{
	worldMatrix = XMMatrixIdentity();
	worldMatrix = mesh->GetScaleMatrix() 
		* mesh->GetRotationMatrix() * mesh->GetTranslationMatrix();
}

void DXApp::InitViewMatrix()
{
	worldMatrix = XMMatrixIdentity();
	cameraPos = XMVectorSet(0.f, 0.f, -200.f, 1.f);
	cameraTarget = XMVectorSet(0.f, 0.f, 0.f, 1.f);
	cameraUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	viewMatrix = XMMatrixLookAtLH(cameraPos, cameraTarget, cameraUp);
}

void DXApp::InitProjectionMatrix()
{
	float fovY = XMConvertToRadians(75.f); // 세로 시야각 설정
	projectionMatrix = XMMatrixPerspectiveFovLH(fovY,
		(float)clientWidth / (float)clientHeight, 1.f, 1000.f);
}

bool DXApp::InitWVPBuffer(Mesh * mesh)
{
	// cbuffer setting
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.ByteWidth = sizeof(CBPerObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &mesh->GetWVPMatrices();

	// cbuffer create
	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &cBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"상수 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	// cbuffer bind
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);
	return true;
}

void DXApp::UpdateWVPBuffer(Mesh * mesh)
{
	InitWorldMatrix(mesh);
	mesh->SetWVPMatrices(worldMatrix, viewMatrix, projectionMatrix);

	// 새로운 행렬값으로 update
	pDeviceContext->UpdateSubresource(cBuffer, 0, 0,
		&mesh->GetWVPMatrices(), 0, 0);
}

bool DXApp::InitLightCB()
{
	CBLight cblight;
	ZeroMemory(&cblight, sizeof(cblight));
	cblight.lightPosition = XMVectorSet(-500.f, 500.f, -500.f, 1.f);
	cblight.cameraPosition = cameraPos;

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(CBLight);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(cbData));
	cbData.pSysMem = &cblight;

	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &lightBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"라이트 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	return true;
}

void DXApp::BindLightCB()
{
	pDeviceContext->VSSetConstantBuffers(1, 1, &lightBuffer);
}

void DXApp::UpdateLightCB(Mesh * mesh)
{
	pDeviceContext->UpdateSubresource(lightBuffer, 0, 0, &mesh->GetLightInfo(), 0, 0);
}

void DXApp::SetViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = clientWidth;
	viewport.Height = clientHeight;

	pDeviceContext->RSSetViewports(1, &viewport);
}
