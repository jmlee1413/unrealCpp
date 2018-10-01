//버텍스 세이더
// float4이면 메인에 4번돌아간다
//버텍스 셰이더의 목적은 공간변환을 위한것

//상수버퍼
cbuffer cbPerObject
{
	matrix world;
	matrix view;
	matrix projection;
};

struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	//float4 color:COLOR;
	float2 texCoord: TEXCOORD0;
	float3 normal: NORMAL; // 출력할때는 normal이라고 하면안됨
	//데이터 비어있는거 아무거에 집어넣고 쓴다
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

// 정점 셰이더.
vs_output main(
	/*float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0*/
	vs_input input )
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(input.pos, world);		// 월드 변환.
	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	//output.color = color;
	output.texCoord = input.texCoord;
	output.normal = input.normal;

	return output;
}