//���ؽ� ���̴�
// float4�̸� ���ο� 4�����ư���

struct vs_output
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};
//�ΰ��� ��� ��ȯ�ϱ� ���ؼ� ����ü�ϳ� ������ְ�
//�ؿ� ���ϰ��� vs_output���� �ٲ۴�

vs_output main( float4 pos: POSITION,
	            float4 color : COLOR ) // float3�� �ƴ� ������ x,y,z,w��
{
	vs_output output;
	output.pos = pos;
	output.color = color;
	return output;
}
//�����ϴ� pos�� SV_POSITION ������ ���ڴٴ¶�