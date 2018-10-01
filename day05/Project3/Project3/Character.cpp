#include "Character.h"
#include "Map.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>



Character::Character()
{
}


Character::~Character()
{
}

void Character::Move(Map * map, int KeyCode )
{
	if (KeyCode == UP)
	{
		if (!map->IsWall(X, Y - 1))
		{
			Y--;
		}
	}
	else if (KeyCode == DOWN)
	{
		if (!map->IsWall(X, Y + 1))
		{
			Y++;
		}
	}
	else if (KeyCode == LEFT)
	{
		if (!map->IsWall(X - 1, Y))
		{
			X--;
		}
	}
	else if (KeyCode == RIGHT)
	{
		if (!map->IsWall(X + 1, Y))
		{
			X++;
		}
	}
}

void Character::Draw()
{
	COORD c;
	c.X = X;
	c.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); // 커서 위치를 플레이어 위치로 변경

	//공통되는것만 남겨놓고 자식에서 구현한다
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // p 색깔 변경
	//std::cout << "P";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 다시 원래 색깔로
}

void Character::Init()
{
}
