#include <stdio.h>
#include <stdlib.h>
#include "Util.h"
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

int main()
{
	//int a = 1;
	//int b = 2;
	//printf("%d %d ", a, b);
	//Swap(&a, &b);
	//Swap2(a, b);
	//
	//printf("%d %d ", a, b);


	//////////////////////
	////struct
	//////////////////////
	//Position p;
	//p.x = 1;
	//p.y = 2;
	//p.z = 3;
	//printf("%d %d %d ", p.x, p.y, p.z);

	//p = Calculate(p);
	//Calculate2(&p);

	//printf("%d %d %d ", p.x, p.y, p.z);


	/////////////////////////
	////문자열
	/////////////////////////

	//// 문자열은 배열이다
	////char a = 'c'; // 한글자 들어감
	//char a[] = "Hello World"; //배열 만들어서 초기화 사이즈는 알아서 잡아줌
	////a[11] = 'z'; //해도 에러안남
	////a[11] = '\0'; // 11번쨰가 끝이다 라고 하는것
	////또는 a[11] = 0;

	//// 'c' "c" 두개는 다르다 c c0 인것

	//printf("%s\n", a);
	//printf("%d\n", strlen(a));

	//char b[1024];
	//strcpy_s(b, a);
	//printf("%s\n", b);
	//printf("%d\n", strlen(b));

	//strcat_s(b, a); // b 뒤에 붙여준다
	//printf("%s\n", b);
	//printf("%d\n", strlen(b));

	//// a, b 비교
	//printf("%d\n", strcmp(b, a)); // 같으면 0
	//printf("%d\n", strcmp(a, b)); // 정렬했을떄 b가 순서가 뒤면 -1
	//char c[] = "zzz";
	//printf("%d\n", strcmp(a, c));

	//// b="what" b에 다시 넣을수 없음
	//sprintf_s(b, "%s", "what"); //s + printf 해서 바꿔준다
	//sprintf_s(b, "Gold: %d", 10);
	////파일출력은 f + printf
	//printf("%s\n", b);

	//const char* p = "abbcd"; // "abbcd"는 나중에 바꿀수없음 const라서
	////그래서 자료형도 const 붙여줌


	///////////////////////
	////파일 입출력
	///////////////////////

	//FILE* fp; // FILE 포인터가 있음
	//FILE* fpout;
	//char Buffer[1024];
	//int total = 0;

	//fp = fopen("C:/JM/day03/data.txt", "r"); //읽기
	//fpout = fopen("C:/JM/day03/dataOut.txt", "w"); // 쓰기

	//fgets(Buffer, 80, fp); //buffer가 한줄씩 읽어서 80자 갖다줌

	//
	//while (strlen(Buffer) > 0)
	//{
	//	// 줄마다 80자 씩 읽어오기
	//	printf("%s\n", Buffer);
	//	Buffer[0] = 0; // buffer 초기화
	//	//memset(Buffer, 0, sizeof(char) * 100); // 초기화 다른버전
	//	fgets(Buffer, 80, fp);

	//	// 문자를 숫자로 바꾸기
	//	int temp = atoi(Buffer);
	//	total += temp;
	//}

	//printf("%d\n", total);
	//fprintf(fpout, "%d", total);

	//fclose(fp); // 열었으면 닫아주기
	//fclose(fpout);

	////////////////////////
	//띄어쓰기 읽기
	////////////////////////

	char Buffer[1024] = { 0, };
	int Data[3][3]; // 3x3 배열
	FILE* fp = fopen("C:/JM/day03/data.txt", "r");


	if (fp) // fp != nullptr (0)
	{
		fgets(Buffer, 1000, fp); // 첫줄만읽고 끝
		printf("%s", Buffer);
		for (int i = 0; i < atoi(Buffer); i++) //첫줄 숫자만큼 읽어오기
		{
			fscanf(fp, "%d %d %d", &Data[i][0], &Data[i][1], &Data[i][2]);
			printf("%d %d %d", Data[i][0], Data[i][1], Data[i][2]);
		}
	}

	return 0;
}

