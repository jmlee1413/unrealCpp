#include "DXApp.h"
#include <fstream>
using namespace std;

// �ݹ��Լ� �ѹ� ��������Ѵ� Ŭ���� ���ο��� ���ҷ���
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
	hwnd = NULL; //�ڵ��� â�� ������ �����Ҽ��ִ�
	// null�̳� nullptr�̳� �Ȱ���
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

//�޽����� ó���� ����
int DXApp::Run()
{	
	// �޽��� ó�� ����
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//�޽����� quit�� �ƴѰ�쿡�� �׻� ����
	while (msg.message != WM_QUIT)
	{
		// get�� �޽���ó�����ϰ� peek�� �޽��������鼭 �ٸ��ϵ� �� (else��)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // �����޽��� ����ڴ�
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���� ������Ʈ, �׸���
			Update();
			Render();
		}

		//if (GetMessage(&msg, NULL, 0, 0))
		//{
		//	TranslateMessage(&msg); // ���� �׻� ������ �м�
		//	DispatchMessage(&msg);  // �м��� ������ �Լ� ȣ�� (Winproc �����)
		//}

	}
	return 0;
}

bool DXApp::Init()
{
	//win 32 �ʱ�ȭ
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
	//�޽��� ó��
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

	// �������� ����Ʈ�� ���ֽÿ� ���� �ٶ�°Ǿ�����
	default:return DefWindowProc(hwnd, msg, wParam, lParam);

	}
}

bool DXApp::InitWindow()
{
	// â�� �����ߵ�
	// ������ Ŭ���� ����
	WNDCLASSEX wc;
	//�ʱ�ȭ �ϴ°��� ���� �˾Ƽ� ���ش�
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance; //�ڵ����� �Ѿ�� ������ �ڵ�
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //�ڿ��ִ°��� ���ڰ��̴�
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WindowClass";
	wc.lpfnWndProc = WinProc;

	//���� Ŭ���� ����ؾߵ�
	if (!RegisterClassEx(&wc))
		return false; // �����ϴ°�� ���α׷� ����

	//������ ����
	//ó�� ���ڴ� �������� Ŭ���� �̸��̶� ���ƾ���
	hwnd = CreateWindow(L"WindowClass", applicationName,
		wndStyle, 0, 0, clientWidth, clientHeight, NULL, NULL,
		hinstance, NULL);

	// ������ �����̾ȵǸ� ���� �Ѿ���ⶫ�� ����ó��
	if (hwnd == NULL)
		return false;

	// â ����
	ShowWindow(hwnd, SW_SHOW);
	return true;
}

bool DXApp::InitDirect3D()
{
	//����� ���� ����
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC SwapDesc;
	ZeroMemory(&SwapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapDesc.BufferCount = 1; // ������� ����. 0 �� �޸鿡 �׸����۾� ���ϰڴ�
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ����Ÿ���� ����� �����̴�
	SwapDesc.OutputWindow = hwnd; //�Ʊ�� ������â
	SwapDesc.Windowed = true;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �ؽ�ó�� 32��Ʈ unorm�� unsigned normalize
	SwapDesc.BufferDesc.Width = clientWidth;
	SwapDesc.BufferDesc.Height = clientHeight;
	// ������
	SwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	// ���ø�
	SwapDesc.SampleDesc.Count = 1;
	SwapDesc.SampleDesc.Quality = 0;
	// ��ġ �� ����ü�� ����
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &SwapDesc, &pSwapChain, &pDevice,
		NULL, &pDeviceContext); // &�� �Ѱܾ� ���ڿ� ���� ä������ ��� �Ź� �Լ��� �����ϰڴ�
	
	if (FAILED(hr))
	{
		MessageBox(NULL, L"��ġ ���� ����", L"����", MB_OK);
		return false;
	}

	//����� (ȭ���� ä�� �ؽ�ó)
	ID3D11Texture2D* pBackBufferTexture;
	hr = pSwapChain->GetBuffer(NULL, //����۰� �ϳ��̻��϶� ���� 0,1,2 �ε�����
		__uuidof(ID3D11Texture2D), 
		(void**)&pBackBufferTexture);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"����� ���� ����", L"����", MB_OK);
		return false;
	}

	hr = pDevice->CreateRenderTargetView(pBackBufferTexture,
		NULL, &pRenderTargetView); // **�� ���� ���ϰ�

	if (FAILED(hr))
	{
		MessageBox(NULL, L"����Ÿ�� ���� ����", L"����", MB_OK);
		return false;
	}

	// ����Ÿ�� ���� ���ϰ�����
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	//����� �ؽ�ó ����
	if (pBackBufferTexture)
	{
		pBackBufferTexture->Release();
		pBackBufferTexture = NULL;
	}


	return true;
}

bool DXApp::InitDepthStencilBuffer()
{
	//���� ������ ����
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = clientWidth;
	depthDesc.Height = clientHeight;
	depthDesc.MipLevels = 1; // �Ⱦ��ʹ�
	// miplevel�� ���������� �ؽ�ó ũ�⸦ �ٸ��� ��� LOD ��� �׷��� ���̺귯������ �ڵ����� �������
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0; // ���̰��ε� ���ø�������������
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	HRESULT hr;
	hr = pDevice->CreateTexture2D(&depthDesc, NULL, &depthStencilBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"����/���ٽǹ��� ���� ����", L"����", MB_OK);
		return false;
	}

	hr = pDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	// ������ pDesc �����ѰŶ� nuLL�� �����
	if (FAILED(hr))
	{
		MessageBox(NULL, L"����/���ٽǹ��� ���� ����", L"����", MB_OK);
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

		//������ �̾ �׸� ��� ����
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

// �ѹ� �� �������ִ� ������ �Լ� �ϳ��� �ϳ��� �ϸ� �ؾߵȴٰ��� �׷��� �ɰ�
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
	// ���ۿ� ����
	CBPerObject cData;
	ZeroMemory(&cData, sizeof(CBPerObject));
	cData.world = XMMatrixTranspose(worldMatrix);
	cData.view = XMMatrixTranspose(viewMatrix);
	cData.projection = XMMatrixTranspose(projectionMatrix);

	

	//���ε�
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	return true;
}

bool DXApp::InitTransformation(Mesh * mesh)
{
	//WVP ����ʱ�ȭ
	InitWorldMatrix(mesh);
	InitViewMatrix();
	InitProjectionMatrix();

	//��� ����
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
	float fovY = XMConvertToRadians(75.f); // ���� �þ߰� ����
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
		MessageBox(NULL, L"��� ���� ���� ����", L"����", MB_OK);
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

	// ���ο� ��İ����� update
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
		MessageBox(NULL, L"����Ʈ ���� ���� ����", L"����", MB_OK);
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
