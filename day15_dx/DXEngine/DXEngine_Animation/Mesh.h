#pragma once
#include "DXUtil.h"
#include <vector>
#include "VertexShader.h"
#include "PixelShader.h"


class Mesh
{
public:
	Mesh();
	Mesh(LPCSTR fbxName, LPCWSTR vsFileName, LPCWSTR psFileName);
	~Mesh();

	// shader
	bool CompileShaders(ID3D11Device* device);
	void BindShaders(ID3D11DeviceContext* deviceContext);

	// vertex
	bool CreateVertexBuffer(ID3D11Device* device);
	void BindVertexBuffer(ID3D11DeviceContext* deviceContext);

	// index
	bool CreateIndexBuffer(ID3D11Device* device);
	void BindIndexBuffer(ID3D11DeviceContext* deviceContext);

	// input layout
	bool CreateInputLayout(ID3D11Device* device);
	void BindInputLayout(ID3D11DeviceContext* deviceContext);

	// texture
	void AddTexture(Texture newTexture);

	// draw
	void DrawMesh(ID3D11DeviceContext* deviceContext);

	// transform
	XMFLOAT3 GetPosition() const { return position; };
	void SetPosition(XMFLOAT3 position);

	XMFLOAT3 GetRotation() const { return rotation; };
	void SetRotation(XMFLOAT3 rotation);

	XMFLOAT3 GetScale() const { return scale; };
	void SetScale(XMFLOAT3 scale);

	XMMATRIX GetTranslationMatrix();
	XMMATRIX GetRotationMatrix();
	XMMATRIX GetScaleMatrix();
	

	LPCSTR GetFBXName() const { return fbxName; };

	std::vector<Vertex>* GetVertexArray() { return &vertices; };
	int GetVertexCount() const { return vertices.size(); };

	std::vector<DWORD>* GetIndexArray() { return &indices; };
	int GetIndexCount() const { return indices.size(); };

	D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDesc() { return inputLayoutDesc; };

	// vertex shader
	CBPerObject GetWVPMatrices() const { return vertexShader.GetWVPMatrices(); };
	void SetWVPMatrices(XMMATRIX world, XMMATRIX view, XMMATRIX projection)
	{
		vertexShader.SetWVPMatrices(world, view, projection);
	};

	XMMATRIX GetWorldMatrix();

	CBLight GetLightInfo() const { return vertexShader.GetLightInfo(); };
	void SetLightInfo(XMVECTOR lightPos, XMVECTOR camPos) 
	{
		vertexShader.SetLightInfo(lightPos, camPos);
	}

	// pixel shader
	bool LoadTextures(ID3D11Device* device);
	void BindTextures(ID3D11DeviceContext* deviceContext);
	bool CreateSamplerState(ID3D11Device* device);
	void BindSamplerState(ID3D11DeviceContext* deviceContext);

	void Release();

	// rasterizer state
	bool CreateRasterizerState(ID3D11Device* device, 
		D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
	void BindRasterizerState(ID3D11DeviceContext* deviceContext);

private:
	LPCSTR fbxName;
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[5] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//D3D11_APPEND_ALIGNED_ELEMENT 로 하면 바이트계산 안해도된다
	};

	// buffer
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11InputLayout* inputLayout;

	// shader
	VertexShader vertexShader;
	PixelShader pixelShader;

	// transform
	XMFLOAT3 position = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 rotation = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 scale    = XMFLOAT3(1.f, 1.f, 1.f);
	//곱하는 순서 SRT
	//로테이션 곱하는순서 ZXY

};

