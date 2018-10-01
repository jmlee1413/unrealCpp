#include <stdio.h>
#include <stdlib.h>

int main()
{
	int count = 0;
	long long total = 0;
	int temp;

	scanf("%d", &count);
	for (int i = 0; i < count; i++)
	{
		scanf("%d", &temp);
		total = total + temp;
	}

	printf("합 : %lld\n", total);
	printf("평균 : %f\n", (double)total / (double)count);


	return 0;
}