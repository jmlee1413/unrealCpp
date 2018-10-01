//버텍스 세이더
// float4이면 메인에 4번돌아간다

//상수버퍼
cbuffer cbPerObject
{
	matrix world;
	matrix view;
	matrix projection;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

// 정점 셰이더.
vs_output main(
	float4 pos : POSITION,
	float4 color : COLOR)
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(pos, world);		// 월드 변환.
	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	output.color = color;

	return output;
}