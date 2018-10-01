#include "DXApp.h"


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
	applicationName = L"Engine01 - DirectX Setup";
	wndStyle = WS_OVERLAPPEDWINDOW;

	pApp = this;

	pDevice = NULL;
	pDeviceContext = NULL;
	pSwapChain = NULL;
	pRenderTargetView = NULL;
}

DXApp::~DXApp()
{
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDeviceContext)
	{
		pDeviceContext->Release();
		pDeviceContext = NULL;
	}
	if (pSwapChain)
	{
		pSwapChain->Release();
		pSwapChain = NULL;
	}
	if (pRenderTargetView)
	{
		pRenderTargetView->Release();
		pRenderTargetView = NULL;
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
			//return 0;
		}
		return 0; // if���� ���ͼ� �����ؾ���
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
		D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, //hardware�� �׷���ī�� ���
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
