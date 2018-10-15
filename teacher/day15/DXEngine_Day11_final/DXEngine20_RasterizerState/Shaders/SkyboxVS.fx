// ��� ���� ����.
cbuffer CBPerObject : register(b0)
{
	matrix world;		// ���� ���.
	matrix view;		// �� ���.
	matrix projection;	// ���� ���.
};

// ��� ���� - ����Ʈ ����.
cbuffer CBLight : register(b1)
{
	float3 worldLightPosition;
	float3 worldCameraPosition;
};

// ���� �Է� ����ü.
struct VS_INPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

// ���� ��� ����ü.
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 viewDir : TEXCOORD1;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.pos = mul(input.pos, world);
	output.viewDir = normalize(output.pos.xyz - worldCameraPosition);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	return output;
}