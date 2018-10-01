//픽셀셰이더
//여기에다가도 구조체 만들어줌 근데 입력용
// 버텍스 쉐이더에서 픽셀쉐이더로 정보가 들어오기떄문에
struct ps_input
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};

float4 main(ps_input input): SV_TARGET
{
	return input.color;
}
//속성에서 타입을 pixel shader로 지정해야쓸수있음