#include "PixelShader.h"



PixelShader::PixelShader()
{
}


PixelShader::~PixelShader()
{
}

bool PixelShader::CompileShader()
{
	if (!ShaderUtil::CompileShader(fileName, entryPoint, profile, &shaderBuffer))
	{
		return false;
	}
	return true;
}

bool PixelShader::CreateShader(ID3D11Device * device)
{
	if (!ShaderUtil::CreatePixelShader(device, shaderBuffer->GetBufferPointer(),
		shaderBuffer->GetBufferSize(), NULL, &pixelShader))
	{
		return false;
	}
	return true;
}

void PixelShader::BindShader(ID3D11DeviceContext * deviceContext)
{
	ShaderUtil::BindPixelShader(deviceContext, pixelShader, NULL, NULL);
}

void PixelShader::Release()
{
	Shader::Release();
	Memory::SafeRelease(pixelShader);
}

bool PixelShader::CreateSamplerState(ID3D11Device * device)
{

	//샘플러 스테이트
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//샘플러 스테이트 생성
	HRESULT hr = device->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"샘플러 스테이트 생성 실패", L"오류", MB_OK);
		return false;
	}

	return true;
}

void PixelShader::BindSamplerState(ID3D11DeviceContext * deviceContext)
{
	deviceContext->PSSetSamplers(0, 1, &samplerState);
}

bool PixelShader::LoadTextures(ID3D11Device * device)
{
	HRESULT hr;
	for (int ix = 0; ix < textures.size(); ++ix)
	{
		hr = D3DX11CreateShaderResourceViewFromFile(device, 
			textures[ix].fileName, NULL, NULL, 
			&textures[ix].textureResource, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, L"텍스처 로드 실패", L"오류", MB_OK);
			return false;
		}
	}

	return true;
}

void PixelShader::BindTextures(ID3D11DeviceContext * deviceContext)
{
	for (int ix = 0; ix < textures.size(); ++ix)
	{
		deviceContext->PSSetShaderResources(ix, 1, &textures[ix].textureResource);
	}

	// deviceContext->PSSetShaderResources(0, 3, &textureResourceArray); 로 가능
}
