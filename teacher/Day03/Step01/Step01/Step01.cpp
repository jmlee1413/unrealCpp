#include <stdio.h>
#include "Util.h"


//a,b 변수는 값 참조를 위해서 사용함
// Call By Value를 이용한 Call By reference 구현
void Swap(int* a, int* b)
{
	int temp = 0;

	temp = *a;
	*a = *b;
	*b = temp;
}


typedef struct tagPosition
{
	int x;
	int y;
	int z;
} Position;

Position Calculate(Position* newPos)
{
	newPos->x += 1;
	newPos->y += 2;
	newPos->z += 3;

	//return newPos;
}

int main()
{
	Position pos;
	pos.x = 1;
	pos.y = 2;
	pos.z = 3;

	printf("(%d, %d, %d)\n", pos.x, pos.y, pos.z);
	pos = Calculate(&pos);
	printf("(%d, %d, %d)\n", pos.x, pos.y, pos.z);

}


