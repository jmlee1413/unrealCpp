// �ȼ� ���̴� �Է¿� ����ü.
struct ps_input
{
	float4 pos : SV_POSITION;
	float3 viewReflection : TEXCOORD0;
};

// �ؽ�ó ����.
//Texture2D objTexture;
TextureCube cubeMap : register(t0);
SamplerState objSampler;

// �ȼ� ���̴�(���̴�/���̴�).
float4 main(ps_input input) : SV_TARGET
{
	// ť��� ���� �б�.
	float3 viewReflection
		= normalize(input.viewReflection);

	float3 cubemapColor
		= cubeMap.Sample(objSampler, viewReflection).rgb;

	//return float4(finalColor, 1);
	return float4(cubemapColor, 1);
}