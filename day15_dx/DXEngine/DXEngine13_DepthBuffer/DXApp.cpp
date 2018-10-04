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
	hwnd = NULL;
	this->hinstance = hinstance;
	clientWidth = 800;
	clientHeight = 600;
	applicationName = L"Engine13 - Depth Buffer";
	// libfbxsdk.dll을 프로젝트 폴더에 복사하고 경로 설정도해줘야함
	// 속성 c/c++ - language - conformance mode 를 no로
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
	Memory::SafeRelease(depthStencilView);
	Memory::SafeRelease(depthStencilBuffer);

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

	//Memory::SafeDeleteArray(vertices);
	//Memory::SafeDeleteArray(indices);

	Memory::SafeRelease(IndexBuffer);
	Memory::SafeRelease(cBuffer);
	Memory::SafeRelease(pTexture);
	Memory::SafeRelease(pSamplerState);

	Memory::SafeRelease(lightBuffer);
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
			// 타이머 업데이트
			gameTimer.UpdateTimer();

			// 엔진 없데이트, 그리기
			Update( gameTimer.DeltaTime() );
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

	gameTimer.StartTime();

	if (InitScene() == false)
		return false;

	if (InitTransformation() == false)
		return false; // 버텍스 셰이더

	if (InitLightCB() == false)
		return false; // 버텍스와 픽셀 사이

	if (InitTexture() == false)
		return false; // 픽셀 셰이더

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

	// 뎁스/ 스텐실 뷰 생성
	if (InitDepthStencilBuffer() == false)
	{
		return false;
	}

	// 렌더타겟 설정
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, depthStencilView);
	// **는 &주소값 전달  *는 그냥 변수 전달

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
	//버텍스셰이더파일 컴파일해서 버텍스셰이더용 버퍼에 저장
	HRESULT hr;
	hr = D3DX11CompileFromFile(L"SpecularVS.fx", NULL, NULL, "main",
		"vs_4_0", NULL, NULL, NULL, &vertexShaderBuffer, 
		NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"정점셰이더 컴파일 실패", L"오류", MB_OK);
		return false;
	}

	//버텍스 셰이더생성 버퍼에있는 값을 버텍스셰이더로 옮긴다
	hr = pDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"정점셰이더 생성 실패", L"오류", MB_OK);
		return false;
	}

	//버텍스 셰이더 바인딩(설정, 연결)binding
	pDeviceContext->VSSetShader(vertexShader, NULL, NULL);

	
	//픽셀셰이더 컴파일해서 필셀셰이더 버퍼에 저장
	hr = D3DX11CompileFromFile(L"SpecularPS.fx", NULL, NULL, "main",
		"ps_4_0", NULL, NULL, NULL, &pixelShaderBuffer, NULL, NULL);


	if (FAILED(hr))
	{
		MessageBox(hwnd, L"픽셀셰이더 컴파일 실패", L"오류", MB_OK);
		return false;
	}

	hr = pDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"픽셀셰이더 생성 실패", L"오류", MB_OK);
		return false;
	}

	//픽셀 셰이더 설정
	pDeviceContext->PSSetShader(pixelShader, NULL, NULL);

	//모델 로드
	//if (LoadModel("cube.txt") == false)
	//{
	//	return false;
	//}

	hr = LoadFBX("HeroTPP.FBX", &vertices, &indices);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"fbx 로드 실패", L"오류", MB_OK);
		return false;
	}

	// 버텍스, 인덱스 개수 설정
	nVertices = vertices.size();
	nIndices = indices.size();

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	//arraysize = sizeof(vertices) / sizeof(vertex)
	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = &vertices[0];

	// 버퍼를 사용하기 이전에 vbDesc,  vbData 를 만들어야 사용해먹을수있다
	pDevice->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"버텍스 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// 버텍스 버퍼 바인딩
	pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
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
	ibData.pSysMem = &indices[0];

	hr = pDevice->CreateBuffer(&ibDesc, &ibData, &IndexBuffer);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"인덱스 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	//인덱스 버퍼 바인딩
	pDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// 입력 레이아웃 점찍는역할
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
		// 앞에있는 포지션이 4byte 4byte 4byte 12바이트 쓰니까 띄우고 쓰라고 12써주는거임
		// 그래픽카드쓸때 이걸 설정해줘야됨
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		// 앞에 두개 더한값 12 + 16 = 28
	};

	// 입력 레이아웃 생성.
	hr = pDevice->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &vertexInputLayout);


	//인풋 레이아웃 바인딩
	pDeviceContext->IASetInputLayout(vertexInputLayout);

	//정점을 이어서 그릴 방식 설정
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//뷰포트 설정 해줘야 그려짐
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = clientWidth;
	viewport.Height = clientHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	pDeviceContext->RSSetViewports(1, &viewport);

	return true;
}

bool DXApp::LoadModel(const char * fileName)
{
	//파일 읽기
	fstream fin;
	fin.open(fileName);

	if (fin.fail())
		return false;

	char input; // 파일에서 읽은 문자 저장
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin >> nVertices; // 띄어쓰기 단위로 읽는다

	nIndices = nVertices; // 인덱스 개수는 버텍스 개수와 동일

	// 배열 공간 확보
	/*vertices = new Vertex[nVertices];
	indices = new DWORD[nIndices];*/

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin.get(input);
	fin.get(input); // 두칸건너뛰기

	for (int ix = 0; ix < nVertices; ++ix)
	{
		float x, y, z, u, v, nx, ny, nz;
		fin >> x >> y >> z;
		fin >> u >> v;
		fin >> nx >> ny >> nz;

		//vertices[ix].position = XMFLOAT3(x, y, z);
		//vertices[ix].texCoord = XMFLOAT2(u, v);
		//vertices[ix].normal = XMFLOAT3(nx, ny, nz);

		//indices[ix] = ix; // 인덱스
		////보통 버텍스 생성이랑 인덱스 생성 순서를 같이한다.
		Vertex vertex(XMFLOAT3(x, y, z), XMFLOAT2(u, v), XMFLOAT3(nx, ny, nz));
		vertices.push_back(vertex);
		indices.push_back(ix);
	}
	fin.close();

	return true;
}

bool DXApp::InitTransformation()
{
	worldMatrix  = XMMatrixIdentity();
	cameraPos    = XMVectorSet(0.f, 0.f, -300.f, 0.f);
	cameraTarget = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	cameraUp     = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	viewMatrix = XMMatrixLookAtLH(cameraPos, cameraTarget, cameraUp);

	worldMatrix = XMMatrixIdentity();
	XMMATRIX rotationX = XMMatrixRotationX(XMConvertToRadians(-90.f));
	XMMATRIX rotationY = XMMatrixRotationY(XMConvertToRadians(-180.f));
	XMMATRIX rotation = rotationX * rotationY;

	XMMATRIX translation = XMMatrixTranslation(0.f, -90.f, 0.f);
	worldMatrix = rotation * translation;

	// 원근 투영방식
	float fovY = XM_PI / 4.f; // 세로 시야각 설정
	projectionMatrix = XMMatrixPerspectiveFovLH(fovY, 
		(float)clientWidth / (float)clientHeight, 1.f, 1000.f);

	// 버퍼에 저장
	CBPerObject cData;
	ZeroMemory(&cData, sizeof(CBPerObject));
	cData.world = XMMatrixTranspose(worldMatrix);
	cData.view = XMMatrixTranspose(viewMatrix);
	cData.projection = XMMatrixTranspose(projectionMatrix);

	// 버퍼 설정
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

	// 버퍼 생성
	HRESULT hr = pDevice->CreateBuffer(&cbDesc, &cbData, &cBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"상수 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	//바인딩
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	return true;
}

bool DXApp::InitTexture()
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		pDevice, L"T_Chr_FPS_D.png", NULL, NULL, &pTexture, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"텍스처 로드 실패", L"오류", MB_OK);
		return false;
	}

	//샘플러 스테이트
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc)); 
	//만든 변수안에 숫자면 0 포인터면 null 등등으로 초기화해줌
	//samplerdesc안에도 여러 인자들이있기떄문에
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//샘플러 스테이트 생성
	hr = pDevice->CreateSamplerState(&samplerDesc, &pSamplerState); // 생성은 언제나 디바이스에서
	if (FAILED(hr))
	{
		MessageBox(NULL, L"샘플러 스테이트 생성 실패", L"오류", MB_OK);
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
		MessageBox(NULL, L"라이트 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	pDeviceContext->VSSetConstantBuffers(1, 1, &lightBuffer ); 
	// 인덱스버퍼에서 인덱스 0썼으니 그뒤애쓰는애는 1으로

	return true;
}

HRESULT DXApp::LoadFBX(const char * fileName, std::vector<Vertex>* pOutVertices, std::vector<DWORD>* pOutIndices)
{
	//fbxmanager가 생성되지 않았으면 생성
	if ( fbxManager == NULL)
	{
		fbxManager = FbxManager::Create();
		FbxIOSettings* pIOSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
		fbxManager->SetIOSettings(pIOSettings);
	}

	FbxGeometryConverter gConverter(fbxManager);
	FbxImporter* importer = FbxImporter::Create(fbxManager, "");
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "");

	// importer 초기화
	if (!importer->Initialize(fileName, -1, fbxManager->GetIOSettings()))
	{
		return E_FAIL;
	}

	// 3d씬 임포트
	if (!importer->Import(fbxScene))
	{
		return E_FAIL;
	}

	// 임포터 해제
	importer->Destroy();

	// fbx node 읽기
	FbxNode* fbxRootNode = fbxScene->GetRootNode();
	if (fbxRootNode == NULL)
		return E_FAIL;

	//모델링 폴리곤 구조를 삼각면으로 설정
	gConverter.Triangulate(fbxScene, true);

	int childCount = fbxRootNode->GetChildCount();
	for (int ix = 0; ix < childCount; ++ix)
	{
		FbxNode* fbxChildNode = fbxRootNode->GetChild(ix);

		//속성이 없는 노드는 패스
		if (fbxChildNode->GetNodeAttribute() == NULL)
			continue;

		// 노드 속성 타입 확인.
		FbxNodeAttribute::EType arrtType
			= fbxChildNode->GetNodeAttribute()->GetAttributeType();

		if (arrtType != FbxNodeAttribute::EType::eMesh)
			continue;

		//메시 정보 읽기
		FbxMesh* fbxMesh = fbxChildNode->GetMesh();

		//컨트롤 포인트 배열 얻어오기
		FbxVector4* vertices = fbxMesh->GetControlPoints();

		// 폴리곤 수 확인
		int polyCount = fbxMesh->GetPolygonCount();
		int vertexCounter = 0;

		for (int jx = 0; jx < polyCount; ++jx)
		{
			int vertexCount = fbxMesh->GetPolygonSize(jx); // 폴리곤 구성하는 버텍스 개수 확인
			for (int kx = 0; kx < vertexCount; ++kx)
			{
				// 버텍스 일기
				int vertexIndex = fbxMesh->GetPolygonVertex(jx, kx);
				Vertex vertex;
				vertex.position.x = (float)vertices[vertexIndex].mData[0];
				vertex.position.y = (float)vertices[vertexIndex].mData[1];
				vertex.position.z = (float)vertices[vertexIndex].mData[2];

				//uv 읽기
				vertex.texCoord = ReadUV(fbxMesh, vertexIndex, vertexCounter);

				// 노멀 읽기
				vertex.normal = ReadNormal(fbxMesh, vertexIndex, vertexCounter);

				pOutVertices->push_back(vertex);
				pOutIndices->push_back(vertexCounter);
				++vertexCounter;
			}
		}

	}



	return S_OK;
}

XMFLOAT2 DXApp::ReadUV(FbxMesh * mesh, int controlPointIndex, int vertexCounter)
{
	// UV가 있는지 확인.
	if (mesh->GetElementUVCount() < 1)
	{
		MessageBox(NULL, L"UV가 없습니다.", L"오류", MB_OK);
		return NULL;
	}

	// 반환용 데이터 선언.
	XMFLOAT2 texCoord(0.0f, 0.0f);

	// UV 전체 배열 읽기.
	FbxGeometryElementUV* vertexUV = mesh->GetElementUV(0);
	const bool isUsingIndex
		= vertexUV->GetReferenceMode() != FbxGeometryElement::eDirect;
	const int indexCount = isUsingIndex ? vertexUV->GetIndexArray().GetCount() : 0;

	// 모드 확인.
	switch (vertexUV->GetMappingMode())
	{
		// 현재 정점이 제어점 유형인 경우.
	case FbxGeometryElement::eByControlPoint:
	{
		// 현재 UV 값을 읽어올 인덱스 얻어오기.
		int index = isUsingIndex ? vertexUV->GetIndexArray().GetAt(controlPointIndex) : controlPointIndex;

		/*if (isUsingIndex == true)
			index = vertexUV->GetIndexArray().GetAt(controlPointIndex);
		else
			index = controlPointIndex;*/

			// UV 값 읽어오기. (DirectX와 FBX의 UV의 V좌표는 서로 반대.)
		texCoord.x = (float)vertexUV->GetDirectArray().GetAt(index).mData[0];
		texCoord.y = 1.0f - (float)vertexUV->GetDirectArray().GetAt(index).mData[1];

		// UV 값 반환.
		return texCoord;
	}

	case FbxGeometryElement::eByPolygonVertex:
	{
		// 현재 UV 값을 읽어올 인덱스 얻어오기.
		int index = isUsingIndex ? vertexUV->GetIndexArray().GetAt(vertexCounter) : vertexCounter;

		// UV 값 읽어오기. (DirectX와 FBX의 UV의 V좌표는 서로 반대.)
		texCoord.x = (float)vertexUV->GetDirectArray().GetAt(index).mData[0];
		texCoord.y = 1.0f - (float)vertexUV->GetDirectArray().GetAt(index).mData[1];

		// UV 값 반환.
		return texCoord;
	}

	default:
	{
		MessageBox(NULL, L"UV 값이 유효하지 않습니다", L"오류", MB_OK);
		return NULL;
	}
	}

	return NULL;
}

XMFLOAT3 DXApp::ReadNormal(FbxMesh * mesh, int controlPointIndex, int vertexCounter)
{
	XMFLOAT3 normal(0.0f, 0.0f, 0.0f);

	// 노멀이 있는지 확인.
	if (mesh->GetElementNormalCount() < 1)
	{
		MessageBox(NULL, L"노멀이 없습니다.", L"오류", MB_OK);
		return NULL;
	}

	FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
	const bool isUsingIndex
		= vertexNormal->GetReferenceMode() != FbxGeometryElement::eDirect;
	const int indexCount = isUsingIndex ? vertexNormal->GetIndexArray().GetCount() : 0;

	switch (vertexNormal->GetMappingMode())
	{
		// 현재 정점이 제어점 유형인 경우.
	case FbxGeometryElement::eByControlPoint:
	{
		// 현재 노멀 값을 읽어올 인덱스 얻어오기.
		int index = isUsingIndex ? vertexNormal->GetIndexArray().GetAt(controlPointIndex) : controlPointIndex;

		// 노멀 값 읽어오기. (DirectX와 FBX의 UV의 V좌표는 서로 반대.)
		normal.x = (float)vertexNormal->GetDirectArray().GetAt(index).mData[0];
		normal.y = (float)vertexNormal->GetDirectArray().GetAt(index).mData[1];
		normal.z = (float)vertexNormal->GetDirectArray().GetAt(index).mData[2];

		// 노멀 값 반환.
		return normal;
	}

	case FbxGeometryElement::eByPolygonVertex:
	{
		// 현재 노멀 값을 읽어올 인덱스 얻어오기.
		int index = isUsingIndex ? vertexNormal->GetIndexArray().GetAt(vertexCounter) : vertexCounter;

		// 노멀 값 읽어오기. (DirectX와 FBX의 UV의 V좌표는 서로 반대.)
		normal.x = (float)vertexNormal->GetDirectArray().GetAt(index).mData[0];
		normal.y = (float)vertexNormal->GetDirectArray().GetAt(index).mData[1];
		normal.z = (float)vertexNormal->GetDirectArray().GetAt(index).mData[2];

		// 노멀 값 반환.
		return normal;
	}

	default:
	{
		MessageBox(NULL, L"노멀 값이 유효하지 않습니다", L"오류", MB_OK);
		return NULL;
	}
	}

	return NULL;
}