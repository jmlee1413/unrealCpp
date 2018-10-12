#include "Mesh.h"



Mesh::Mesh()
{
}

Mesh::Mesh(LPCSTR fbxName, LPCWSTR vsFileName, LPCWSTR psFileName)
{
	this->fbxName = fbxName;
	vertexShader = VertexShader(vsFileName);
	pixelShader = PixelShader(psFileName);
}


Mesh::~Mesh()
{
}

// shader //
bool Mesh::CompileShaders(ID3D11Device * device)
{
	// compile
	if (!vertexShader.CompileShader())
		return false;
	if (!pixelShader.CompileShader())
		return false;

	// create
	if (!vertexShader.CreateShader(device))
		return false;
	if (!pixelShader.CreateShader(device))
		return false;

	return true;
}

void Mesh::BindShaders(ID3D11DeviceContext * deviceContext)
{
	vertexShader.BindShader(deviceContext);
	pixelShader.BindShader(deviceContext);
}

// vertex //
bool Mesh::CreateVertexBuffer(ID3D11Device * device)
{
	int nVertices = vertices.size();

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = &vertices[0];

	HRESULT hr = device->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"버텍스 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	return true;
}

void Mesh::BindVertexBuffer(ID3D11DeviceContext * deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

bool Mesh::CreateIndexBuffer(ID3D11Device * device)
{
	int nIndices = indices.size();

	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
	ibDesc.ByteWidth = sizeof(DWORD) * nIndices;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = &indices[0];

	HRESULT hr = device->CreateBuffer(&ibDesc, &ibData, &indexBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"인덱스 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	return true;
}

void Mesh::BindIndexBuffer(ID3D11DeviceContext * deviceContext)
{
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

bool Mesh::CreateInputLayout(ID3D11Device * device)
{
	HRESULT hr = device->CreateInputLayout(inputLayoutDesc, ARRAYSIZE(inputLayoutDesc),
		vertexShader.GetShaderBuffer()->GetBufferPointer(),
		vertexShader.GetShaderBuffer()->GetBufferSize(), &inputLayout);

	return true;
}

void Mesh::BindInputLayout(ID3D11DeviceContext * deviceContext)
{
	deviceContext->IASetInputLayout(inputLayout);
}

void Mesh::AddTexture(Texture newTexture)
{
	pixelShader.AddTexture(newTexture);
}


void Mesh::DrawMesh(ID3D11DeviceContext * deviceContext)
{
	deviceContext->DrawIndexed(GetIndexCount(), 0, 0);
}

void Mesh::SetPosition(XMFLOAT3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
}

void Mesh::SetRotation(XMFLOAT3 rotation)
{
	this->rotation.x = rotation.x;
	this->rotation.y = rotation.y;
	this->rotation.z = rotation.z;
}

void Mesh::SetScale(XMFLOAT3 scale)
{
	this->scale.x = scale.x;
	this->scale.y = scale.y;
	this->scale.z = scale.z;
}

XMMATRIX Mesh::GetTranslationMatrix()
{
	return XMMatrixTranslation(position.x, position.y, position.z);
}

// deg2Rad = pi/180;
// rad2Deg = 180/pi;
XMMATRIX Mesh::GetRotationMatrix()
{
	// rotation matix값은 radian으로 써야됨
	XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(rotation.x));
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(rotation.z));

	return rotZ * rotX * rotY;
}

XMMATRIX Mesh::GetScaleMatrix()
{
	return XMMatrixScaling(scale.x, scale.y, scale.z);
}

XMMATRIX Mesh::GetWorldMatrix()
{
	return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();
}

bool Mesh::LoadTextures(ID3D11Device * device)
{
	if (!pixelShader.LoadTextures(device))
		return false;

	return true;
}

void Mesh::BindTextures(ID3D11DeviceContext * deviceContext)
{
	pixelShader.BindTextures(deviceContext);
}

bool Mesh::CreateSamplerState(ID3D11Device * device)
{
	if (!pixelShader.CreateSamplerState(device))
		return false;

	return true;
}

void Mesh::BindSamplerState(ID3D11DeviceContext * deviceContext)
{
	pixelShader.BindSamplerState(deviceContext);
}

void Mesh::Release()
{
	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(indexBuffer);
	Memory::SafeRelease(inputLayout);

	vertexShader.Release();
	pixelShader.Release();
}
