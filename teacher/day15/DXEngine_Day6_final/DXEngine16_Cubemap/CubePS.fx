// ÇÈ¼¿ ¼ÎÀÌ´õ ÀÔ·Â¿ë ±¸Á¶Ã¼.
struct ps_input
{
	float4 pos : SV_POSITION;
	float3 viewReflection : TEXCOORD0;
};

// ÅØ½ºÃ³ Á¤º¸.
//Texture2D objTexture;
TextureCube cubeMap : register(t0);
SamplerState objSampler;

// ÇÈ¼¿ ¼ÎÀÌ´õ(½¦ÀÌ´õ/¼ÎÀÌ´õ).
float4 main(ps_input input) : SV_TARGET
{
	// Å¥ºê¸Ê »ö»ó ÀÐ±â.
	float3 viewReflection
		= normalize(input.viewReflection);

	float3 cubemapColor
		= cubeMap.Sample(objSampler, viewReflection).rgb;

	//return float4(finalColor, 1);
	return float4(cubemapColor, 1);
}