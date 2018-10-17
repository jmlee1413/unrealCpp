#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include "DxUtil.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//linker - input - additional dependencies : lib �߰�

class InputClass
{
public:
	InputClass();
	InputClass(HINSTANCE hinstance, HWND hwnd);
	~InputClass();

	bool InitInput();
	bool DetectKeyboard(BYTE key);
	bool DetectMouse(DIMOUSESTATE& currentMouseState);
	// &: �ѱ�� �� �����͸� ����

private:
	IDirectInputDevice8* diKeyboard;
	IDirectInputDevice8* diMouse;

	DIMOUSESTATE prevMouseState; // ���� position x,y���� ���簪�� ��
	// Ű����� �������� �޾ƿ���ȴ�
	LPDIRECTINPUT8 directInput; // �ʱ�ȭ

	HINSTANCE hinstance;
	HWND hwnd;
};

