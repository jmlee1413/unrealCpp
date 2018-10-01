#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

void HelloWorld(int a)
{
	printf("Hello World!\n");
}

void DrawTriagle(int a)
{
	for (int i = 0; i < a; ++i)
	{
		DrawLine(i+1);
	}
}

void DrawReverseTriagle(int a)
{
	for (int i = a; i > 0; --i)
	{
		DrawLine(i);
	}
}

void DrawLine(int a)
{
	for (int i = 0; i < a; ++i)
	{
		printf("*");
	}
	printf("\n");
}

void ArrayTest()
{
	int test[100] = {0};
	//			*----------------*
	//			|test * 100(int) |
	//          *----------------*
	for (int i = 0; i < 100; ++i)
	{
		test[i] = i;
	}

	for (int i = 0; i < 100; ++i)
	{
		printf("%d ", *(test + i));
	}
}

void AllocTest()
{
	int* test = (int*)malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; ++i)
	{
		test[i] = i;
	}

	for (int i = 0; i < 100; ++i)
	{
		printf("%d ", *(test + i));
	}

	free(test);
}