#include <Windows.h>

//콜백을 하나 만들어야된다
//실제로 키입력을 받아서 실행하는 함수
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);


// 윈도우 메인함수 고대로 가져옴
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	LPSTR IpCmdLine,
	int nCmdLine)
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
		return 0; // 실패하는경우 프로그램 종료

	//윈도우 생성
	HWND hwnd;
	//처음 인자는 위에만든 클래스 이름이랑 같아야함
	hwnd = CreateWindow(L"WindowClass", L"Engine00 - Win Setup",
		WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL,
		hinstance, NULL);
	
	// 윈도우 생성이안되면 널이 넘어오기땜에 예외처리
	if (hwnd == NULL)
		return 0;

	// 창 띄우기
	ShowWindow(hwnd, SW_SHOW);

	// 메시지 처리 루프
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//메시지가 quit이 아닌경우에는 항상 실행
	while (msg.message != WM_QUIT)
	{
		// 메시지 맵핑
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); // 둘은 항상 쌍으로 분석
			DispatchMessage(&msg);  // 분석후 적절한 함수 호출 (Winproc 만든거)
		}
	}

	return 0;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam )
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
