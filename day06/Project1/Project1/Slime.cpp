#include "Slime.h"
#include <iostream>

using namespace std;


Slime::Slime()
{
	cout << "슬라임생성" << endl;
	SetName("slime");
}


Slime::~Slime()
{
	cout << "슬라임삭제" << endl;
}

void Slime::Tick()
{
	cout << name << "처리" << endl;
}

void Slime::Draw()
{
	cout << name << "그리기" << endl;
}
