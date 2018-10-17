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
	float3 normal : NORMAL;
};

// 정점 셰이더 출력용 구조체.
struct vs_output
{
	float4 pos : SV_POSITION;
	float3 viewReflection : TEXCOORD0;
};

// 정점 셰이더.
vs_output main(vs_input input)
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(input.pos, world);		// 월드 변환.

	// 월드 좌표계 기준 노멀 값 구하기.
	float3 worldNormal = normalize(mul(input.normal, (float3x3)world));

	// 뷰 벡터 구하기.
	float4 viewDir = normalize(output.pos - worldCameraPosition);

	// 뷰벡터의 반사벡터 구하기.
	output.viewReflection
		= reflect(viewDir.xyz, worldNormal);
	output.viewReflection
		= normalize(output.viewReflection);

	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	return output;
}