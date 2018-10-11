// 픽셀 셰이더 입력용 구조체.
// 색상값을 추출하기 위한 셰이더
// 버텍스 안에들어가는 픽셀수를 계산한다.
struct ps_input
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD0;
};

// 텍스처 정보.
Texture2D objTexture;
SamplerState objSampler;

// 픽셀 셰이더(쉐이더/셰이더).
float4 main(ps_input input) : SV_TARGET
{
	// 텍스처 샘플링 (색상 정보 추출).
	float4 texColor = objTexture.Sample(
		objSampler, input.texCoord);

// 텍스처 색상 반환.
return texColor;
}