#include "InputClass.h"



InputClass::InputClass()
{
}

InputClass::InputClass(HINSTANCE hinstance, HWND hwnd)
{
	this->hinstance = hinstance;
	this->hwnd = hwnd;
}


InputClass::~InputClass()
{
}

bool InputClass::InitInput()
{
	HRESULT hr;
	hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&directInput, NULL );
		// **더블포인터를 &주소값으로 변경 요새는 포인터정도
	if (IsError(hr, L"입력 초기화 실패"))
		return false;

	hr = directInput->CreateDevice(GUID_SysKeyboard,
		&diKeyboard, NULL);
	if (IsError(hr, L"키보드 초기화 실패"))
		return false;

	hr = directInput->CreateDevice(GUID_SysMouse,
		&diMouse, NULL);
	if (IsError(hr, L"마우스 초기화 실패"))
		return false;

	// dikeyboard는 키보드 값을 받을것이다.
	hr = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (IsError(hr, L"키보드포맷 설정 실패"))
		return false;

	// dimouse는 마우스 값을 받을것이다.
	hr = diMouse->SetDataFormat(&c_dfDIMouse);
	if (IsError(hr, L"마우스포맷 설정 실패"))
		return false;

	// discl: direct input system cooperative level
	// 창이 여러개 중에 맨 앞에 있을떄 이 창에서 쓰것다.
	hr = diKeyboard->SetCooperativeLevel(hwnd, 
		DISCL_FOREGROUND|DISCL_EXCLUSIVE | DISCL_NOWINKEY);
	if (IsError(hr, L"키보드 협력 레벨 설정 실패"))
		return false;

	// nowinkey: win key 무효화
	hr = diMouse->SetCooperativeLevel(hwnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE| DISCL_NOWINKEY);
	if (IsError(hr, L"마우스 협력 레벨 설정 실패"))
		return false;

	return true;
}

bool InputClass::DetectKeyboard(BYTE key)
{
	// 키보드 입력 감지를 위한 배열
	BYTE keyboardState[256];
	// BYTE : unsigned char

	// 입력 획득
	diKeyboard->Acquire();

	// 키보드 장치 상태 얻어오기
	diKeyboard->GetDeviceState(sizeof(keyboardState),
		(void**)&keyboardState);

	// 키보드 입력 확인
	if (keyboardState[key] & 0x80) // 비트연산 & 곱하기 | 더하기
		return true;



	return false;
}

bool InputClass::DetectMouse(DIMOUSESTATE & currentMouseState)
{
	diMouse->Acquire();
	diMouse->GetDeviceState(sizeof(currentMouseState),
		&currentMouseState);
	
	// 마우스 입력 확인
	bool retValue = false;
	if (currentMouseState.lX != prevMouseState.lX
		|| currentMouseState.lY != prevMouseState.lY
		|| currentMouseState.lZ != prevMouseState.lZ)
	{
		retValue = true;
		prevMouseState = currentMouseState;
	}

	return retValue;
}
