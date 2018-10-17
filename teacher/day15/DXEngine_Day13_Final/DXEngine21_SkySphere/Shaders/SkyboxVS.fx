// ������� - ������ȯ���.
cbuffer cbPerObject : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// ������� - ����Ʈ��.
cbuffer cbLight : register(b1)
{
	float4 worldLightPosition;
	float4 worldCameraPosition;
};

// ���� ���̴� �Է¿� ����ü.
struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// ���� ���̴� ��¿� ����ü.
struct vs_output
{
	float4 pos : SV_POSITION;
	float3 clipPos : TEXCOORD1;
};

vs_output main(vs_input input)
{
	vs_output output;

	// ���� ��ȯ.
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.clipPos = input.pos;

	return output;
}