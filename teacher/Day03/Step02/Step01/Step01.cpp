#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"

//int main()
//{
//	FILE* fp;
//	FILE* fpout;
//	int total = 0;
//	char Buffer[1024];
//
//	fp = fopen("c:/Data/data.txt", "r");
//	fpout = fopen("c:/Data/output.txt", "w");
//
//	fgets(Buffer, 80, fp);
//	while (strlen(Buffer) > 0)
//	{
//		int temp = atoi(Buffer); //문자열 "10" -> 10 int
//		total += temp;
//		memset(Buffer, 0, sizeof(char) * 100);
//		fgets(Buffer, 80, fp);
//	}
//
//	fprintf(fpout, "%d\n", total);
//
//	fclose(fp);
//	fclose(fpout);
//}

using namespace std;

int main()
{
	//char Buffer[1024] = { 0, };
	//int Data[3][3];
	//FILE* fp = fopen("c:/Data/data.txt", "r");


	//if (fp)
	//{
	//	fgets(Buffer, 1000, fp);

	//	for (int i = 0; i < atoi(Buffer); ++i)
	//	{
	//		fscanf(fp, "%d %d %d", &Data[i][0], &Data[i][1], &Data[i][2]);
	//	}
	//}


	//Step01.exe < "c:\JM\Day03\data.txt" > "c:\JM\Day03\output2.txt"
	int count;
	int Data[3][3];
	scanf("%d", &count);
	//printf("%d", count);

	for (int i = 0; i < count; ++i)
	{
		scanf("%d %d %d", &Data[i][0], &Data[i][1], &Data[i][2]);
	}

	for (int i = 0; i < count; ++i)
	{
		printf("%d %d %d\n", Data[i][0], Data[i][1], Data[i][2]);
	}
}
