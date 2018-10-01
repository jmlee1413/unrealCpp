//버텍스 세이더
// float4이면 메인에 4번돌아간다

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

vs_output main( float4 pos: POSITION,
	            float4 color : COLOR ) // float3이 아닌 이유는 x,y,z,w라서
{
	vs_output output;
	output.pos = pos;
	output.color = color;
	return output;
}
//리턴하는 pos를 SV_POSITION 값으로 쓰겠다는뜻