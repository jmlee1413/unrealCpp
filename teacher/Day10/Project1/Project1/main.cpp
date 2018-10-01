#include <iostream>
#include "List.h"
#include <list>
#include <string>
#include "TList.h"
using namespace std;

int main()
{
	List<int> IntList;
	for (int i = 1; i <= 10; ++i)
	{
		IntList.PushBack(i);
	}

	IntList.Remove(IntList.Find(6));

	for (List<int>::Iterator iter = IntList.begin(); iter != IntList.end(); ++iter)
	{
		//cout.<<(iter->Data) cout.<<(endl);
		cout << *iter << endl;
	}

	//cout << *IntList.Find(9) << endl;

	//List<float> FloatList;
	//for (int i = 1; i <= 10; ++i)
	//{
	//	FloatList.PushBack((float)i * 1.1f);
	//}

	//for (auto iter = FloatList.begin(); iter != FloatList.end(); ++iter)
	//{
	//	//cout.<<(iter->Data) cout.<<(endl);
	//	cout << *iter << endl;
	//}

	//for (auto iter : FloatList)
	//{
	//	cout << iter << endl;
	//}


	return 0;
}