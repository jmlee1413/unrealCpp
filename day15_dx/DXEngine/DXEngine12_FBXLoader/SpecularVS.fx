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
	float3 worldCameraPosition;
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
	float3 diffuse: TEXCOORD1; //texcoord�� 8������ ��밡��
	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
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
	float3 lightDir = output.pos - worldLightPosition;
	lightDir = normalize(lightDir); //����ȭ
	float3 worldNormal = normalize(mul(input.normal, (float3x3)world));// ��ü�� �������ִ� ��ְ��� ��������� ��ְ����� ��ȯ����
	float3 diffuse = dot(-lightDir.xyz, worldNormal); // ���ѹ����� 0.0�� �ٶ󺻴� �ٵ� �ݴ�ιٶ������ �׷��� -
	//output.diffuse = diffuse;
	output.diffuse = diffuse * 0.5f + 0.4f;

	//����ŧ��
	float3 viewDir = normalize(output.pos - worldCameraPosition);
	float3 reflection = reflect(lightDir, worldNormal); // Reflect = Light + 2normal(-Light����normal)
	output.viewDir = viewDir;
	output.reflection = reflection;

	output.pos = mul(output.pos, view);		// �� ��ȯ.
	output.pos = mul(output.pos, projection);		// ���� ��ȯ.

	//output.color = color;
	output.texCoord = input.texCoord;
	output.normal = input.normal;

	return output;
}