#include "Character.h"
#include <iostream>

using namespace std;


Character::Character()
{
	cout << "ĳ���� ����" << endl;
	SetName("Character");
}


Character::~Character()
{
	cout << name <<" ����" << endl;
}


void Character::Tick()
{
	cout << name << "ó��" << endl;
	Move();
}

void Character::Draw()
{
	cout << "ĳ���� �׸���" << endl;
}

void Character::SetName(std::string newName)
{
	cout << name << "�̸�����" << endl;
	name = newName;
}

std::string Character::GetName()
{
	//�̸� ��ȯ
	return name;
}

void Character::Move()
{
	cout << "ĳ���� ����" << endl;
}