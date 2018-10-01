//버텍스 세이더
// float4이면 메인에 4번돌아간다
float4 main(float4 pos:POSITION):SV_POSITION // float3이 아닌 이유는 x,y,z,w라서
{
	return pos;
}
//리턴하는 pos를 SV_POSITION 값으로 쓰겠다는뜻