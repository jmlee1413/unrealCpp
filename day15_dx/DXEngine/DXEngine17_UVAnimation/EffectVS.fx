//���ؽ� ���̴�
// float4�̸� ���ο� 4�����ư���
//���ؽ� ���̴��� ������ ������ȯ�� ���Ѱ�

//�������
cbuffer cbPerObject: register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

//������� 2
cbuffer cbPerFrame: register(b1)
{
	float4 time;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
	float2 texCoord: TEXCOORD0;
};
//�ΰ��� ��� ��ȯ�ϱ� ���ؼ� ����ü�ϳ� ������ְ�
//�ؿ� ���ϰ��� vs_output���� �ٲ۴�

// ���� ���̴�.
vs_output main(
	float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0)
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(pos, world);		// ���� ��ȯ.
	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	output.color = color;

	//output.texCoord = texCoord;
	output.texCoord = texCoord + float2(time.x *0.02f, 0) ; // u���� ���ϱ�

	return output;
}