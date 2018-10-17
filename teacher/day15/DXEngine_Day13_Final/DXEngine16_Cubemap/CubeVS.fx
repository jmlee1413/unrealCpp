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
	float3 normal : NORMAL;
};

// ���� ���̴� ��¿� ����ü.
struct vs_output
{
	float4 pos : SV_POSITION;
	float3 viewReflection : TEXCOORD0;
};

// ���� ���̴�.
vs_output main(vs_input input)
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(input.pos, world);		// ���� ��ȯ.

	// ���� ��ǥ�� ���� ��� �� ���ϱ�.
	float3 worldNormal = normalize(mul(input.normal, (float3x3)world));

	// �� ���� ���ϱ�.
	float4 viewDir = normalize(output.pos - worldCameraPosition);

	// �交���� �ݻ纤�� ���ϱ�.
	output.viewReflection
		= reflect(viewDir.xyz, worldNormal);
	output.viewReflection
		= normalize(output.viewReflection);

	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	return output;
}