#include <iostream>
#include <stack>
#include <conio.h>
#include <queue>

using namespace std;

#define MAX 5

int Maze[MAX][MAX] = {
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 1, 1, 1},
	{1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0}
};

#define PATH 0
#define WALL 1
#define VISITED 2
#define BACKTRACE 3

class Position
{
public:
	Position(int NewX = 0, int NewY = 0) 
	{
		x = NewX;
		y = NewY;
	}
	int x;
	int y;
};

void PrintMap()
{
	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			cout << Maze[y][x] << '\t';
		}
		cout << endl;
	}
}

void PrintPath() //���ÿ�
{
	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			if (Maze[y][x] == VISITED)
			{
				cout << "(" << x << ", " << y << ")" << endl;
			}
		}
	}
}

Position Dir[4];


bool CanMove(Position& Current)
{
	Position Next;

	//Up
	Next.x = Current.x;
	Next.y = Current.y - 1;

	if (Next.y > -1) 
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	//Right
	Next.x = Current.x + 1;
	Next.y = Current.y;
	if (Next.x < MAX)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	//Down
	Next.x = Current.x;
	Next.y = Current.y + 1;
	if (Next.y < MAX)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	//Left
	Next.x = Current.x - 1;
	Next.y = Current.y;
	if (Next.x > -1)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	return false;
}

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

bool CanMove2(Position& Current)
{
	Position Next;

	for (int i = UP; i <= LEFT; ++i)
	{
		Next.x = Current.x + Dir[i].x;
		Next.y = Current.y + Dir[i].y;

		if (Next.x < 0 || Next.y < 0 ||
			Next.x > MAX || Next.y > MAX) // �迭 ���� ���� ����� �̵� �Ұ�
		{
			continue;
		}

		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	return false;
}

bool RFindMaze(Position Current)
{
	if (Current.x < 0 || Current.y < 0 ||
		Current.x > MAX || Current.y > MAX) //�迭�� ���
	{
		return false;
	}
	else if (Maze[Current.y][Current.x] != PATH) //���� �ƴϸ� ����
	{
		return false;
	}
	else if (Current.x == (MAX - 1) && Current.y == (MAX - 1)) //������ ����
	{
		Maze[Current.y][Current.x] = VISITED;
		return true;
	}
	else
	{
		Maze[Current.y][Current.x] = VISITED;
		if (RFindMaze(Position(Current.x, Current.y - 1)) ||
			RFindMaze(Position(Current.x + 1, Current.y)) ||
			RFindMaze(Position(Current.x, Current.y + 1)) ||
			RFindMaze(Position(Current.x - 1, Current.y))) //���� ����(4����)
		{
			return true;
		}

		Maze[Current.y][Current.x] = BACKTRACE;
		return false;
	}

}

int BFSMaze()
{
	//UP
	Dir[UP].x = 0;
	Dir[UP].y = -1;

	//Right
	Dir[RIGHT].x = 1;
	Dir[RIGHT].y = 0;

	//Down
	Dir[DOWN].x = 0;
	Dir[DOWN].y = 1;

	//Left
	Dir[LEFT].x = -1;
	Dir[LEFT].y = 0;

	Position Current;
	Current.x = 0;
	Current.y = 0;

	RFindMaze(Current);

	//stack<Position> EscapeMap;

	//while (true)
	//{
	//	Maze[Current.y][Current.x] = VISITED;
	//	if (CanMove2(Current))
	//	{
	//		//�̵� ����
	//		EscapeMap.push(Current);
	//	}
	//	else
	//	{
	//		if (!EscapeMap.empty()) //�ǵ��� ������ �ֳ�?
	//		{
	//			//���� ��ġ���� �̵� �Ұ���
	//			//map���� �� ��ġ�� �����ͼ� �ű⼭ �̵� �׽�Ʈ
	//			Position Temp = EscapeMap.top(); //�ڷ� ������
	//			EscapeMap.pop(); //remove
	//			Maze[Current.y][Current.x] = BACKTRACE;
	//			Current = Temp;
	//		}
	//		else
	//		{
	//			cout << "Not Escape" << endl;
	//			break;
	//		}
	//	}

	//	//system("cls");
	//	//PrintMap();
	//	//getch();


	//	if (Current.x == (MAX - 1) && Current.y == (MAX - 1))
	//	{
	//		Maze[Current.y][Current.x] = VISITED;
	//		cout << "Ż��" << endl;
	//		break;
	//	}
	//}

	////system("cls");
	////PrintMap();
	////getch();

	PrintPath();

	return 0;

}

void InitDir()
{
	//UP
	Dir[UP].x = 0;
	Dir[UP].y = -1;

	//Right
	Dir[RIGHT].x = 1;
	Dir[RIGHT].y = 0;

	//Down
	Dir[DOWN].x = 0;
	Dir[DOWN].y = 1;

	//Left
	Dir[LEFT].x = -1;
	Dir[LEFT].y = 0;
}

void Trace()
{
	Position Current(MAX - 1, MAX - 1);
	stack<Position> Trace;
	Trace.push(Current);

	bool found = false;
	while (Current.y != 0 || Current.x != 0)
	{
		int Level = Maze[Current.y][Current.x];

		for (int dir = UP; dir <= LEFT; ++dir)
		{
			Position Next(Current.x + Dir[dir].x, Current.y + Dir[dir].y);
			if (Next.x < 0 || Next.y < 0 ||
				Next.x >= MAX || Next.y >= MAX) //�迭�� ���
			{
				continue;
			}
			if (Maze[Next.y][Next.x] == Level - 1)
			{
				Trace.push(Next);
				Current = Next;
				break;
			}
		}
	}

	while (!Trace.empty())
	{
		Position Temp = Trace.top();
		Trace.pop();
		cout << "(" << Temp.x << ", " << Temp.y << ")" << endl;
	}
}

bool CanMoveQ(Position& Current, Position& NewPostion, int dir) //�̸� ������
{
	Position Next;
	Next.x = Current.x + Dir[dir].x;
	Next.y = Current.y + Dir[dir].y;

	if (Next.x < 0 || Next.y < 0 ||
		Next.x > MAX || Next.y > MAX) //�迭�� ���
	{
		return false;
	}
	
	if (Maze[Next.y][Next.x] == PATH) //���� ������ true
	{
		NewPostion = Next;
		return true;
	}

	return false; //���� �ƴϸ�
}


int main()
{
	queue<Position> Q;
	InitDir();
	Position Current;

	Q.push(Current);
	Maze[Current.y][Current.x] = 10;
	bool found = false;
	while (!Q.empty())
	{
		Current = Q.front();
		Q.pop();
		int Level = Maze[Current.y][Current.x];
		for (int dir = UP; dir <= LEFT; ++dir)
		{
			Position NewPosition;
			if (CanMoveQ(Current, NewPosition, dir))
			{
				Maze[NewPosition.y][NewPosition.x] = Level + 1;
				if (NewPosition.x == (MAX - 1) && NewPosition.y == (MAX - 1))
				{
					cout << "Ż��" << endl;
					found = true;
					break;
				}

				Q.push(NewPosition);
			}
		}
	}

	if (!found)
	{
		cout << "Ż�� �Ұ�" << endl;
	}

	PrintMap();
	if (found)
	{
		Trace();
	}

	return 0;
}
