#pragma once

#include <D3D11.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <fbxsdk.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "libfbxsdk.lib")

//메모리 해제 헬퍼
namespace Memory
{
	template<class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = NULL;
		}
	}

	template<class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = NULL;
		}
	}

	template<class T> void SafeDeleteArray(T& t)
	{
		if (t)
		{
			delete[] t;
			t = NULL;
		}
	}
}

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT2 texCoord; // uv좌표를 저장
	XMFLOAT3 normal;
	XMFLOAT3 tangent;
	XMFLOAT3 binormal;

	Vertex() {};
	Vertex(float x, float y, float z) : position(x, y, z) {}
	Vertex(XMFLOAT3 position) : position(position) {}
	Vertex(XMFLOAT3 position, XMFLOAT2 texCoord, XMFLOAT3 normal)
		: position(position), texCoord(texCoord), normal(normal) {}
	Vertex(XMFLOAT3 position, XMFLOAT2 texCoord, XMFLOAT3 normal, XMFLOAT3 tangent, XMFLOAT3 binormal)
		: position(position), texCoord(texCoord), normal(normal), tangent(tangent), binormal(binormal) {}
};

struct CBPerObject
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct CBLight
{
	XMVECTOR lightPosition;
	XMVECTOR cameraPosition;
};

struct Texture
{
public:
	Texture() { ZeroMemory(this, sizeof(Texture)); };
	~Texture() { Memory::SafeRelease(textureResource); };

	LPCTSTR fileName;
	ID3D11ShaderResourceView* textureResource = NULL; // file 로드하면 생기는 애
};

bool IsError(HRESULT hr, LPCWSTR errorMsg);

extern float Rad2Deg;
extern float Deg2Rad;
// 헤더에 안하는 이유는 XM_PI땜에 너무 많이 정의됐다고 에러나서
// extern은 다른데 값 설정하겠다는 뜻
// 보통 헤더에 선언하고 cpp에 정의 변수도 같은식으로 한거