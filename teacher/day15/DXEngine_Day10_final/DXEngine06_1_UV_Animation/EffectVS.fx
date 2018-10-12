// �������.
cbuffer cbPerObject : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer cbPerFrame : register(b1)
{
	float time;
};

// ���� ���̴� ��¿� ����ü.
struct vs_output
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD0;
};

// ���� ���̴�.
vs_output main(float4 pos : POSITION,
	float4 color : COLOR, float2 texCoord : TEXCOORD0)
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(pos, world);		// ���� ��ȯ.
	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	output.color = color;

	// �������� �Է¹��� �ؽ�ó ��ǥ ��ȯ.
	output.texCoord = texCoord + float2(time * 0.25f, 0);

	return output;
}