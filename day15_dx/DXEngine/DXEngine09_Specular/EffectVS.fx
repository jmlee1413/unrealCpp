//���ؽ� ���̴�
// float4�̸� ���ο� 4�����ư���
//���ؽ� ���̴��� ������ ������ȯ�� ���Ѱ�

//�������
cbuffer cbPerObject
{
	matrix world;
	matrix view;
	matrix projection;
};

struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct vs_output
{
	float4 pos:SV_POSITION;
	//float4 color:COLOR;
	float2 texCoord: TEXCOORD0;
	float3 normal: NORMAL; // ����Ҷ��� normal�̶�� �ϸ�ȵ�
	//������ ����ִ°� �ƹ��ſ� ����ְ� ����
};
//�ΰ��� ��� ��ȯ�ϱ� ���ؼ� ����ü�ϳ� ������ְ�
//�ؿ� ���ϰ��� vs_output���� �ٲ۴�

// ���� ���̴�.
vs_output main(
	/*float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0*/
	vs_input input )
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(input.pos, world);		// ���� ��ȯ.
	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	//output.color = color;
	output.texCoord = input.texCoord;
	output.normal = input.normal;

	return output;
}