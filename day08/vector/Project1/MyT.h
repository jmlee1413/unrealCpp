#pragma once
#include <iostream> // iostream.h ���������� ����� �� �����߱⶧����

template<typename T, typename T2>
// template�� cpp�� ������ ����� �ٳ־���Ѵ�

class MyT
{
public:
	MyT()
	{

	}
	~MyT()
	{

	}

	//T�� �����¸𸣰����� a������ڴ�
	T a; //���ø��� int a ������ ���°ű���

	T2 b;

	void Print()
	{
		std::cout << a << " ";
		std::cout << b << std::endl;
	}
};

