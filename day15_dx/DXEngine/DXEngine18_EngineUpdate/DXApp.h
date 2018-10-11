#pragma once

#include <Windows.h>
#include "DxUtil.h"
#include "FBXLoader.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	int Run();

	virtual bool Init();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual LRESULT MSGProc(HWND, UINT, WPARAM, LPARAM);

protected:
	// win32
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCWSTR applicationName;
	DWORD wndStyle;

	// directx
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView; 

	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;

	// transform
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	XMVECTOR cameraPos;
	XMVECTOR cameraTarget;
	XMVECTOR cameraUp;

	ID3D11Buffer* cBuffer; // ������ۿ� ��ȯ����� �����ؼ� ���̴��� ����
	ID3D11Buffer* lightBuffer; // ����Ʈ�� �������

	ID3D11ShaderResourceView* pNormalTexture;

	std::vector<Mesh> meshes;

protected:

	// init method //
	bool InitWindow();

	bool InitDirect3D();

	bool InitDepthStencilBuffer();

	bool InitScene();

	// mesh //
	void InitMeshInfo();

	// shader //
	bool CompileShader(Mesh* mesh);
	void BindShader(Mesh* mesh);

	// vertex buffer
	bool InitVertexBuffer(Mesh* mesh);
	void BindVertexBuffer(Mesh* mesh);

	// index buffer
	bool InitIndexBuffer(Mesh* mesh);
	void BindIndexBuffer(Mesh* mesh);

	// input layout
	bool InitInputLayout(Mesh* mesh);
	void BindInputLayout(Mesh* mesh);

	// transform //
	bool InitTransformation();

	bool InitTransformation(Mesh* mesh);
	void InitWorldMatrix(Mesh* mesh);
	void InitViewMatrix();
	void InitProjectionMatrix();

	bool InitWVPBuffer(Mesh* mesh);
	void UpdateWVPBuffer(Mesh* mesh);

	// light //
	bool InitLightCB();
	void BindLightCB();
	void UpdateLightCB(Mesh* mesh);

	// viewport // 
	void SetViewport();
};

