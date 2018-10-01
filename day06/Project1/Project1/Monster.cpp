#include "Monster.h"
#include <iostream>

using namespace std;


Monster::Monster()
{
	cout << "몬스터 생성" << endl;
	SetName("Monster");
}


Monster::~Monster()
{
	cout << "몬스터 삭제" << endl;
}

void Monster::GiveItem()
{
	cout << "몬스터가 아이템 준다" << endl;
}
