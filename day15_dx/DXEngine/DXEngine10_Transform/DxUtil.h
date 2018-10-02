#pragma once

#include <D3D11.h>
#include <D3DX11.h>
#include <xnamath.h> // ms�����ִ� �� ���� ���̺귯��
// #include <D3DX10math.h> //10���������� ���ж��̺귯��������

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

//�޸� ���� ����
namespace Memory
{
	template<class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = NULL;
		}
	}

	template<class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = NULL;
		}
	}

	template<class T> void SafeDeleteArray(T& t)
	{
		if (t)
		{
			delete[] t;
			t = NULL;
		}
	}
}

