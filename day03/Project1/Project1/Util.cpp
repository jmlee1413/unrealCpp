#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

//
//// a, b 변수를 참조를 위해 새로 만든것
//// call by value 를 이용한 call by reference
//// 실제 값을 넣은거라
//// 게임쪽은 이거쓴다
//void Swap(int* a, int* b)
//{
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//// & 뜻 : 다른데있는 변수를 갖고와서 쓰겠다
//void Swap2(int& a, int& b) // const int& 붙이면 안바뀜
//// 그래서 함수내에서 바꿀떄는 int&, 안바꿀때는 const int&
//// 보자마자 알수있다
//// c++에서만 컴파일가능해서 안쓰기로
//{
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//Position Calculate(Position newPos)
//// 다른 메모리 공간에 받은 newPos를 복사하게된다
//{
//	newPos.x += 1;
//	newPos.y += 1;
//	newPos.z += 1;
//
//	return newPos;
//}
//// 큰파일 읽어오는경우 메모리 잡아먹어서 아래 함수처럼 바꾼다
//
//void Calculate2(Position* newPos)
//{
//	newPos->x += 1;
//	newPos->y += 1;
//	newPos->z += 1;
//	//newPos가 포인터일떄 멤버에 접근할떄 ->를 쓴다
//
//	//return *newPos;
//	//리턴할 필요없음
//}

