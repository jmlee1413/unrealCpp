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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); // Ŀ�� ��ġ�� �÷��̾� ��ġ�� ����

	//����Ǵ°͸� ���ܳ��� �ڽĿ��� �����Ѵ�
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // p ���� ����
	//std::cout << "P";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ٽ� ���� �����
}

void Character::Init()
{
}
