#pragma once

#include <D3D11.h>
#include <D3DX11.h>
#include <xnamath.h> // ms에서주는 겜 수학 라이브러리
// #include <D3DX10math.h> //10버전까지만 수학라이브러리가있음

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

//메모리 해제 헬퍼
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

