#include <iostream>
//#include <vector>
//#include <list>
//#include <queue>
//#include <algorithm>

using namespace std;
//
//int main()
//{
//	//�ڷᱸ��: �迭�� �������� �������ش�
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
//	// a�� ó������ ������ 2�� ã�Ƽ� ������
//	a.erase(find(a.begin(),a.end(), 2));
//	a.insert(a.begin(), 20);
//
//
//	//�ڷᱸ�������� for��
//
//
//	//int ���Ϳ� �����ϴ� ���ͷ�����(�����Ͷ� ���)
//	//vector<int>::iterator iter;
//	//map<int, int>::iterator iter2;
//	//list<int>::iterator iter3;
//
//	//������
//	for (vector<int>::iterator iter = a.begin(); iter != a.end(); ++iter)
//	{
//		cout << *iter << endl;
//	}
//
//	//������
//	for (auto iter = a.rbegin(); iter != a.rend(); ++iter)
//	{
//		cout << *iter << endl;
//	}
//
//	//���ӵ� for��
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
// �̷��� Ÿ�Ը��� ����� �ȴ�
// template <typename t> �Լ����ٰ� �ٿ���


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
	//a.Erase(a.Find(20)); //������ iterate�� ���� ��ߵ�

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
	// string�� ��� memcpy�� for������ �ٲٸ� �����ȳ���

	//MyVectorT<MyVector> MyVectorVector;
	//MyVector a1;
	//MyVectorVector.PushBack(a1);

	//MyVectorT<MyVector*> MyVectorVector; //��Ŭ���������� �����ͷ�
	//MyVectorVector.PushBack(new MyVector());
	

}