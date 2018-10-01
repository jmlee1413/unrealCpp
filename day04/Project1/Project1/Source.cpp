#include <stdio.h>
#include <conio.h> // 콜솔 입출력 키보드모니터
#include <stdlib.h>

#define MAXSIZEX 10
#define MAXSIZEY 10

// 나중에 0x48 이딴식이면 찾기 힘드니까 디파인 해놓는것
#define UP    0x48 
#define DOWN  0x50 
#define LEFT  0x4B 
#define RIGHT 0x4D

typedef struct tagVector2D
{
	int X;
	int Y;
} Vector2D;

Vector2D PlayerPosition;

bool bIsRunning = true;
int map[MAXSIZEX][MAXSIZEY] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,3,1},
	{1,1,1,1,1,1,1,1,1,1}
}; // 2차원 맵은 2차원 배열로..

int Input()
{
	int key = _getch(); // 키값을 받음

	//_beep(40000, 0.f); // 비프 사운드

	return key;
}

void Process(int KeyCode)
{
	// 종료
	if (KeyCode == 'q' || KeyCode == 'Q')
	{
		bIsRunning = false;
	}

	// 이동
	// 화면은 y가 위쪽에서 아래쪽으로 커진다
	else if (KeyCode == UP)
	{
		if(map[PlayerPosition.Y-1][PlayerPosition.X] != 1)
			PlayerPosition.Y--;
	}
	else if (KeyCode == DOWN)
	{
		if (map[PlayerPosition.Y + 1][PlayerPosition.X] != 1)
			PlayerPosition.Y++;
	}
	else if (KeyCode == LEFT)
	{
		if(map[PlayerPosition.Y][PlayerPosition.X-1] != 1)
			PlayerPosition.X--;
	}
	else if (KeyCode == RIGHT)
	{
		if (map[PlayerPosition.Y][PlayerPosition.X + 1] != 1)
			PlayerPosition.X++;
	}

	//clear -> 다음스테이지로
	if (map[PlayerPosition.Y][PlayerPosition.X] == 3)
	{
		bIsRunning = false;
	}
}

void Rendering()
{
	system("cls"); //화면초기화
	for (int y = 0; y < MAXSIZEY; ++y)
	{
		for (int x = 0; x < MAXSIZEX; ++x)
		{
			// 값이 1인 벽만 프린트
			if (map[y][x] == 1)
			{
				printf(" %d", map[y][x]); // 보통 뒤가 x 
			}
			else if (y == PlayerPosition.Y && x == PlayerPosition.X)
			{
				printf(" P");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}


int main()
{
	//위치값 초기화
	PlayerPosition.X = 1;
	PlayerPosition.Y = 1;

	while (bIsRunning)
	{
		int keyCode = Input();
		Process(keyCode);
		Rendering();
	}
}