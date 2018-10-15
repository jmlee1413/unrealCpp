#pragma once

#include <Windows.h>
#include "DxUtil.h"
#include "FBXLoader.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"
#include "InputClass.h"
#include "GameTimer.h"
#include "CameraClass.h"

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	int Run();

	virtual bool Init();
	virtual void ProcessInput(double deltaTime) = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void Render() = 0;
	virtual LRESULT MSGProc(HWND, UINT, WPARAM, LPARAM);

	LPCWSTR GetAppName() const { return applicationName; };
	HWND GetWindowHandle() const { return hwnd; };

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
	//XMMATRIX worldMatrix;
	//XMMATRIX viewMatrix;
	//XMMATRIX projectionMatrix;

	//XMVECTOR cameraPos;
	//XMVECTOR cameraTarget;
	//XMVECTOR cameraUp;

	ID3D11Buffer* cBuffer; // 상수버퍼에 변환행렬을 저장해서 셰이더로 보냄
	ID3D11Buffer* lightBuffer; // 라이트용 상수버퍼

	ID3D11ShaderResourceView* pNormalTexture;

	std::vector<Mesh> meshes;

	InputClass input;

	GameTimer gameTimer;

	CameraClass camera;

protected:

	// init method //
	bool InitWindow();

	bool InitInput();

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
	//bool InitTransformation();

	bool InitTransformation(Mesh* mesh, CameraClass* camera);
	//void InitWorldMatrix(Mesh* mesh);
	//void InitViewMatrix();
	//void InitProjectionMatrix();

	bool InitWVPBuffer(Mesh* mesh);
	void UpdateWVPBuffer(Mesh * mesh, CameraClass* camera);

	// light //
	bool InitLightCB();
	void BindLightCB();
	void UpdateLightCB(Mesh* mesh);

	// viewport // 
	void SetViewport();
};

