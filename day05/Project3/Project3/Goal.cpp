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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); // 커서 위치를 goal 위치로 변경
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //g 색깔 변경

	std::cout << "G";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 다시 원래 색깔로
}
