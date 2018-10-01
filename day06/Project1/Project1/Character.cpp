#include "Character.h"
#include <iostream>

using namespace std;


Character::Character()
{
	cout << "캐릭터 생성" << endl;
	SetName("Character");
}


Character::~Character()
{
	cout << name <<" 삭제" << endl;
}


void Character::Tick()
{
	cout << name << "처리" << endl;
	Move();
}

void Character::Draw()
{
	cout << "캐릭터 그리기" << endl;
}

void Character::SetName(std::string newName)
{
	cout << name << "이름세팅" << endl;
	name = newName;
}

std::string Character::GetName()
{
	//이름 반환
	return name;
}

void Character::Move()
{
	cout << "캐릭터 무브" << endl;
}