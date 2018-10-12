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
		// **���������͸� &�ּҰ����� ���� ����� ����������
	if (IsError(hr, L"�Է� �ʱ�ȭ ����"))
		return false;

	hr = directInput->CreateDevice(GUID_SysKeyboard,
		&diKeyboard, NULL);
	if (IsError(hr, L"Ű���� �ʱ�ȭ ����"))
		return false;

	hr = directInput->CreateDevice(GUID_SysMouse,
		&diMouse, NULL);
	if (IsError(hr, L"���콺 �ʱ�ȭ ����"))
		return false;

	// dikeyboard�� Ű���� ���� �������̴�.
	hr = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (IsError(hr, L"Ű�������� ���� ����"))
		return false;

	// dimouse�� ���콺 ���� �������̴�.
	hr = diMouse->SetDataFormat(&c_dfDIMouse);
	if (IsError(hr, L"���콺���� ���� ����"))
		return false;

	// discl: direct input system cooperative level
	// â�� ������ �߿� �� �տ� ������ �� â���� ���ʹ�.
	hr = diKeyboard->SetCooperativeLevel(hwnd, 
		DISCL_FOREGROUND|DISCL_EXCLUSIVE | DISCL_NOWINKEY);
	if (IsError(hr, L"Ű���� ���� ���� ���� ����"))
		return false;

	// nowinkey: win key ��ȿȭ
	hr = diMouse->SetCooperativeLevel(hwnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE| DISCL_NOWINKEY);
	if (IsError(hr, L"���콺 ���� ���� ���� ����"))
		return false;

	return true;
}

bool InputClass::DetectKeyboard(BYTE key)
{
	// Ű���� �Է� ������ ���� �迭
	BYTE keyboardState[256];
	// BYTE : unsigned char

	// �Է� ȹ��
	diKeyboard->Acquire();

	// Ű���� ��ġ ���� ������
	diKeyboard->GetDeviceState(sizeof(keyboardState),
		(void**)&keyboardState);

	// Ű���� �Է� Ȯ��
	if (keyboardState[key] & 0x80) // ��Ʈ���� & ���ϱ� | ���ϱ�
		return true;



	return false;
}

bool InputClass::DetectMouse(DIMOUSESTATE & currentMouseState)
{
	diMouse->Acquire();
	diMouse->GetDeviceState(sizeof(currentMouseState),
		&currentMouseState);
	
	// ���콺 �Է� Ȯ��
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
