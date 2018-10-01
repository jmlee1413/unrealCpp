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
	clientWidth = 800;
	clientHeight = 600;
	applicationName = L"Engine09 - Specular";
	wndStyle = WS_OVERLAPPEDWINDOW;

	pApp = this;

	pDevice = NULL;
	pDeviceContext = NULL;
	pSwapChain = NULL;
	pRenderTargetView = NULL;

	vertexBuffer = NULL;
	vertexShader = NULL;
	pixelShader = NULL;
	vertexShaderBuffer = NULL;
	pixelShaderBuffer = NULL;
	vertexInputLayout = NULL;
}

DXApp::~DXApp()
{
	Memory::SafeRelease(pRenderTargetView);
	Memory::SafeRelease(pSwapChain);
	Memory::SafeRelease(pDeviceContext);
	Memory::SafeRelease(pDevice);

	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(vertexShader);
	Memory::SafeRelease(pixelShader);
	Memory::SafeRelease(vertexShaderBuffer);
	Memory::SafeRelease(pixelShaderBuffer);
	Memory::SafeRelease(vertexInputLayout);
	

	Memory::SafeDeleteArray(vertices);
	Memory::SafeDeleteArray(indices);

	Memory::SafeRelease(IndexBuffer);
	Memory::SafeRelease(cBuffer);
	Memory::SafeRelease(pTexture);
	Memory::SafeRelease(pSamplerState);

	Memory::SafeRelease(lightBuffer);
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

	if (InitScene() == false)
		return false;

	if (InitTransformation() == false)
		return false; // ���ؽ� ���̴�

	if (InitLightCB() == false)
		return false; // ���ؽ��� �ȼ� ����

	if (InitTexture() == false)
		return false; // �ȼ� ���̴�

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

bool DXApp::InitScene()
{
	//���ؽ����̴����� �������ؼ� ���ؽ����̴��� ���ۿ� ����
	HRESULT hr;
	hr = D3DX11CompileFromFile(L"SpecularVS.fx", NULL, NULL, "main",
		"vs_4_0", NULL, NULL, NULL, &vertexShaderBuffer, 
		NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"�������̴� ������ ����", L"����", MB_OK);
		return false;
	}

	//���ؽ� ���̴����� ���ۿ��ִ� ���� ���ؽ����̴��� �ű��
	hr = pDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"�������̴� ���� ����", L"����", MB_OK);
		return false;
	}

	//���ؽ� ���̴� ���ε�(����, ����)binding
	pDeviceContext->VSSetShader(vertexShader, NULL, NULL);

	
	//�ȼ����̴� �������ؼ� �ʼ����̴� ���ۿ� ����
	hr = D3DX11CompileFromFile(L"SpecularPS.fx", NULL, NULL, "main",
		"ps_4_0", NULL, NULL, NULL, &pixelShaderBuffer, NULL, NULL);


	if (FAILED(hr))
	{
		MessageBox(hwnd, L"�ȼ����̴� ������ ����", L"����", MB_OK);
		return false;
	}

	hr = pDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"�ȼ����̴� ���� ����", L"����", MB_OK);
		return false;
	}

	//�ȼ� ���̴� ����
	pDeviceContext->PSSetShader(pixelShader, NULL, NULL);

	//���� ������ �迭 ����
	//uv�� ���� ���� 0,0
	//Vertex vertices[] =
	//{
	//	Vertex(XMFLOAT3(-0.5f, 0.5f, 0.5f),
	//	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),

	//	Vertex(XMFLOAT3(0.5f, 0.5f, 0.5f),
	//	XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),

	//	Vertex(XMFLOAT3(0.5f, -0.5f, 0.5f),
	//	XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),

	//	Vertex(XMFLOAT3(-0.5f, -0.5f, 0.5f),
	//	XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),  XMFLOAT2(0.0f, 1.0f))
	//}; // �߾��� 0.0
	// dx�� �޼���ǥ�踦 �Ἥ �������� �ϸ� ���� ī�޶� �ٶ�
	// �簢���׸���� �ﰢ�� �ΰ���������;

	//nVertices = ARRAYSIZE(vertices);

	//�� �ε�
	if (LoadModel("cube.txt") == false)
	{
		return false;
	}

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	//arraysize = sizeof(vertices) / sizeof(vertex)
	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = vertices;

	// ���۸� ����ϱ� ������ vbDesc,  vbData �� ������ ����ظ������ִ�
	pDevice->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"���ؽ� ���� ���� ����", L"����", MB_OK);
		return false;
	}

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// ���ؽ� ���� ���ε�
	pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//// �ε��� ���� ����
	// unsigned long
	//DWORD indices[] = 
	//{
	//	0,1,2,
	//	0,2,3
	//}; // �ﰢ�� �ΰ��׸���
	
	//nIndices = ARRAYSIZE(indices);

	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
	ibDesc.ByteWidth = sizeof(DWORD) * nIndices;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = indices;

	hr = pDevice->CreateBuffer(&ibDesc, &ibData, &IndexBuffer);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"�ε��� ���� ���� ����", L"����", MB_OK);
		return false;
	}

	//�ε��� ���� ���ε�
	pDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �Է� ���̾ƿ� ����¿���
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		/*LPCSTR SemanticName;
		UINT SemanticIndex;
		DXGI_FORMAT Format;
		UINT InputSlot;
		UINT AlignedByteOffset;
		D3D11_INPUT_CLASSIFICATION InputSlotClass;
		UINT InstanceDataStepRate;*/
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// �տ��ִ� �������� 4byte 4byte 4byte 12����Ʈ ���ϱ� ���� ����� 12���ִ°���
		// �׷���ī�徵�� �̰� ��������ߵ�
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		// �տ� �ΰ� ���Ѱ� 12 + 16 = 28
	};

	// �Է� ���̾ƿ� ����.
	hr = pDevice->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &vertexInputLayout);


	//��ǲ ���̾ƿ� ���ε�
	pDeviceContext->IASetInputLayout(vertexInputLayout);

	//������ �̾ �׸� ��� ����
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//����Ʈ ���� ����� �׷���
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = clientWidth;
	viewport.Height = clientHeight;

	pDeviceContext->RSSetViewports(1, &viewport);

	return true;
}

bool DXApp::LoadModel(const char * fileName)
{
	//���� �б�
	fstream fin;
	fin.open(fileName);

	if (fin.fail())
		return false;

	char input; // ���Ͽ��� ���� ���� ����
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin >> nVertices; // ���� ������ �д´�

	nIndices = nVertices; // �ε��� ������ ���ؽ� ������ ����

	// �迭 ���� Ȯ��
	vertices = new Vertex[nVertices];
	indices = new DWORD[nIndices];

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin.get(input);
	fin.get(input); // ��ĭ�ǳʶٱ�

	for (int ix = 0; ix < nVertices; ++ix)
	{
		float x, y, z, u, v, nx, ny, nz;
		fin >> x >> y >> z;
		fin >> u >> v;
		fin >> nx >> ny >> nz;

		vertices[ix].position = XMFLOAT3(x, y, z);
		vertices[ix].texCoord = XMFLOAT2(u, v);
		vertices[ix].normal = XMFLOAT3(nx, ny, nz);

		indices[ix] = ix; // �ε���
		//���� ���ؽ� �����̶� �ε��� ���� ������ �����Ѵ�.
	}

	fin.close();

	return true;
}

bool DXApp::InitTransformation()
{
	worldMatrix  = XMMatrixIdentity();
	cameraPos    = XMVectorSet(4.f, 4.f, -8.f, 0.f);
	cameraTarget = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	cameraUp     = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	viewMatrix = XMMatrixLookAtLH(cameraPos, cameraTarget, cameraUp);

	// ���� �������
	float fovY = XM_PI / 4.f; // ���� �þ߰� ����
	projectionMatrix = XMMatrixPerspectiveFovLH(fovY, 
		(float)clientWidth / (float)clientHeight, 1.f, 1000.f);

	// ���ۿ� ����
	CBPerObject cData;
	ZeroMemory(&cData, sizeof(CBPerObject));
	cData.world = XMMatrixTranspose(worldMatrix);
	cData.view = XMMatrixTranspose(viewMatrix);
	cData.projection = XMMatrixTranspose(projectionMatrix);

	// ���� ����
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.ByteWidth = sizeof(CBPerObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &cData;

	// ���� ����
	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &cBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"��� ���� ���� ����", L"����", MB_OK);
		return false;
	}

	//���ε�
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	return true;
}

bool DXApp::InitTexture()
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		pDevice, L"dx.jpg", NULL, NULL, &pTexture, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"�ؽ�ó �ε� ����", L"����", MB_OK);
		return false;
	}

	//���÷� ������Ʈ
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc)); 
	//���� �����ȿ� ���ڸ� 0 �����͸� null ������� �ʱ�ȭ����
	//samplerdesc�ȿ��� ���� ���ڵ����ֱ⋚����
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//���÷� ������Ʈ ����
	hr = pDevice->CreateSamplerState(&samplerDesc, &pSamplerState); // ������ ������ ����̽�����
	if (FAILED(hr))
	{
		MessageBox(NULL, L"���÷� ������Ʈ ���� ����", L"����", MB_OK);
		return false;
	}
	
	pDeviceContext->PSSetShaderResources(0, 1, &pTexture);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

	return true;
}

bool DXApp::InitLightCB()
{
	CBLight cblight;
	ZeroMemory(&cblight, sizeof(cblight));
	cblight.lightPosition = XMVectorSet(-500.f, 500.f, -500.f, 1.f );
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

	pDeviceContext->VSSetConstantBuffers(1, 1, &lightBuffer ); 
	// �ε������ۿ��� �ε��� 0������ �׵ھ־��¾ִ� 1����

	return true;
}
