#pragma once

#include <Windows.h>
#include "DxUtil.h"


class DXApp
{
public:

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 texCoord; // uv좌표를 저장

		Vertex(float x, float y, float z) : position(x,y,z) {}
		Vertex(XMFLOAT3 position) : position(position) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color) : position(position), color(color) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT2 uv)
			: position(position), color(color) , texCoord(uv) {}
	};

	// 상수버퍼 저장용 구조체
	struct CBPerObject
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		//셋을 곱하면 공간변환이된다
		//셋을 곱해서 쉐이더 보내도되고 한번씩 곱해도됨
	};

	struct CBPerFrame
	{
		XMFLOAT4 time;

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

	int nVertices;

	ID3D11Buffer* IndexBuffer;
	int nIndices; 

	// 공간변환에 필요한 변수
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	XMVECTOR cameraPos;
	XMVECTOR cameraTarget; // 카메라가 보는 방향
	XMVECTOR cameraUp; // 카메라의 업방향

	ID3D11Buffer* cBuffer; // 상수버퍼에 변환행렬을 저장해서 셰이더로 보냄

	// 텍스처, 샘플러 스테이트
	ID3D11ShaderResourceView* pTexture;
	ID3D11SamplerState* pSamplerState;

protected:

	// 초기화 함수(메소드) 클래스 안에 있으면 메소드 밖에있으면 함수
	bool InitWindow();

	bool InitDirect3D();

	bool InitScene();

	// 공간변환 행렬 초기화
	bool InitTransformation();

	// 텍스쳐 초기화
	bool InitTexture();

};

