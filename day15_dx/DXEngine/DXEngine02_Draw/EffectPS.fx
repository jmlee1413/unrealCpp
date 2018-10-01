//픽셀셰이더
float4 main(float4 input: POSITION):SV_TARGET
{
	return float4(1.0f,0.1f,0.1f,1.0f);
}
//속성에서 타입을 pixel shader로 지정해야쓸수있음