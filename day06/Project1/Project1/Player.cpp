#include "Player.h"
#include "conio.h"
#include <iostream>

using namespace std;

Player::Player()
{
	cout << "�÷��̾� ����" << endl;
	SetName("player");
}


Player::~Player()
{
	cout << "�÷��̾� ����" << endl;
}

void Player::Input()
{
	cout << "�÷��̾� �Է�" << endl;
}

void Player::Tick()
{
	Character::Tick();
	cout << name << "ó��" << endl;
}

void Player::Draw()
{
	cout << name << "�׸���" << endl;
}

void Player::Skill1()
{
	cout << "�÷��̾� ��ų" << endl;
}
