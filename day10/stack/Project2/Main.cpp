#include <iostream>
#include "ListStack2.h"
#include "ListStack.h"
using namespace std;

int main()
{
	/*Stack stack(10);
	stack.Resize(100);
	int i = 0;
	while (!stack.IsFull())
	{
		stack.Push(++i);
	}
	
	
	while (!stack.IsEmpty())
	{
		cout << stack.Pop() << endl;
	}
*/
	/*int i = 0;
	while (!stack.IsFull())
	{
		stack.Push(++i);
	}
	while (!stack.IsEmpty())
	{
		cout << stack.Pop() << endl;
	}*/

	ListStack<int> intStack;
	for (int i = 1; i <= 10; ++i)
	{
		intStack.Push(i);
	}
	while (!intStack.IsEmpty())
	{
		cout << intStack.Pop() << endl;
	}

	ListStack2<float> floatStack;
	for (int i = 1; i <= 10; ++i)
	{
		floatStack.Push(i*1.11f);
	}
	while (!floatStack.IsEmpty())
	{
		cout << floatStack.Pop() << endl;
	}
}


