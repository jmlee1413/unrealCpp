#include <Windows.h>

//�ݹ��� �ϳ� �����ߵȴ�
//������ Ű�Է��� �޾Ƽ� �����ϴ� �Լ�
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);


// ������ �����Լ� ���� ������
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	LPSTR IpCmdLine,
	int nCmdLine)
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
		return 0; // �����ϴ°�� ���α׷� ����

	//������ ����
	HWND hwnd;
	//ó�� ���ڴ� �������� Ŭ���� �̸��̶� ���ƾ���
	hwnd = CreateWindow(L"WindowClass", L"Engine00 - Win Setup",
		WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL,
		hinstance, NULL);
	
	// ������ �����̾ȵǸ� ���� �Ѿ���ⶫ�� ����ó��
	if (hwnd == NULL)
		return 0;

	// â ����
	ShowWindow(hwnd, SW_SHOW);

	// �޽��� ó�� ����
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//�޽����� quit�� �ƴѰ�쿡�� �׻� ����
	while (msg.message != WM_QUIT)
	{
		// �޽��� ����
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); // ���� �׻� ������ �м�
			DispatchMessage(&msg);  // �м��� ������ �Լ� ȣ�� (Winproc �����)
		}
	}

	return 0;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam )
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
