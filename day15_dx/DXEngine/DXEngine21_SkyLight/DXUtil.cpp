#include "DxUtil.h"

bool IsError(HRESULT hr, LPCWSTR errorMsg)
{
	if (hr<0)
	{
		MessageBox(NULL, errorMsg, L"error", MB_OK);
		return true;
	}

	return false;
}

float Rad2Deg = 180.f / XM_PI;
float Deg2Rad = XM_PI / 180.f;
