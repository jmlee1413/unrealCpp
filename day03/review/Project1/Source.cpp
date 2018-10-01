#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Hello World \n");

	int count = 0;
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		printf("%*s", count-i, " ");
		for (int j = 0; j < i + 1; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < count; i++)
	{
		printf("%*s", i+1, " ");
		for (int j = 0; j < count - i; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

	//int nums[100];
	int* nums = (int*)malloc(sizeof(int) * count);

	for (int i = 0; i < count; i++)
	{
		*(nums + i) = i;
	}

	for (int i = 0; i < count; i++)
	{
		printf("%d\n", *(nums + i));
	}

	free(nums);
}

//배열은 포인터
//자료형도 포인터
//malloc 다음에 꼭 free
