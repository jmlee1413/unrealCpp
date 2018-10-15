#pragma once
#include "DxUtil.h"

namespace ShaderUtil
{
	//class Shader;
	// �ֹ��� ��� ��Ŭ��� �Ҷ� ���� ��Ŭ��� ���°�
	// ��������� ���ϰ� cpp���� ��Ŭ����Ѵ�

	//bool CompileShader(Shader shader);
	bool CompileShader(LPCWSTR fileName, LPCSTR entry, 
		LPCSTR profile, ID3DBlob** pOutShaderBuffer);

	// vertex //
	bool CreateVertexShader(ID3D11Device* device, const void* pointer,
		SIZE_T size, ID3D11ClassLinkage* linkage, ID3D11VertexShader** ppVertexShader);

	void BindVertexShader(ID3D11DeviceContext* deviceContext, ID3D11VertexShader* pVertexShader,
		ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances);

	// pixel //
	bool CreatePixelShader(ID3D11Device* device, const void* pointer,
		SIZE_T size, ID3D11ClassLinkage* linkage, ID3D11PixelShader** ppPixelShader);

	void BindPixelShader(ID3D11DeviceContext* deviceContext, ID3D11PixelShader* pPixelShader,
		ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances);

};

