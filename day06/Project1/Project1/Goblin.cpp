#include "Goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin()
{
	cout << "��� ����" << endl;
	SetName("Goblin");
}


Goblin::~Goblin()
{
	cout << "��� ����" << endl;
}

void Goblin::Tick()
{
	cout << name << "ó��" << endl;
}

void Goblin::Draw()
{
	cout << name << "�׸���" << endl;
}
