#include <iostream>
#include "List.h"
#include <list>
using namespace std;

int main()
{
	list<int> STLListTest;
	List TestList;

	//TestList.PushFront(1);
	//TestList.PushFront(2);
	//TestList.PushFront(3);
	//TestList.PushFront(4);
	//TestList.PushFront(5);
	//TestList.PushFront(6);
	//TestList.PushFront(7);

	TestList.PushBack(1);
	TestList.PushBack(2);
	TestList.PushBack(3);
	TestList.PushBack(4);
	TestList.PushBack(5);
	TestList.PushBack(6);
	TestList.PushBack(7);
	TestList.InsertAfter(TestList.Find(6), 8);
	TestList.InsertBefore(TestList.Find(3), 9);

	//TestList.Remove(TestList.Find(2));
	//TestList.Remove(TestList.Find(7));
	//TestList.Remove(TestList.Find(4));

	for (Node* Cursor = TestList.Begin(); Cursor != TestList.End(); Cursor = Cursor->Next)
	{
		cout << Cursor->Data << endl;
	}

	for (Node* Cursor = TestList.REnd(); Cursor != TestList.RBegin(); Cursor = Cursor->Prev)
	{
		cout << Cursor->Data << endl;
	}

	TestList.RemoveAll();

	//STLListTest.erase()

	//STLListTest.push_back(1);
	//STLListTest.push_back(2);
	//STLListTest.push_back(3);
	//for (list<int>::iterator iter = STLListTest.begin(); iter != STLListTest.end(); ++iter)
	////for(auto iter : STLListTest)
	//{
	//	cout << *iter << endl;
	//}

	//for (list<int>::reverse_iterator iter = STLListTest.rbegin(); iter != STLListTest.rend(); ++iter)
	//{
	//	cout << *iter << endl;
	//}

	//TestList.Insert(1);
	//TestList.Insert(2);
	//TestList.Insert(3);
	//TestList.Insert(4);
	//TestList.Insert(5);

	//cout << TestList.Find(2)->Data << endl;

//	TestList.Remove(Find(2));

	//Node* Current = TestList.GetHead();
	//while (Current)
	//{
	//	cout << Current->Data << endl;
	//	Current = Current->Next;
	//}

	//TestList.Remove(3);

	//Current = TestList.GetHead();
	//while (Current)
	//{
	//	cout << Current->Data << endl;
	//	Current = Current->Next;
	//}

	return 0;
}