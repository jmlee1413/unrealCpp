// 상수버퍼 - 공간변환행렬.
cbuffer cbPerObject : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// 상수버퍼 - 라이트용.
cbuffer cbLight : register(b1)
{
	float4 worldLightPosition;
	float4 worldCameraPosition;
};

// 정점 셰이더 입력용 구조체.
struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// 정점 셰이더 출력용 구조체.
struct vs_output
{
	float4 pos : SV_POSITION;
	float3 clipPos : TEXCOORD1;
};

vs_output main(vs_input input)
{
	vs_output output;

	// 공간 변환.
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.clipPos = input.pos;

	return output;
}