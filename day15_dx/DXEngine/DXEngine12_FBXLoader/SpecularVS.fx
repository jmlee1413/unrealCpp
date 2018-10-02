//버텍스 세이더
// float4이면 메인에 4번돌아간다
//버텍스 셰이더의 목적은 공간변환을 위한것

//상수버퍼
cbuffer cbPerObject :  register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// register(b0) 붙일수도 안붙일수도있다 걍 선언된순서
// b는 종류별로 다르게붙이면됨 여기선 상수버퍼
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
	float3 normal: NORMAL; // 출력할때는 normal이라고 하면안됨
	//데이터 비어있는거 아무거에 집어넣고 쓴다
	float3 diffuse: TEXCOORD1; //texcoord는 8개까지 사용가능
	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
};
//두개를 모두 반환하기 위해서 구조체하나 만들어주고
//밑에 리턴값을 vs_output으로 바꾼다

// 정점 셰이더.
vs_output main(
	/*float4 pos : POSITION,
	float4 color : COLOR,
	float2 texCoord : TEXCOORD0*/
	vs_input input)
{
	vs_output output;
	// 공간 변환.
	output.pos = mul(input.pos, world);		// 월드 변환.

	//라이트
	float3 lightDir = output.pos - worldLightPosition;
	lightDir = normalize(lightDir); //정규화
	float3 worldNormal = normalize(mul(input.normal, (float3x3)world));// 물체가 가지고있는 노멀값을 월드공간의 노멀값으로 변환해줌
	float3 diffuse = dot(-lightDir.xyz, worldNormal); // 구한방향이 0.0을 바라본다 근디 반대로바라봐야함 그래서 -
	//output.diffuse = diffuse;
	output.diffuse = diffuse * 0.5f + 0.4f;

	//스펙큘러
	float3 viewDir = normalize(output.pos - worldCameraPosition);
	float3 reflection = reflect(lightDir, worldNormal); // Reflect = Light + 2normal(-Light내적normal)
	output.viewDir = viewDir;
	output.reflection = reflection;

	output.pos = mul(output.pos, view);		// 뷰 변환.
	output.pos = mul(output.pos, projection);		// 투영 변환.

	//output.color = color;
	output.texCoord = input.texCoord;
	output.normal = input.normal;

	return output;
}