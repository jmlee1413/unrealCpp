#include "Player.h"
#include "Job.h"
#include "Map.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>



Player::Player()
{
	Init();

}


Player::~Player()
{
}

//character draw�Լ��� ���Ƽ� �׳� ����

//void Player::Move(int KeyCode, Map* map)
//{
	//// �÷��̾� �̵��� ��� �÷��̾� ���ο� �־����
	//if (KeyCode == UP)
	//{
	//	if (!map->IsWall(x, y - 1))
	//		// map->IsUpWall(player) ������ ����°� �������ϴ� �̰� ��ü������ �����̴�
	//	{
	//		y--;
	//		//  Move() �� �ϴ°ź��� UP() ���θ���°� �������̴�
	//		// ������ ���������Ҷ� ���� �������
	//	}
	//}
	//else if (KeyCode == DOWN)
	//{
	//	if (!map->IsWall(x, y + 1))
	//	{
	//		y++;
	//	}
	//}
	//else if (KeyCode == LEFT)
	//{
	//	if (!map->IsWall(x - 1, y))
	//	{
	//		x--;
	//	}
	//}
	//else if (KeyCode == RIGHT)
	//{
	//	if (!map->IsWall(x + 1, y))
	//	{
	//		x++;
	//	}
	//}
//}

void Player::Draw()
{
	Character::Draw(); // �θ� draw �����ϰڴ�.

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // p ���� ����
	std::cout << "P";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ٽ� ���� �����
}

void Player::Init()
{
	Character::Init();

	X = 1;
	Y = 1;
	job = EJob::Farmer;
}
