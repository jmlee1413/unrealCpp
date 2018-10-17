cbuffer cbPerObject :  register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float3 clipPos:TEXCOORD1;
};

vs_output main(vs_input input)
{
	vs_output output;
	output.pos = mul(input.pos, world);
	output.pos = mul(input.pos, view);
	output.pos = mul(input.pos, projection);

	output.clipPos = input.pos;
	return output;
}