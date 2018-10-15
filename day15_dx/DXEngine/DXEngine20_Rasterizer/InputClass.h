#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include "DxUtil.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//linker - input - additional dependencies : lib 추가

class InputClass
{
public:
	InputClass();
	InputClass(HINSTANCE hinstance, HWND hwnd);
	~InputClass();

	bool InitInput();
	bool DetectKeyboard(BYTE key);
	bool DetectMouse(DIMOUSESTATE& currentMouseState);
	// &: 넘기는 쪽 데이터를 변경

private:
	IDirectInputDevice8* diKeyboard;
	IDirectInputDevice8* diMouse;

	DIMOUSESTATE prevMouseState; // 이전 position x,y값을 현재값과 비교
	// 키보드는 눌린값만 받아오면된다
	LPDIRECTINPUT8 directInput; // 초기화

	HINSTANCE hinstance;
	HWND hwnd;
};

