#pragma once
#include <iostream>

template<typename T, typename T2>
class MyT
{
public:
	MyT()
	{

	}

	~MyT()
	{

	}

	T a;
	T2 b;

	void Print()
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;

	}
};

