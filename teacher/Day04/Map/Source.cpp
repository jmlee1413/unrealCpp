#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAXSIZEX 10
#define MAXSIZEY 10

#define UP		0x48
#define DOWN	0x50
#define LEFT	0x4B
#define RIGHT	0x4D

typedef struct tagVector2D {
	int X;
	int Y;
} Position;

Position PlayerPoistion;


bool bIsRunning = true;
int map[MAXSIZEX][MAXSIZEY] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int Input()
{
	int key = _getch();

	return key;
}

void Process(int KeyCode)
{
	//종료하자.
	if (KeyCode == 'q' || KeyCode == 'Q')
	{
		bIsRunning = false;
	}
	else if (KeyCode == UP)
	{
		PlayerPoistion.Y--;
	}
	else if (KeyCode == DOWN)
	{
		PlayerPoistion.Y++;
	}
	else if (KeyCode == LEFT)
	{
		PlayerPoistion.X--;
	}
	else if (KeyCode == RIGHT)
	{
		PlayerPoistion.X++;
	}
	
}

void Rendering()
{
	//화면 지우기
	system("cls");
	for (int y = 0; y < MAXSIZEY; ++y)
	{
		for (int x = 0; x < MAXSIZEX; ++x)
		{
			if (map[y][x] == 1) //현재 출력 위치에 정보에 벽이냐?
			{
				printf("%d", map[y][x]);
			}
			else if (y == PlayerPoistion.Y && x == PlayerPoistion.X)
			{
				printf("P");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}


int main()
{
	PlayerPoistion.X = 1;
	PlayerPoistion.Y = 1;

	while (bIsRunning)
	{
		int keyCode = Input();
		Process(keyCode);//이동
		Rendering();
	}


	return 0;
}