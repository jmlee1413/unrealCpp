#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

#define MAX 10
int MAP3[MAX][MAX] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

int MAP2[MAX][MAX] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,1,1,1,1,0,0},
	{0,0,0,0,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

int MAP[MAX][MAX] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,0,0,0,0,0},
	{0,0,1,0,1,0,0,0,0,0},
	{0,0,1,0,1,1,1,1,0,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
};

#define WALL 0
#define PATH 1
#define VISITED 2

class Position
{
public:
	Position(int tempx, int tempy) 
	{
		x = tempx; 
		y = tempy; 
	}
	int x;
	int y;
};

int onecount;

bool RCountOne(Position Current)
{
	//cout << Current.x << " " << Current.y << endl;

	if (Current.x<0 || Current.y<0 ||
		Current.x>MAX || Current.y>MAX)
	{
		return false;
	}
	else if (MAP[Current.y][Current.x] != PATH)
	{
		return false;
	}
	else if (Current.x == MAX - 1 && Current.y == MAX - 1)
	{
		return false;
	}
	else
	{
		if (MAP[Current.y][Current.x] == PATH)
		{
			MAP[Current.y][Current.x] = VISITED;
		}
		onecount++;
		if (RCountOne(Position(Current.x, Current.y - 1)) ||
			RCountOne(Position(Current.x + 1, Current.y)) ||
			RCountOne(Position(Current.x, Current.y + 1)) ||
			RCountOne(Position(Current.x - 1, Current.y)))
		{
			return true;
		}
		return false;
	}

}

int CountCell(int x, int y)
{
	if (x < 0 || x >= MAX || y < 0 || y >= MAX)
	{
		return 0;
	}
	else if (MAP[y][x] != 1)
	{
		return 0;
	}
	else
	{
		MAP[y][x] = 2;
		return 1 + CountCell(x, y - 1) +
			CountCell(x + 1, y) +
			CountCell(x, y+1) +
			CountCell(x - 1, y);
	}

	return 0;
}

void RFill(int x, int y)
{
	if (x < 0 || x >= MAX || y < 0 || y >= MAX)
	{
		return;
	}
	else if (MAP[y][x] != 0)
	{
		return;
	}
	else
	{
		MAP[y][x] = 1;
		RFill(x, y - 1);
		RFill(x, y + 1);
		RFill(x - 1, y);
		RFill(x + 1, y);
	}
}

void PrintMap()
{
	for (int y = 0; y < MAX - 1; ++y)
	{
		for (int x = 0; x < MAX - 1; ++x)
		{
			cout << MAP[y][x];
		}
		cout << endl;
	}

}

void putPixel(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("#");
}


void drawLine(Position Start, Position End)
{
	//getch();
	Position Middle((Start.x + End.x) / 2, (Start.y + End.y) / 2);
	//cout << Middle.x << Middle.y << endl;
	//cout << Start.x << End.x << Start.y << End.y << endl;
	if ( abs(Start.x-End.x)<=1 && abs(Start.y-End.y)<=1)
	{
		return;
	}
	else
	{
		//cout << (Start.x + End.x) / 2 << (Start.y + End.y) / 2 << endl;
		
		putPixel(Middle.x, Middle.y);
		//cout << Start.x << Middle.x << endl;
		drawLine(Start, Middle);
		drawLine(Middle, End);
		return;
	}

}

void RLine(int startx, int starty, int endx, int endy)
{
	if (abs(startx - endx) <= 1 && abs(starty - endy) <= 1)
	{
		putPixel(startx, starty);
		putPixel(endx, endy);
		return;
	}
	else
	{
		putPixel((startx + endx) / 2, (starty + endy) / 2);
		RLine(startx, starty, (startx + endx) / 2, (starty + endy) / 2);
		RLine((startx + endx) / 2, (starty + endy) / 2, endx, endy );
	}
}


int main()
{
	/*PrintMap();
	RFill(5,4);
	PrintMap();*/

	//Position Current(2, 1);
	//cout << CountCell(2, 1) << endl;
	///*onecount = 0;
	//RCountOne(Current);*/
	//cout << onecount << endl;
	//Position Start(0, 0);
	//Position End(2,2);
	//drawLine(Start, End);
	RLine(2,2,10, 3);
	return 0;
}