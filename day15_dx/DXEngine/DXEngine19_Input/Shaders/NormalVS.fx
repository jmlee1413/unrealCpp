//버텍스 세이더
// float4이면 메인에 4번돌아간다
//버텍스 셰이더의 목적은 공간변환을 위한것

//상수버퍼
cbuffer cbPerObject :  register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// register(b0) 붙일수도 안붙일수도있다 걍 선언된순서
// b는 종류별로 다르게붙이면됨 여기선 상수버퍼
cbuffer cbLight : register(b1)
{
	float4 worldLightPosition;
	float4 worldCameraPosition;
};

struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
	float3 binormal: BINORMAL;
	// 로컬 노멀 x TBN행렬: 월드기준 노멀값으로 변환할수 있다
	// 그래서 굳이 normal tangent binormal값을 들고온것
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float2 texCoord: TEXCOORD0;
	float3 lightDir: TEXCOORD1;
	float3 viewDir:  TEXCOORD2;

	float3 T: TEXCOORD3;
	float3 B: TEXCOORD4;
	float3 N: TEXCOORD5;
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

// 정점 셰이더.
vs_output main(
	/*float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0*/
	vs_input input)
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(input.pos, world);		// 월드 변환.

	//라이트
	output.lightDir = normalize(output.pos - worldLightPosition);
	output.viewDir  = normalize(output.pos - worldCameraPosition);

	output.N = normalize(mul(input.normal, (float3x3)world)); // 물체가 가지고있는 노멀값을 월드공간의 노멀값으로 변환해줌
	output.T = normalize(mul(input.tangent, (float3x3)world));
	output.B = normalize(mul(input.binormal, (float3x3)world));

	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	output.texCoord = input.texCoord;

	return output;
}