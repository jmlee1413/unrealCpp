#pragma once

#include <vector>
#include "DxUtil.h"
#include "ShaderUtil.h"

class Shader
{
public:
	Shader();
	Shader(LPCWSTR fileName);
	Shader(LPCWSTR fileName, LPCSTR entry, LPCSTR profile);
	virtual ~Shader();

protected:
	// shader
	LPCWSTR fileName; 
	LPCSTR entryPoint;
	LPCSTR profile;
	ID3DBlob* shaderBuffer;

protected:
	virtual bool CompileShader() = 0;
	virtual bool CreateShader(ID3D11Device* device) = 0;
	virtual void BindShader(ID3D11DeviceContext* deviceContext) = 0;
	// = 0 은 본 클래스에서는 구현안하고 상속받은 클래스에서 구현하겠다
	virtual void Release();

public:
	void SetFileName(LPCWSTR fileName)
	{
		this->fileName = fileName;
	}
	void SetEntry(LPCSTR entry)
	{
		this->entryPoint = entry;
	}
	void SetProfile(LPCSTR profile)
	{
		this->profile = profile;
	}

	LPCWSTR GetFileName() const {return fileName;	};
	LPCSTR GetEntry() const { return entryPoint; };
	LPCSTR GetProfile() const { return profile; };
	ID3DBlob* GetShaderBuffer() const { return shaderBuffer; };
};

