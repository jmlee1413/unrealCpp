#include <stdio.h>
#include <stdlib.h>

int main()
{
	//int count = 0;
	//int total = 0;
	//printf("��� ���ڸ� �Է��Ͻðڽ��ϱ�\n");
	//scanf_s("%d", &count);
	//printf("%d ���ڸ� �Է����ּ���\n", count);

	//for (int i = 0; i < count; i++)
	//{
	//	int input = 0;
	//	scanf_s("%d", &input);
	//	total += input;
	//}

	//printf("�� : %d\n", total);
	//float avg = float(total) / float(count);
	//printf("��� : %.1f\n", avg);

	FILE* fp;
	FILE* fpout;
	fp = fopen("C:/JM/day04/review/input3.txt", "r");
	fpout = fopen("C:/JM/day04/review/myoutput3.txt", "w");

	char Buffer[1024];
	char tempBuffer[1024];
	long long total = 0;

	if (fp)
	{
		fgets(Buffer, 100, fp);
		int count = atoi(Buffer);
		for (int i = 0; i < count; i++)
		{
			tempBuffer[0] = 0;
			fgets(tempBuffer, 100, fp);
			int temp = atoi(tempBuffer);
			total += temp;
		}
	
	printf("%u %d", total, count);
	
	fprintf(fpout, "�� : %lld\n", total); // long ��½� %lld
	fprintf(fpout, "��� : %f\n", double(total) / double(count)); // �׳� double�� �ٲ��ش�

	fclose(fp);
	fclose(fpout);
	}


	return 0;
}