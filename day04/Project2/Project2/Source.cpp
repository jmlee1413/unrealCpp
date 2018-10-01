#include <iostream> //c++ 에서쓰는 stdio.h
#include <string> // c++ 에서 제공하는 문자열
// c++ 라이브러리는 .h가 없다
#include "Apple.h"

using namespace jm;

int main()
{
	//Apple a; //메모리에 만들어주세요
	Apple a; // jm이 만든사과
	a.weight = 10;
	a.quality = 1;
	a.Calculate();

	std::cout << a.GetPrice() << std::endl;


	//Apple aa[10];
	//c: malloc
	//c++: new
	int size = 10;
	Apple* aa = new Apple[size]; // new 사용하면 size값을 아무렇게넣을수 있음
	for (int i = 0; i < 10; ++i)
	{
		aa[i].weight = rand() % 100; //두자리
		aa[i].quality = rand() % 10; //한자리
		aa[i].Calculate();

		std::cout << aa[i].GetPrice() << std::endl;
	}

	//c : free
	//c++ : delete
	
	delete[] aa; // 배열로 만들면 []붙여준다

	Apple* b = new Apple();
	delete b;
}