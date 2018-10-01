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

	float3 finalColor = texColor.rgb * diffuse;

// �ؽ�ó ���� ��ȯ.
return float4(finalColor, 1);
}