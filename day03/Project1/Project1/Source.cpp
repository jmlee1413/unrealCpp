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
	////���ڿ�
	/////////////////////////

	//// ���ڿ��� �迭�̴�
	////char a = 'c'; // �ѱ��� ��
	//char a[] = "Hello World"; //�迭 ���� �ʱ�ȭ ������� �˾Ƽ� �����
	////a[11] = 'z'; //�ص� �����ȳ�
	////a[11] = '\0'; // 11������ ���̴� ��� �ϴ°�
	////�Ǵ� a[11] = 0;

	//// 'c' "c" �ΰ��� �ٸ��� c c0 �ΰ�

	//printf("%s\n", a);
	//printf("%d\n", strlen(a));

	//char b[1024];
	//strcpy_s(b, a);
	//printf("%s\n", b);
	//printf("%d\n", strlen(b));

	//strcat_s(b, a); // b �ڿ� �ٿ��ش�
	//printf("%s\n", b);
	//printf("%d\n", strlen(b));

	//// a, b ��
	//printf("%d\n", strcmp(b, a)); // ������ 0
	//printf("%d\n", strcmp(a, b)); // ���������� b�� ������ �ڸ� -1
	//char c[] = "zzz";
	//printf("%d\n", strcmp(a, c));

	//// b="what" b�� �ٽ� ������ ����
	//sprintf_s(b, "%s", "what"); //s + printf �ؼ� �ٲ��ش�
	//sprintf_s(b, "Gold: %d", 10);
	////��������� f + printf
	//printf("%s\n", b);

	//const char* p = "abbcd"; // "abbcd"�� ���߿� �ٲܼ����� const��
	////�׷��� �ڷ����� const �ٿ���


	///////////////////////
	////���� �����
	///////////////////////

	//FILE* fp; // FILE �����Ͱ� ����
	//FILE* fpout;
	//char Buffer[1024];
	//int total = 0;

	//fp = fopen("C:/JM/day03/data.txt", "r"); //�б�
	//fpout = fopen("C:/JM/day03/dataOut.txt", "w"); // ����

	//fgets(Buffer, 80, fp); //buffer�� ���پ� �о 80�� ������

	//
	//while (strlen(Buffer) > 0)
	//{
	//	// �ٸ��� 80�� �� �о����
	//	printf("%s\n", Buffer);
	//	Buffer[0] = 0; // buffer �ʱ�ȭ
	//	//memset(Buffer, 0, sizeof(char) * 100); // �ʱ�ȭ �ٸ�����
	//	fgets(Buffer, 80, fp);

	//	// ���ڸ� ���ڷ� �ٲٱ�
	//	int temp = atoi(Buffer);
	//	total += temp;
	//}

	//printf("%d\n", total);
	//fprintf(fpout, "%d", total);

	//fclose(fp); // �������� �ݾ��ֱ�
	//fclose(fpout);

	////////////////////////
	//���� �б�
	////////////////////////

	char Buffer[1024] = { 0, };
	int Data[3][3]; // 3x3 �迭
	FILE* fp = fopen("C:/JM/day03/data.txt", "r");


	if (fp) // fp != nullptr (0)
	{
		fgets(Buffer, 1000, fp); // ù�ٸ��а� ��
		printf("%s", Buffer);
		for (int i = 0; i < atoi(Buffer); i++) //ù�� ���ڸ�ŭ �о����
		{
			fscanf(fp, "%d %d %d", &Data[i][0], &Data[i][1], &Data[i][2]);
			printf("%d %d %d", Data[i][0], Data[i][1], Data[i][2]);
		}
	}

	return 0;
}

