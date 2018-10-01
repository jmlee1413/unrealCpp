//���ؽ� ���̴�
// float4�̸� ���ο� 4�����ư���

//�������
cbuffer cbPerObject
{
	matrix world;
	matrix view;
	matrix projection;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};
//�ΰ��� ��� ��ȯ�ϱ� ���ؼ� ����ü�ϳ� ������ְ�
//�ؿ� ���ϰ��� vs_output���� �ٲ۴�

// ���� ���̴�.
vs_output main(
	float4 pos : POSITION,
	float4 color : COLOR)
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(pos, world);		// ���� ��ȯ.
	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	output.color = color;

	return output;
}