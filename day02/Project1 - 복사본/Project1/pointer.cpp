#include <stdio.h>

int main()
{
	int a = 2;
	int* b = &a; // char�� �����͸� char* �ΰ���

	printf("%x", &a);
	printf("%x", b);

	return 0;
}