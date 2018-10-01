#include <stdio.h>

int main()
{
	int a = 2;
	int* b = &a; // char의 포인터면 char* 인거임

	printf("%x", &a);
	printf("%x", b);

	return 0;
}