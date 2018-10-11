//버텍스 세이더
// float4이면 메인에 4번돌아간다
//버텍스 셰이더의 목적은 공간변환을 위한것

//상수버퍼
cbuffer cbPerObject: register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

//상수버퍼 2
cbuffer cbPerFrame: register(b1)
{
	float4 time;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
	float2 texCoord: TEXCOORD0;
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

// 정점 셰이더.
vs_output main(
	float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0)
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(pos, world);		// 월드 변환.
	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	output.color = color;

	//output.texCoord = texCoord;
	output.texCoord = texCoord + float2(time.x *0.02f, 0) ; // u값에 더하기

	return output;
}