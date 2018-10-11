// �ȼ� ���̴� �Է¿� ����ü.
struct ps_input
{
	float4 pos:SV_POSITION;
	float2 texCoord: TEXCOORD0;
	float3 lightDir: TEXCOORD1;
	float3 viewDir:  TEXCOORD2;

	float3 T: TEXCOORD3;
	float3 B: TEXCOORD4;
	float3 N: TEXCOORD5;
};

// �ؽ�ó ����.
Texture2D diffuseMap    : register(t0);
Texture2D normalMap     : register(t1);
SamplerState texSampler : register(s0);

// �ȼ� ���̴�(���̴�/���̴�).
float4 main(ps_input input) : SV_TARGET
{
	// ��ָ�
	float4 tangentNormal = normalMap.Sample(
		texSampler, input.texCoord);
	tangentNormal = normalize(tangentNormal * 2 - 1); // 0~1 -> -1~1 �� �ٲ�� 0~1���� �ٽø�������ؼ�

	// ��ָ��� ������ǥ�� �ٲٱ�
	// tbn ���
	float3x3 TBN = float3x3(
		normalize(input.T),
		normalize(input.B),
		normalize(input.N)
	);
	float3 worldNormal = normalize(mul(tangentNormal, transpose(TBN)));

	// ����Ʈ
	float3 lightDir = normalize(input.lightDir);
	float3 diffuse = saturate(dot(worldNormal, -lightDir)); // �÷����ƴ϶� ���ݻ籤

	// ��ǻ���÷�
	float4 albedo = diffuseMap.Sample(texSampler, input.texCoord); // ��ǻ���ؽ�ó
	diffuse = albedo * diffuse; // ��ǻ����� = ��ǻ�����Ʈ * ��ǻ���ؽ���
	//��������Ʈ
	//diffuse = pow(diffuse * 0.5f + 0.5f, 2.0f);

	// ����ŧ��
	float3 specular = 0;
	if (diffuse.x > 0)
	{
		//�ݻ纤��,�交�� ���ϱ�
		float3 reflection = reflect(lightDir, worldNormal);
		float3 viewDir = normalize(input.viewDir);

		specular = dot(reflection, -viewDir);
		specular = saturate(specular);
		specular = pow(specular, 20.0f);
	}

	// �ؽ�ó ���� ��ȯ.
	return float4(diffuse + specular, 1);
}