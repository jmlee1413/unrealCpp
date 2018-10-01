#include <iostream> //c++ �������� stdio.h
#include <string> // c++ ���� �����ϴ� ���ڿ�
// c++ ���̺귯���� .h�� ����
#include "Apple.h"

using namespace jm;

int main()
{
	//Apple a; //�޸𸮿� ������ּ���
	Apple a; // jm�� ������
	a.weight = 10;
	a.quality = 1;
	a.Calculate();

	std::cout << a.GetPrice() << std::endl;


	//Apple aa[10];
	//c: malloc
	//c++: new
	int size = 10;
	Apple* aa = new Apple[size]; // new ����ϸ� size���� �ƹ����Գ����� ����
	for (int i = 0; i < 10; ++i)
	{
		aa[i].weight = rand() % 100; //���ڸ�
		aa[i].quality = rand() % 10; //���ڸ�
		aa[i].Calculate();

		std::cout << aa[i].GetPrice() << std::endl;
	}

	//c : free
	//c++ : delete
	
	delete[] aa; // �迭�� ����� []�ٿ��ش�

	Apple* b = new Apple();
	delete b;
}