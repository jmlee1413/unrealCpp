struct ps_input
{
	float4 pos:SV_POSITION;

	float2 texCoord: TEXCOORD0;
	float3 normal: NORMAL;
	float3 diffuse: TEXCOORD1;

	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
	float3 viewReflection:TEXCOORD4;
};

// 환경맵
// 뷰벡터에서 큐브맵에 반사된벡터를 텍스처값으로 사용할것이다

// 텍스처 정보.
//Texture2D objTexture;
TextureCube cubeMap : register(t0);
SamplerState objSampler;

// 픽셀 셰이더(쉐이더/셰이더).
float4 main(ps_input input) : SV_TARGET
{
	//	//// 텍스처 샘플링 (색상 정보 추출).
	//	float4 texColor = objTexture.Sample(
	//		objSampler, input.texCoord);
	//
	//// 디퓨즈 색상 추출
	//float3 diffuse = saturate(input.diffuse); // 0이하의 값은 0으로 고정해주는 saturate
	//
	//// 스펙큘러
	//float3 reflection = normalize(input.reflection).xyz;
	//float3 viewDir = normalize(input.viewDir).xyz;
	//float3 specular = 0;
	//
	//if (diffuse.x > 0)
	//{
	//	//뷰벡터와 반사벡터의 내적
	//	specular = dot(reflection, -viewDir);
	//	specular = saturate(specular);
	//
	//	// 코사인그래프를 제곱해서 그래프를 좁게만든다 정반사영역이좁아짐
	//	specular = pow(specular, 30.f);
	//}
	//// 주변광
	//float3 ambient = float3(0.1f, 0.1f, 0.1f);

	// 큐브맵 색상 읽기
	float3 viewReflection = normalize(input.viewReflection); // 페이스 노멀값에 대한 뷰벡터의 반사벡터
	float3 cubemapColor = cubeMap.Sample(objSampler, viewReflection).rgb;

	// 최종색상
	//float3 finalColor = texColor.rgb * diffuse + specular + ambient * 0.5;
	//float3 finalColor = diffuse + specular + ambient;

	// 텍스처 색상 반환.
	return float4(cubemapColor, 1);
}