#include "Goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin()
{
	cout << "고블린 생성" << endl;
	SetName("Goblin");
}


Goblin::~Goblin()
{
	cout << "고블린 삭제" << endl;
}

void Goblin::Tick()
{
	cout << name << "처리" << endl;
}

void Goblin::Draw()
{
	cout << name << "그리기" << endl;
}
