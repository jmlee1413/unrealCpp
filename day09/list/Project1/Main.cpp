#include <iostream>
#include "List.h"
#include "ListT.h"
using namespace std;


int main()
{
	List TestList;
	TestList.PushBack(0);
	TestList.PushBack(1);
	TestList.PushBack(2);
	TestList.PushBack(3);
	for (List::Iterator iter = TestList.begin(); iter != TestList.end(); ++iter)
	{
		cout << *iter << endl; // iter로는 출력을할수없으니 *로 값을 받아온다
	}

	ListT<int> TestListT;
	TestListT.PushBack(0);
	TestListT.PushBack(1);
	TestListT.PushBack(2);
	TestListT.PushBack(3);
	for (ListT<int>::Iterator iter = TestListT.begin(); iter != TestListT.end(); ++iter)
	{
		cout << *iter << endl; // iter로는 출력을할수없으니 *로 값을 받아온다
	}
	for (ListT<int>::ReverseIterator iter = TestListT.rbegin(); iter != TestListT.rend(); ++iter)
	{
		cout << *iter << endl; // iter로는 출력을할수없으니 *로 값을 받아온다
	}

	ListT<float> TestListTf;
	TestListTf.PushBack(0.1f);
	TestListTf.PushBack(1.1f);
	TestListTf.PushBack(2.1f);
	TestListTf.PushBack(3.1f);
	for (ListT<float>::Iterator iter = TestListTf.begin(); iter != TestListTf.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}