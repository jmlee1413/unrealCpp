#include "Player.h"
#include "conio.h"
#include <iostream>

using namespace std;

Player::Player()
{
	cout << "플레이어 생성" << endl;
	SetName("player");
}


Player::~Player()
{
	cout << "플레이어 삭제" << endl;
}

void Player::Input()
{
	cout << "플레이어 입력" << endl;
}

void Player::Tick()
{
	Character::Tick();
	cout << name << "처리" << endl;
}

void Player::Draw()
{
	cout << name << "그리기" << endl;
}

void Player::Skill1()
{
	cout << "플레이어 스킬" << endl;
}
