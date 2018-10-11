//���ؽ� ���̴�
// float4�̸� ���ο� 4�����ư���
//���ؽ� ���̴��� ������ ������ȯ�� ���Ѱ�

//�������
cbuffer cbPerObject :  register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// register(b0) ���ϼ��� �Ⱥ��ϼ����ִ� �� ����ȼ���
// b�� �������� �ٸ��Ժ��̸�� ���⼱ �������
cbuffer cbLight : register(b1)
{
	float4 worldLightPosition;
	float4 worldCameraPosition;
};

struct vs_input
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
	float3 binormal: BINORMAL;
	// ���� ��� x TBN���: ������� ��ְ����� ��ȯ�Ҽ� �ִ�
	// �׷��� ���� normal tangent binormal���� ���°�
};

struct vs_output
{
	float4 pos:SV_POSITION;
	float2 texCoord: TEXCOORD0;
	float3 lightDir: TEXCOORD1;
	float3 viewDir:  TEXCOORD2;

	float3 T: TEXCOORD3;
	float3 B: TEXCOORD4;
	float3 N: TEXCOORD5;
};
//�ΰ��� ��� ��ȯ�ϱ� ���ؼ� ����ü�ϳ� ������ְ�
//�ؿ� ���ϰ��� vs_output���� �ٲ۴�

// ���� ���̴�.
vs_output main(
	/*float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0*/
	vs_input input)
{
	vs_output output;
	// ���� ��ȯ.
	output.pos = mul(input.pos, world);		// ���� ��ȯ.

	//����Ʈ
	output.lightDir = normalize(output.pos - worldLightPosition);
	output.viewDir  = normalize(output.pos - worldCameraPosition);

	output.N = normalize(mul(input.normal, (float3x3)world)); // ��ü�� �������ִ� ��ְ��� ��������� ��ְ����� ��ȯ����
	output.T = normalize(mul(input.tangent, (float3x3)world));
	output.B = normalize(mul(input.binormal, (float3x3)world));

	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	output.texCoord = input.texCoord;

	return output;
}