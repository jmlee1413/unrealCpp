#include "VertexShader.h"

VertexShader::VertexShader()
{
}

VertexShader::VertexShader(LPCWSTR fileName)
	:Shader(fileName)
{
	profile = "vs_5_0";
}

VertexShader::VertexShader(LPCWSTR fileName, LPCSTR entry, LPCSTR profile)
	:Shader(fileName, entry, profile)
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::SetWVPMatrices(XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	cbMatrices.world = XMMatrixTranspose(world);
	cbMatrices.view = XMMatrixTranspose(view);
	cbMatrices.projection = XMMatrixTranspose(projection);
	// dx11 ��켱 hlsl ���켱
}

void VertexShader::SetLightInfo(XMVECTOR lightPos, XMVECTOR cameraPos)
{
	cbLight.lightPosition = lightPos;
	cbLight.cameraPosition = cameraPos;
}

bool VertexShader::CompileShader()
{
	if (!ShaderUtil::CompileShader(fileName, entryPoint, profile, &shaderBuffer))
	{
		MessageBox(NULL, L"���� ���̴� ������ ����", L"����", MB_OK);
		return false;
	}

	return true;
}

bool VertexShader::CreateShader(ID3D11Device * device)
{
	if (!ShaderUtil::CreateVertexShader(device, shaderBuffer->GetBufferPointer(),
		shaderBuffer->GetBufferSize(), NULL, &vertexShader))
	{
		MessageBox(NULL, L"���� ���̴� ���� ����", L"����", MB_OK);
		return false;
	}

	return true;
}

void VertexShader::BindShader(ID3D11DeviceContext * deviceContext)
{
	ShaderUtil::BindVertexShader(deviceContext, vertexShader, NULL, NULL);
}

void VertexShader::Release()
{
	Shader::Release();
	Memory::SafeRelease(vertexShader);
	Memory::SafeRelease(rsState);
}

bool VertexShader::CreateRasterizerState(ID3D11Device * device, 
	D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
{
	// ��ü�� ���۴� �׻� desc �ʿ�
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.FillMode = fillMode;
	rsDesc.CullMode = cullMode;

	if(IsError(device->CreateRasterizerState(&rsDesc, &rsState),
		L"�����Ͷ����� ���� ���� ����"))
		return false;

	return true;
}

void VertexShader::BindRasterizerState(ID3D11DeviceContext * deviceContext)
{
	deviceContext->RSSetState(rsState);
}
