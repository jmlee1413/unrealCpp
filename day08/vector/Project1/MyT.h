#pragma once
#include <iostream> // iostream.h 없는이유는 헤더에 다 구현했기때문에

template<typename T, typename T2>
// template은 cpp를 못쓴다 헤더에 다넣어야한다

class MyT
{
public:
	MyT()
	{

	}
	~MyT()
	{

	}

	//T가 뭔지는모르겠지만 a를만들겠다
	T a; //템플릿을 int a 쓰듯이 쓰는거구만

	T2 b;

	void Print()
	{
		std::cout << a << " ";
		std::cout << b << std::endl;
	}
};

