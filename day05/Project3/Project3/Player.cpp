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

//character draw함수와 같아서 그냥 없앰

//void Player::Move(int KeyCode, Map* map)
//{
	//// 플레이어 이동은 사실 플레이어 내부에 있어야함
	//if (KeyCode == UP)
	//{
	//	if (!map->IsWall(x, y - 1))
	//		// map->IsUpWall(player) 식으로 만드는게 보기편하다 이게 객체지향의 목적이다
	//	{
	//		y--;
	//		//  Move() 로 하는거보다 UP() 으로만드는게 직관적이다
	//		// 무조건 유지보수할때 편한 방식으로
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
	Character::Draw(); // 부모꺼 draw 실행하겠다.

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // p 색깔 변경
	std::cout << "P";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 다시 원래 색깔로
}

void Player::Init()
{
	Character::Init();

	X = 1;
	Y = 1;
	job = EJob::Farmer;
}
