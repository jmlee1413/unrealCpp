#include "Monster.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include "Map.h"

Monster::Monster()
{

}


Monster::~Monster()
{
}

//void Monster::Init()
//{
//	Character::Init();
//}

void Monster::Move(Map* map, int KeyCode)
{
	//랜덤으로 위아래 움직임
	//player는 engine이 움직여주는데
	//monster가 자체적으로 움직이는게 맞으므로
	//여기다 구현하도록 하겠음

	int dir = rand() % 4; // 방향 네가지 0~3
	switch (dir) // if 와 같은것
	{
		case 0:
			KeyCode = UP;
			break;
		case 1:
			KeyCode = DOWN;
			break;
		case 2:
			KeyCode = LEFT;
			break;
		case 3:
			KeyCode = RIGHT;
			break;
	}

	Character::Move(map, KeyCode);

	// character move함수를 쓸 것임
	//if (dir == 0) // UP
	//{
	//	if (!map->IsWall(x, y - 1)) // 쓸려면 Map.h include 해야함
	//	{
	//		y--;
	//	}
	//}
	//else if (dir == 1) // DOWN
	//{
	//	if (!map->IsWall(x, y + 1)) 
	//	{
	//		y++;
	//	}
	//}
	//else if (dir == 2) // LEFT
	//{
	//	if (!map->IsWall(x-1, y))
	//	{
	//		x--;
	//	}
	//}
	//else if (dir == 3) //RIGHT
	//{
	//	if (!map->IsWall(x+1, y))
	//	{
	//		x++;
	//	}
	//}
}

void Monster::Draw()
{
	Character::Draw();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // p 색깔 변경
	std::cout << "M";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 다시 원래 색깔로
}
