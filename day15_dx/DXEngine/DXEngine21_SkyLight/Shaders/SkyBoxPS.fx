struct ps_input
{
	float4 pos:SV_POSITION;
	float3 clipPos:TEXCOORD1;
};

TextureCube skyMap;
SamplerState skyMapSampler;

float4 main(ps_input input):SV_TARGET // render target
// deferred 렌더링에는 타겟이 여러개
// diffuse + specular + normal ...
{
	return skyMap.Sample(skyMapSampler, input.clipPos);
	// clipPos: 스피어의 버텍스위치
}