// 픽셀 셰이더 입력용 구조체.
struct ps_input
{
	float4 pos : SV_POSITION;
	float3 clipPos : TEXCOORD1;
};

TextureCube skymap;
SamplerState skymapSampler;

float4 main(ps_input input) : SV_TARGET
{
	return skymap.Sample(skymapSampler, input.clipPos);
}