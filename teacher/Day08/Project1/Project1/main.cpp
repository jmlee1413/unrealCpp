//#include <iostream>
//#include <vector>
//#include <list>
//#include <queue>
//#include <map>
//#include <algorithm>
//
//using namespace std;
//
//int main()
//{
//	vector<int> a;
//	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
//	//for (auto iter : b)
//	//{
//	//	cout << iter << endl;
//	//}
//
//	cout << a.size() << endl;
//
//	a.push_back(1);
//	a.push_back(2);
//	a.push_back(3);
//
//	a.erase(find(a.begin(), a.end(), 2));
//
//	cout << a.size() << endl;
//
//	a.push_back(5);
//	a.push_back(6);
//	a.push_back(7);
//	a.insert(find(a.begin(), a.end(), 5), 20);
//
//
//	//for (int i = 0; i < 3; ++i)
//	//{
//	//	cout << a[i] << endl;
//	//}
//
//	//vector<int>::iterator iter;
//	//map<int, int>::iterator iter2;
//	//list<int>::iterator iter3;
//	//for (auto iter = a.begin(); iter != a.end(); ++iter)
//	//for (auto iter = a.rbegin(); iter != a.rend(); ++iter)
//
//
//	for(auto iter : a)
//	{
//		cout << iter << endl;
//	}
//	
//	
//	return 0;
//}

#include <iostream>
#include "MyVector.h"
#include <vector>
#include "MyT.h"
#include <string>
#include "MyVectorT.h"
#include <stdlib.h>
#include <set>

using namespace std;

template<typename T>
void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}
//
//void Swap(float& a, float& b)
//{
//	float t = a;
//	a = b;
//	b = t;
//}

int main()
{
	//int a = 10;
	//int b = 20;
	//cout << a << ", " << b << endl;
	//Swap<int>(a, b);
	//cout << a << ", " << b << endl;

	//float c = 10.0;
	//float d = 20.0;
	//cout << c << ", " << d << endl;
	//Swap<float>(c, d);
	//cout << c << ", " << d << endl;


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
	//a.Erase(a.Find(20));

	//for (int i = 0; i < a.GetSize(); ++i)
	//{
	//	cout << a.GetValue(i) << " ";
	//}
	//cout << endl;

	//vector<MyT<int, float>> stl;
	//stl.push_back(1);
	//stl.push_back(2);
	//stl.push_back(3);
	//for (auto iter = stl.begin(); iter != stl.end(); ++iter)
	//{
	//	iter = stl.erase(iter);
	//}

	//MyT<int, string> a;
	//MyT<float, int> b;


	//a.a = 10;
	//a.b = "aaa";
	//a.Print();

	//b.a = 11.5f;
	//b.b = 30;
	//b.Print();

	MyVectorT<int> IntVector;
	MyVectorT<float> FloatVector;
	MyVectorT<string> StringVector;
	MyVectorT<MyVector*> MyVectorVector;


	//MyVector a1;
	//for (int i = 0; i < 100; ++i)
	//{
	//	MyVectorVector.PushBack(new MyVector());
	//}

	for (int i = 0; i < 100; ++i)
	{
		IntVector.PushBack(i);
	}

	IntVector[10] = 1020;
	cout << IntVector[10] << endl;

	if (IntVector[1000] == MyVectorT<int>::Empty)
	{
		cout << "empty" << endl;
	}

	//string aaa;
	//string bbb;
	//if (aaa == bbb)
	//{

	//}

	//for (int i = 0; i < 100; ++i)
	//{
	//	FloatVector.PushBack((float)i * 1.1f);
	//}

	//for (int i = 0; i < 100; ++i)
	//{
	//	char Buffer[1024];
	//	sprintf(Buffer, "%d", i);
	//	//string temp = Buffer;
	//	StringVector.PushBack(Buffer);
	//}

	return 0;
}