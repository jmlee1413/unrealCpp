#include "Vector.h"
#include <iostream>

using namespace std;
int main()
{
	Vector<int> v1;
	v1.PushBack(0);
	v1.PushBack(1);
	v1.PushBack(2);

	v1.Remove(1);
	//for (int i = 0; i < v1.GetSize(); ++i)
	//{
	//	cout << v1.GetValue(i) << endl;
	//}
	for (Vector<int>::Iterator iter = v1.begin(); iter != v1.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}