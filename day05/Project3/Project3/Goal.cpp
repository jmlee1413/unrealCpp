#include "Goal.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>


Goal::Goal()
{
}


Goal::~Goal()
{
}

void Goal::Draw()
{
	COORD c;
	c.X = X;
	c.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); // Ŀ�� ��ġ�� goal ��ġ�� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //g ���� ����

	std::cout << "G";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ٽ� ���� �����
}
