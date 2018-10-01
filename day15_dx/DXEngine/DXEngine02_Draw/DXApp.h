#pragma once

#include <Windows.h>
#include "DxUtil.h"
//#include <d3d11.h>
//#include <d3dx11.h>
//
//#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//라이브러리를 프로젝트에 추가시키라


class DXApp
{
public:

	struct Vertex
	{
		float x;
		float y;
		float z;

		Vertex(float x, float y, float z) :x(x), y(y), z(z) {}
	};

	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	int Run();

	virtual bool Init();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual LRESULT MSGProc(HWND, UINT, WPARAM, LPARAM);

protected:
	// win32 설정 변수
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCWSTR applicationName;
	DWORD wndStyle;

	// directx 변수
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain; //백버퍼를 그린뒤 실제 그려지는 프론트버퍼로 전환시키는 장치. 많게 세장도있다
	ID3D11RenderTargetView* pRenderTargetView; 
	//최소 위 네개 필요

	ID3D11Buffer* vertexBuffer;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* vertexShaderBuffer;
	ID3DBlob* pixelShaderBuffer;
	ID3D11InputLayout* vertexInputLayout; //버텍스 정보를 입력하는애

protected:

	// 초기화 함수(메소드) 클래스 안에 있으면 메소드 밖에있으면 함수
	bool InitWindow();

	bool InitDirect3D();

	bool InitScene();
};

