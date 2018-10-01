#include <stdio.h> //standard input output
#include <stdlib.h> // malloc 

#define NUM 10 // c에서 쓰는방식 

int main() // entry point : exe실행시 메모리에 올라감
{
	//int a = 100;
	//printf("Hello World. %x", &a); // & -> a가들어있는 메모리주소
	//// %d %x

	//// 1byte가 8bit라 ascii로는 한글표현이안됨
	//// 그래서 유니코드를쓴다
	//// utf8은 8bit가 한글자인애 32bit가 한글자인애 왔다갔다해줌

	//char b = 98; // -128 ~ 127 (0) 까지 표현가능 (1bit를 빼서 +- 표현)
	//unsigned char c = 98; // 글자에 마이너스를 안쓰겠다는 뜻 0~255까지 표현
	//printf("Hello World. %c", b);
	//// 98넣어도 %c로 출력하면 글자나옴

	//// int 32bit 인데 윈도우가 32bit면 램 4기가까지밖에안써짐
	//// 그래서 os에 따라 int 크기가 다르다
	//// 그래서 언리얼에서 int32 처럼 쓰는것
	//int d;
	//printf(" aaa %d", sizeof(d));
	//unsigned int e = 0xffffffff; // int중 가장 큰수
	//printf(" largest int %u", e);

	//char r, g, b, a; // 0~255 포토샵 rgba가 char였던것


	////////////////////////
	////pointer//
	////////////////////////
	//int a = 2;
	//int* b = &a; // char의 포인터면 char* 인거임

	//printf("%x\n", &a);
	//printf("%d\n", b);
	//printf("%d\n", *b); //b가 *참조하는것

	//a = 3;
	//*b = 3; // 두개 똑같음

	//printf("%d\n", a);
	//printf("%d\n", *b);

	////unsigned char* a = 0x00000000; // 처럼 하드웨어 주소값에 바로접근할수있다
	//// 좋긴한데 메모리에 os영역 해킹의위험이있어서 다른프로그램은 못건든다
	//// DirectX 는 그래픽카드에 바로 접근할수있는것
	//// OpenGL Metal Vulkan 등등있음


	///////////////////////////
	/////배열과 반복문
	///////////////////////////

	////int kor[NUM];
	////int eng[NUM];
	////int math[NUM];
	////float avg[NUM]; NUM 적어주는대로 바뀐다

	//int count = 0;
	//scanf("%d", &count);

	//int* kor = (int*)malloc(sizeof(int)*count); 
	//int* eng = (int*)malloc(sizeof(int)*count);
	//int* math = (int*)malloc(sizeof(int)*count);
	//float* avg = (float*)malloc(sizeof(float)*count);
	//// 배열 만드는 대신 NUM 사이즈만큼 메모리 할당
	//// 배열을 포인터로 표현가능
	//// 하드코딩을 피하는 방법

	//for (int i = 0; i < count; i++)
	//{
	//	kor[i] = 100;
	//	eng[i] = 90;
	//	math[i] = 80;
	//	avg[i] = (kor[i] + eng[i] + math[i]) / 3;
	//	printf("%f\n", *(avg + i));
	//}

	//free(kor); // 선언하면 무조건 메모리 풀어주기
	//free(eng);
	//free(math);
	//free(avg);

	int count = 0;
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

}
