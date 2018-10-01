#include "DXApp.h"


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
			//return 0;
		}
		return 0; // if문을 나와서 종료해야함
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
		D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, //hardware는 그래픽카드 사용
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
