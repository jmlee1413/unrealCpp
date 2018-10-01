#include <iostream>
#include <stack>
#include <conio.h>
#include <queue>

using namespace std;

//미로찾기

#define MAX 5
int Maze[MAX][MAX] = {
	{0, 0, 1, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0},
};

#define PATH 0
#define WALL 1
#define VISITED 2
#define BACKTRACE 3 // 들어가면 안되는곳 막혀있었던곳

class Position
{
public:
	Position(int newx=0, int newy=0) 
	{
		x = newx; 
		y = newy; 
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
			cout << Maze[y][x] << " ";
		}
		cout << endl;
	}
}

void PrintPath()
{
	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			if (Maze[y][x] == PATH)
			{
				cout << "(" << x << "," << y << ")" << endl;
			}
		}
	}
}


bool CanMove(Position& Current)
{
	Position Next;
	//UP
	Next.x = Current.x;
	Next.y = Current.y - 1;

	if (Next.y >= 0)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	//RIGHT
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
	//DOWN
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
	//LEFT
	Next.x = Current.x - 1;
	Next.y = Current.y;
	if (Next.x >= 0)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}

	return false;
}


Position Dir[4];

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
			Next.x > MAX || Next.y > MAX)
		{
			continue; // 맵 밖을 넘어가는거니까 다음꺼 검사한다
		}

		if (Maze[Next.y][Next.x] == PATH)
		{
			Current = Next;
			return true;
		}
	}
	return false;
}

Position RFindPath(Position Current)
{
	//cout << Current.x << " " << Current.y << endl;
	system("cls");
	PrintMap();
	getch();

	int count=0;
	Position Next;
	//UP
	Next.x = Current.x;
	Next.y = Current.y - 1;

	if (Next.y >= 0)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Maze[Current.y][Current.x] = VISITED;
			Current = Next;
			return RFindPath(Current);
		}
		else if (Maze[Next.y][Next.x] == VISITED)
		{
			Current = Next;
			return RFindPath(Current);
		}
		else if (count == 3)
		{
			Maze[Current.y][Current.x] = BACKTRACE;
			Current = Next;
			return RFindPath(Current);
		}
		count++;
	}

	//RIGHT
	Next.x = Current.x + 1;
	Next.y = Current.y;
	if (Next.x < MAX)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Maze[Current.y][Current.x] = VISITED;
			Current = Next;
			return RFindPath(Current);
		}
		else if (Maze[Next.y][Next.x] == VISITED)
		{
			Current = Next;
			return RFindPath(Current);
		}
		else if (count == 3)
		{
			Maze[Current.y][Current.x] = BACKTRACE;
			Current = Next;
			return RFindPath(Current);
		}
		count++;
	}

	//DOWN
	Next.x = Current.x;
	Next.y = Current.y + 1;
	if (Next.y < MAX)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Maze[Current.y][Current.x] = VISITED;
			Current = Next;
			return RFindPath(Current);
		}
		else if (Maze[Next.y][Next.x] == VISITED)
		{
			Current = Next;
			return RFindPath(Current);
		}
		else if (count == 3)
		{
			Maze[Current.y][Current.x] = BACKTRACE;
			Current = Next;
			return RFindPath(Current);
		}
		count++;
	}
	//LEFT
	Next.x = Current.x - 1;
	Next.y = Current.y;
	if (Next.x >= 0)
	{
		if (Maze[Next.y][Next.x] == PATH)
		{
			Maze[Current.y][Current.x] = VISITED;
			Current = Next;
			return RFindPath(Current);
		}
		else if (Maze[Next.y][Next.x] == VISITED)
		{
			Current = Next;
			return RFindPath(Current);
		}
		else if (count == 3)
		{
			Maze[Current.y][Current.x] = BACKTRACE;
			Current = Next;
			return RFindPath(Current);
		}
		count++;
	}

	
	return Position();
}


bool RFindMaze(Position Next)
{
	
	if (Next.x<0 || Next.y<0 ||
		Next.x>MAX || Next.y>MAX)
	{
		return false;
	}
	else if (Maze[Next.y][Next.x] != PATH)
	{
		return false;
	}
	else if (Next.x == MAX - 1 && Next.y == MAX - 1)
	{
		Maze[Next.y][Next.x] = VISITED;
		return true;
	}
	else
	{
		Maze[Next.y][Next.x] = VISITED;
		if (RFindMaze(Position(Next.x, Next.y - 1)) ||
			RFindMaze(Position(Next.x + 1, Next.y)) ||
			RFindMaze(Position(Next.x, Next.y + 1)) ||
			RFindMaze(Position(Next.x - 1, Next.y)))
		{
			return true;
		}

		Maze[Next.y][Next.x] = BACKTRACE;
		return false;
	}
}
int main2()
{

	Position Current;
	Current.x = 0;
	Current.y = 0;
	RFindPath(Current);

	//stack<Position> EscapeMap;

	//while (true)
	//{
	//	Maze[Current.y][Current.x] = VISITED;
	//	if (CanMove2(Current)) // 이동할수있는 상태인가
	//	{
	//		//가능데스 
	//		EscapeMap.push(Current); // 기록한다
	//	}
	//	else
	//	{
	//		if (!EscapeMap.empty())
	//		{
	//			//현재위치에서 이동불가 돌아가야댐
	//			//EscapeMap에서 전 위치를 가져와서 그위치에서 이동테스트
	//			Position Temp = EscapeMap.top(); //자료 꺼내기
	//			EscapeMap.pop(); // remove 
	//			Maze[Current.y][Current.x] = BACKTRACE; //못가는 곳이다 기록
	//			Current = Temp; //이전위치로
	//		}
	//		else
	//		{
	//			cout << "탈출불가" << endl;
	//			break;
	//		}
	//	}

		//system("cls");
		//PrintMap();
		//getch();

	//	if (Current.x == (MAX - 1) && Current.y == (MAX - 1))
	//	{
	//		Maze[Current.y][Current.x] = VISITED;
	//		//system("cls");
	//		//PrintMap();
	//		//getch();
	//		cout << "탈출" << endl;
	//		break;
	//	}
	//	
	//}
	//PrintPath();

	RFindMaze(Current);
	return 0;
}

void InitDir()
{
	//위
	Dir[UP].x = 0;
	Dir[UP].y = -1;
	//right
	Dir[RIGHT].x = 1;
	Dir[RIGHT].y = 0;
	//down
	Dir[DOWN].x = 0;
	Dir[DOWN].y = 1;
	//left
	Dir[LEFT].x = -1;
	Dir[LEFT].y = 0;
}

bool CanMoveQ(Position& Current, Position& NewPosition, int dir)
{
	Position Next;
	Next.x = Current.x + Dir[dir].x;
	Next.y = Current.y + Dir[dir].y;
	
	if (Next.x<0 || Next.y<0 ||
		Next.x>MAX || Next.y>MAX)
	{
		return false;
	}

	if (Maze[Next.y][Next.x] == PATH)
	{
		NewPosition = Next;
		return true;
	}

	return false;
}

void Trace()
{
	//while(!Q.empty())
	//{
	//	Position Temp = Q.front();
	//	cout << Temp.x << ',' << Temp.y << endl;
	//	Q.pop();
	//}
	//return;
	Position Current(MAX - 1, MAX - 1);
	stack<Position> trace;
	trace.push(Current);

	bool found = false;
	while (!(Current.y == 0 && Current.x == 0))
	{
		int Level = Maze[Current.y][Current.x];
		for (int dir = UP; dir <= LEFT; ++dir)
		{
			Position Next(Current.x + Dir[dir].x, Current.y + Dir[dir].y);
			if (Next.x<0 || Next.y<0 ||
				Next.x>=MAX || Next.y>=MAX)
			{
				continue;
			}
			if (Maze[Next.y][Next.x] == Level - 1)
			{
				trace.push(Next);
				Current = Next;
				break;
			}
		}
	}

	while (!trace.empty())
	{
		Position temp = trace.top();
		trace.pop();
		cout << temp.x << " " << temp.y << endl;
	}

}

int main()
{
	queue<Position> Q;
	queue<Position> Q1;
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
		for (int dir = UP; dir < LEFT; ++dir)
		{
			Position NewPos;
			if (CanMoveQ(Current, NewPos, dir))
			{
				Q1.push(Current);
				Maze[NewPos.y][NewPos.x] = Level + 1;
				if (NewPos.x == MAX - 1 && NewPos.y == MAX - 1)
				{
					cout << "탈출" << endl;
					found = true;
					break;
				}

				Q.push(NewPos);
			}
		}
	}

	if (!found)
	{
		cout << "탈출불가" << endl;
	}

	PrintMap();

	if (found)
	{
		Trace();
	}

	return 0;
}