#pragma once

#include <Windows.h>
#include "DxUtil.h"
#include "GameTImer.h"
#include <vector>

//#include <d3d11.h>
//#include <d3dx11.h>
//
//#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//���̺귯���� ������Ʈ�� �߰���Ű��

using namespace std;

class DXApp
{
public:

	struct Vertex
	{
		XMFLOAT3 position;
		//XMFLOAT4 color;
		XMFLOAT2 texCoord; // uv��ǥ�� ����
		XMFLOAT3 normal;

		Vertex() {};
		Vertex(float x, float y, float z) : position(x,y,z) {}
		Vertex(XMFLOAT3 position) : position(position) {}
		/*Vertex(XMFLOAT3 position, XMFLOAT4 color) : position(position), color(color) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT2 uv)
			: position(position), color(color) , texCoord(uv) {}*/
		Vertex(XMFLOAT3 position, XMFLOAT2 texCoord, XMFLOAT3 normal) 
			: position(position), texCoord(texCoord), normal(normal) {}
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

	struct CBLight
	{
		XMVECTOR lightPosition;
		XMVECTOR cameraPosition;
	};

	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	int Run();

	virtual bool Init();
	virtual void Update(double deltaTime) = 0;
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
	//Vertex* vertices;
	std::vector<Vertex> vertices;

	ID3D11Buffer* IndexBuffer;
	int nIndices; 
	//DWORD* indices;
	std::vector<DWORD> indices;

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

	ID3D11Buffer* lightBuffer; // ����Ʈ�� �������

	GameTImer gameTimer;

	FbxManager* fbxManager; // fbx �δ�

protected:

	// �ʱ�ȭ �Լ�(�޼ҵ�) Ŭ���� �ȿ� ������ �޼ҵ� �ۿ������� �Լ�
	bool InitWindow();

	bool InitDirect3D();

	bool InitScene();

	// ť�� �ʱ�ȭ
	bool LoadModel(const char* fileName);

	// ������ȯ ��� �ʱ�ȭ
	bool InitTransformation();

	// �ؽ��� �ʱ�ȭ
	bool InitTexture();

	bool InitLightCB();

	//fbx �ε�
	HRESULT LoadFBX(const char* fileName, std::vector<Vertex>* pOutVertices,
		std::vector<DWORD>* pOutIndices);
};

