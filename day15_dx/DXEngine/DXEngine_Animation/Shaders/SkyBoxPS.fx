struct ps_input
{
	float4 pos:SV_POSITION;
	float3 clipPos:TEXCOORD1;
};

TextureCube skyMap;
SamplerState skyMapSampler;

float4 main(ps_input input):SV_TARGET // render target
// deferred ���������� Ÿ���� ������
// diffuse + specular + normal ...
{
	return skyMap.Sample(skyMapSampler, input.clipPos);
	// clipPos: ���Ǿ��� ���ؽ���ġ
}