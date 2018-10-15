#pragma once
#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader();
	VertexShader(LPCWSTR fileName);
	VertexShader(LPCWSTR fileName, LPCSTR entry, LPCSTR profile);
	~VertexShader();

	// camera
	CBPerObject GetWVPMatrices() const { return cbMatrices; };
	void SetWVPMatrices(XMMATRIX world, XMMATRIX view, XMMATRIX projection);

	// light
	CBLight GetLightInfo() const { return cbLight; };
	void SetLightInfo(XMVECTOR lightPos, XMVECTOR cameraPos);

	// vertex shader
	virtual bool CompileShader() override;
	virtual bool CreateShader(ID3D11Device* device) override;
	virtual void BindShader(ID3D11DeviceContext* deviceContext) override;
	virtual void Release() override;

	// rasterizer state
	bool CreateRasterizerState(ID3D11Device* device,
		D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
	void BindRasterizerState(ID3D11DeviceContext* deviceContext);


private:
	ID3D11VertexShader* vertexShader;
	CBPerObject cbMatrices; // camera matrix 넘기는애
	CBLight cbLight;
	ID3D11RasterizerState* rsState;

};

