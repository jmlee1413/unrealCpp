// 픽셀 셰이더 입력용 구조체.
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

// 텍스처 정보.
Texture2D diffuseMap    : register(t0);
Texture2D normalMap     : register(t1);
SamplerState texSampler : register(s0);

// 픽셀 셰이더(쉐이더/셰이더).
float4 main(ps_input input) : SV_TARGET
{
	// 노멀맵
	float4 tangentNormal = normalMap.Sample(
		texSampler, input.texCoord);
	tangentNormal = normalize(tangentNormal * 2 - 1); // 0~1 -> -1~1 로 바뀐걸 0~1으로 다시만들기위해서

	// 노멀맵을 월드좌표로 바꾸기
	// tbn 행렬
	float3x3 TBN = float3x3(
		normalize(input.T),
		normalize(input.B),
		normalize(input.N)
	);
	float3 worldNormal = normalize(mul(tangentNormal, transpose(TBN)));

	// 라이트
	float3 lightDir = normalize(input.lightDir);
	float3 diffuse = saturate(dot(worldNormal, -lightDir)); // 컬러가아니라 난반사광

	// 디퓨즈컬러
	float4 albedo = diffuseMap.Sample(texSampler, input.texCoord); // 디퓨즈텍스처
	diffuse = albedo * diffuse; // 디퓨즈맵핑 = 디퓨즈라이트 * 디퓨즈텍스쳐
	//하프램버트
	//diffuse = pow(diffuse * 0.5f + 0.5f, 2.0f);

	// 스페큘러
	float3 specular = 0;
	if (diffuse.x > 0)
	{
		//반사벡터,뷰벡터 구하기
		float3 reflection = reflect(lightDir, worldNormal);
		float3 viewDir = normalize(input.viewDir);

		specular = dot(reflection, -viewDir);
		specular = saturate(specular);
		specular = pow(specular, 20.0f);
	}

	// 텍스처 색상 반환.
	return float4(diffuse + specular, 1);
}