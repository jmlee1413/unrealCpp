// �ȼ� ���̴� �Է¿� ����ü.
// ������ �����ϱ� ���� ���̴�
// ���ؽ� �ȿ����� �ȼ����� ����Ѵ�.
struct ps_input
{
	float4 pos:SV_POSITION;
	//float4 color:COLOR;
	float2 texCoord: TEXCOORD0;
	float3 normal: NORMAL;
	float3 diffuse: TEXCOORD1;
	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
};

// �ؽ�ó ����.
Texture2D objTexture;
SamplerState objSampler;

// �ȼ� ���̴�(���̴�/���̴�).
float4 main(ps_input input) : SV_TARGET
{
	//// �ؽ�ó ���ø� (���� ���� ����).
	float4 texColor = objTexture.Sample(
		objSampler, input.texCoord);

// ��ǻ�� ���� ����
float3 diffuse = saturate(input.diffuse); // 0������ ���� 0���� �������ִ� saturate

// ����ŧ��
float3 reflection = normalize(input.reflection).xyz;
float3 viewDir = normalize(input.viewDir).xyz;
float3 specular = 0;

if (diffuse.x > 0)
{
	//�交�Ϳ� �ݻ纤���� ����
	specular = dot(reflection, -viewDir);
	specular = saturate(specular);
	// �ڻ��α׷����� �����ؼ� �׷����� ���Ը���� ���ݻ翵����������
	specular = pow(specular, 30.f); 
}
// �ֺ���
float3 ambient = float3(0.1f, 0.1f, 0.1f);

// ��������
//float3 finalColor = texColor.rgb * diffuse + specular;
float3 finalColor = diffuse + specular + ambient;

// �ؽ�ó ���� ��ȯ.
return float4(finalColor, 1);
}