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
		XMFLOAT2 texCoord; // uv��ǥ�� ����

		Vertex(float x, float y, float z) : position(x,y,z) {}
		Vertex(XMFLOAT3 position) : position(position) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color) : position(position), color(color) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT2 uv)
			: position(position), color(color) , texCoord(uv) {}
	};

	// ������� ����� ����ü
	struct CBPerObject
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		//���� ���ϸ� ������ȯ�̵ȴ�
		//���� ���ؼ� ���̴� �������ǰ� �ѹ��� ���ص���
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

	int nVertices;

	ID3D11Buffer* IndexBuffer;
	int nIndices; 

	// ������ȯ�� �ʿ��� ����
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	XMVECTOR cameraPos;
	XMVECTOR cameraTarget; // ī�޶� ���� ����
	XMVECTOR cameraUp; // ī�޶��� ������

	ID3D11Buffer* cBuffer; // ������ۿ� ��ȯ����� �����ؼ� ���̴��� ����

	// �ؽ�ó, ���÷� ������Ʈ
	ID3D11ShaderResourceView* pTexture;
	ID3D11SamplerState* pSamplerState;

protected:

	// �ʱ�ȭ �Լ�(�޼ҵ�) Ŭ���� �ȿ� ������ �޼ҵ� �ۿ������� �Լ�
	bool InitWindow();

	bool InitDirect3D();

	bool InitScene();

	// ������ȯ ��� �ʱ�ȭ
	bool InitTransformation();

	// �ؽ��� �ʱ�ȭ
	bool InitTexture();

};

