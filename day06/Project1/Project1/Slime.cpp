#include "Slime.h"
#include <iostream>

using namespace std;


Slime::Slime()
{
	cout << "�����ӻ���" << endl;
	SetName("slime");
}


Slime::~Slime()
{
	cout << "�����ӻ���" << endl;
}

void Slime::Tick()
{
	cout << name << "ó��" << endl;
}

void Slime::Draw()
{
	cout << name << "�׸���" << endl;
}
