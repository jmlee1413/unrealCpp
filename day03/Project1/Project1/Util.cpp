#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

//
//// a, b ������ ������ ���� ���� �����
//// call by value �� �̿��� call by reference
//// ���� ���� �����Ŷ�
//// �������� �̰ž���
//void Swap(int* a, int* b)
//{
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//// & �� : �ٸ����ִ� ������ ����ͼ� ���ڴ�
//void Swap2(int& a, int& b) // const int& ���̸� �ȹٲ�
//// �׷��� �Լ������� �ٲ܋��� int&, �ȹٲܶ��� const int&
//// ���ڸ��� �˼��ִ�
//// c++������ �����ϰ����ؼ� �Ⱦ����
//{
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//Position Calculate(Position newPos)
//// �ٸ� �޸� ������ ���� newPos�� �����ϰԵȴ�
//{
//	newPos.x += 1;
//	newPos.y += 1;
//	newPos.z += 1;
//
//	return newPos;
//}
//// ū���� �о���°�� �޸� ��ƸԾ �Ʒ� �Լ�ó�� �ٲ۴�
//
//void Calculate2(Position* newPos)
//{
//	newPos->x += 1;
//	newPos->y += 1;
//	newPos->z += 1;
//	//newPos�� �������ϋ� ����� �����ҋ� ->�� ����
//
//	//return *newPos;
//	//������ �ʿ����
//}

