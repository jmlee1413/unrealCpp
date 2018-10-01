#include <iostream>
//#include <vector>
//#include <list>
//#include <queue>
//#include <algorithm>

using namespace std;
//
//int main()
//{
//	//자료구조: 배열을 동적으로 관리해준다
//	vector<int> a;
//	a.push_back(1);
//	a.push_back(2);
//	a.push_back(3);
//
//	for (int i = 0; i < a.size(); i++)
//	{
//		cout << a[i] << endl;
//	}
//
//	a.erase(a.begin());
//	// #include algorithm
//	// a의 처음부터 끝까지 2를 찾아서 지워라
//	a.erase(find(a.begin(),a.end(), 2));
//	a.insert(a.begin(), 20);
//
//
//	//자료구조에서의 for문
//
//
//	//int 벡터에 접근하는 이터레이터(포인터랑 비슷)
//	//vector<int>::iterator iter;
//	//map<int, int>::iterator iter2;
//	//list<int>::iterator iter3;
//
//	//정방향
//	for (vector<int>::iterator iter = a.begin(); iter != a.end(); ++iter)
//	{
//		cout << *iter << endl;
//	}
//
//	//역방향
//	for (auto iter = a.rbegin(); iter != a.rend(); ++iter)
//	{
//		cout << *iter << endl;
//	}
//
//	//네임드 for문
//	for (auto iter : a)
//	{
//		cout << iter << endl;
//	}
//	
//	return 0;
//}

#include "MyVector.h"
#include "MyT.h"
#include "MyVectorT.h"
#include "stdio.h"

template<typename T>
void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

//void Swap(float& a, float& b)
//{
//	float t = a;
//	a = b;
//	b = t;
//}
// 이렇게 타입마다 만들기 싫다
// template <typename t> 함수에다가 붙여줌


int main()
{
	//MyVector a;
	//for (int i = 0; i < 100; ++i)
	//{
	//	a.PushBack(i);
	//}

	//for (int i = 0; i < a.GetSize(); ++i)
	//{
	//	cout << a.GetValue(i) << " ";
	//}
	//cout << endl;

	//a.Erase(a.Find(10));
	//a.Erase(a.Find(20)); //원래는 iterate를 만들어서 써야됨

	//for (int i = 0; i < a.GetSize(); ++i)
	//{
	//	cout << a.GetValue(i) << " ";
	//}
	//cout << endl;

	/*MyT<int, float> a;
	MyT<float, int> b;

	a.a = 10;
	a.b = 20.1f;
	a.Print();

	b.a = 11.5f;
	b.b = 30;
	b.Print();

	return 0;*/

	int a = 10;
	int b = 20;
	cout << a << " " << b << endl;
	Swap<int>(a, b);
	cout << a << " " << b << endl;

	float c = 10.0;
	float d = 20.0;
	cout << c << " " << d << endl;
	Swap<float>(c, d);
	cout << c << " " << d << endl;

	MyVectorT<int> IntVector;
	MyVectorT<float> FloatVector;
	//MyVectorT<string> StrVector;
	for (int i = 0; i < 100; ++i)
	{
		IntVector.PushBack(i);
	}
	for (int i = 0; i < 100; ++i)
	{
		FloatVector.PushBack(i*1.1f);
	}

	cout << IntVector[10] << endl;
	if (IntVector[1000] == MyVectorT<int>::Empty)
	{
		cout << "empty" << endl;
	}
	//for (int i = 0; i < 100; ++i)
	//{
	//	char Buffer[1024];
	//	sprintf(Buffer, "%d", i);
	//	StrVector.PushBack(Buffer);
	//}
	// string의 경우 memcpy를 for문으로 바꾸면 에러안난다

	//MyVectorT<MyVector> MyVectorVector;
	//MyVector a1;
	//MyVectorVector.PushBack(a1);

	//MyVectorT<MyVector*> MyVectorVector; //내클래스쓸때는 포인터로
	//MyVectorVector.PushBack(new MyVector());
	

}