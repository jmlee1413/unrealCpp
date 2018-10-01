#pragma once

#include <Windows.h>
#include "DxUtil.h"
//#include <d3d11.h>
//#include <d3dx11.h>
//
//#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//���̺귯���� ������Ʈ�� �߰���Ű��


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
	// win32 ���� ����
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCWSTR applicationName;
	DWORD wndStyle;

	// directx ����
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain; //����۸� �׸��� ���� �׷����� ����Ʈ���۷� ��ȯ��Ű�� ��ġ. ���� ���嵵�ִ�
	ID3D11RenderTargetView* pRenderTargetView; 
	//�ּ� �� �װ� �ʿ�

	ID3D11Buffer* vertexBuffer;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* vertexShaderBuffer;
	ID3DBlob* pixelShaderBuffer;
	ID3D11InputLayout* vertexInputLayout; //���ؽ� ������ �Է��ϴ¾�

protected:

	// �ʱ�ȭ �Լ�(�޼ҵ�) Ŭ���� �ȿ� ������ �޼ҵ� �ۿ������� �Լ�
	bool InitWindow();

	bool InitDirect3D();

	bool InitScene();
};

