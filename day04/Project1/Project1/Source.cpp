#include <stdio.h>
#include <conio.h> // �ݼ� ����� Ű��������
#include <stdlib.h>

#define MAXSIZEX 10
#define MAXSIZEY 10

// ���߿� 0x48 �̵����̸� ã�� ����ϱ� ������ �س��°�
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
}; // 2���� ���� 2���� �迭��..

int Input()
{
	int key = _getch(); // Ű���� ����

	//_beep(40000, 0.f); // ���� ����

	return key;
}

void Process(int KeyCode)
{
	// ����
	if (KeyCode == 'q' || KeyCode == 'Q')
	{
		bIsRunning = false;
	}

	// �̵�
	// ȭ���� y�� ���ʿ��� �Ʒ������� Ŀ����
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

	//clear -> ��������������
	if (map[PlayerPosition.Y][PlayerPosition.X] == 3)
	{
		bIsRunning = false;
	}
}

void Rendering()
{
	system("cls"); //ȭ���ʱ�ȭ
	for (int y = 0; y < MAXSIZEY; ++y)
	{
		for (int x = 0; x < MAXSIZEX; ++x)
		{
			// ���� 1�� ���� ����Ʈ
			if (map[y][x] == 1)
			{
				printf(" %d", map[y][x]); // ���� �ڰ� x 
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
	//��ġ�� �ʱ�ȭ
	PlayerPosition.X = 1;
	PlayerPosition.Y = 1;

	while (bIsRunning)
	{
		int keyCode = Input();
		Process(keyCode);
		Rendering();
	}
}