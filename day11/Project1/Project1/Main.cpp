#include "Queue.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int main()
{
	Queue<int> q1;
	for (int i = 0; i < 10; ++i)
	{
		q1.EnQueue(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << q1.Dequeue() << endl;

	}

	q1.EnQueue(199);
	q1.EnQueue(199);
	q1.EnQueue(199);

	/*for (int i = 0; i < 10; ++i)
	{
		cout << q1.Dequeue() << endl;
	}*/
	for (auto iter : q1)
	{
		cout << iter << endl;
	}


	return 0;

}
