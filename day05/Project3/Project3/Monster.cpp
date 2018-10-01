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
	//�������� ���Ʒ� ������
	//player�� engine�� �������ִµ�
	//monster�� ��ü������ �����̴°� �����Ƿ�
	//����� �����ϵ��� �ϰ���

	int dir = rand() % 4; // ���� �װ��� 0~3
	switch (dir) // if �� ������
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

	// character move�Լ��� �� ����
	//if (dir == 0) // UP
	//{
	//	if (!map->IsWall(x, y - 1)) // ������ Map.h include �ؾ���
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // p ���� ����
	std::cout << "M";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ٽ� ���� �����
}
