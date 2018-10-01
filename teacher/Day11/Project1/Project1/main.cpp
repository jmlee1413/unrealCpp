#include <iostream>
#include "MyVectorT.h"
#include <vector>
#include <list>
#include <algorithm>
#include "Queue.h"
#include <string>
#include "LQueue.h"
#include  <stack>

using namespace std;

//int main()
//{
//	list<int> c;
//	MyVectorT<int> a;
//	for (int i = 0; i < 10; ++i)
//	{
//		a.PushBack(i);
//	}
//
//	for (auto i = a.begin(); i != a.end(); ++i)
//	{
//		cout << *i << ", ";
//	}
//	cout << endl;
//
//	for (auto i : a)
//	{
//		cout << i << ", ";
//	}
//	cout << endl;
//
//	cout << *find(a.begin(), a.end(), 5) << endl;
//	sort(c.begin(), c.end());
//
//	return 0;
//}

int Sum(int n)
{
	int s = 0;
	for (int i = 0; i <= n; ++i)
	{
		s += i;
	}

	return s;
}

int RSum(int n)
{
	if (n == 1)
	{
		return n;
	}

	return n + RSum(n - 1);
}

void ReversePrint(string msg)
{
	for (int i = msg.length()-1; i >= 0; --i)
	{
		cout << msg.substr(i, 1);
	}
	cout << endl;
}

void RReversePrint(string msg)
{
	if (msg.length() == 0)
	{
		return;
	}

	RReversePrint(msg.substr(1));
	cout << msg[0];
}


int ArraySum(int* num, int size)
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += num[i];
	}

	return sum;
}

int RArraySum(int* num, int size)
{
	if (size == 0)
	{
		return 0;
	}

	return num[size - 1] + RArraySum(num, size - 1);
}

int StringLength(char* str)
{
	//while(1) 
	//for(;;)
	for (int i = 0; ; ++i)
	{
		if (str[i] == '\0')
		{
			return i;
		}
	}
}

int RStringLength(char* str)
{
	if (str[0] == '\0')
	{
		return 0;
	}

	return 1 + RStringLength(str+1);
}

//10 -> 1010, %, /
void ToBinary(int n)
{
	//string Binary;
	//while (n >= 1)
	//{
	//	int mod = n % 2;
	//	n = n / 2;
	//	Binary.append(to_string(mod));
	//}

	//RReversePrint(Binary);
	stack<int> Binary;
	while (n >= 1)
	{
		int mod = n % 2;
		n = n / 2;
		Binary.push(mod);
	}

	while (!Binary.empty())
	{
		cout << Binary.top();
		Binary.pop();
	}
}

void RToBinary(int n)
{
	if (n <= 1)
	{
		cout << n;
	}
	else
	{
		RToBinary(n / 2);
		cout << n % 2;
	}
}

//n=3 3*2*1
int Factorial(int n)
{
	int sum = 1;
	for (int i = n; i >= 1; --i)
	{
		sum *= i;
	}

	return sum;
}

int RFactorial(int n)
{
	if (n == 1)
	{
		return n;
	}

	return n * RFactorial(n - 1);
}

int SerchTime = 0;

int Search(int* Data, int Size, int target)
{
	for (int i = Size-1; i >= 0; --i)
	{
		SerchTime++;
		if (Data[i] == target)
		{
			return i;
		}
	}
	
	return -1;
}

int RSearch(int* Data, int Size, int target)
{
	SerchTime++;
	if (Size == 0)
	{
		return -1;
	}

	if (Data[Size-1] == target)
	{
		return Size - 1;
	}

	return RSearch(Data, Size - 1, target);
}

int RSearch2(int* Data, int begin, int end, int target)
{
	SerchTime++;

	if (begin > end)
	{
		return -1;
	}
	else if (Data[begin] == target)
	{
		return begin;
	}
	else
	{
		return RSearch2(Data, begin + 1, end, target);
	}
}


int RSearch3(int* Data, int begin, int end, int target)
{
	SerchTime++;

	if (begin > end)
	{
		return -1;
	}
	else
	{
		int middle = (begin + end) / 2;
		if (Data[middle] == target)
		{
			return middle;
		}
		int index = RSearch3(Data, begin, middle - 1, target);
		if (index != -1)
		{
			return index;
		}
		else
		{
			return RSearch3(Data, middle + 1, end, target);
		}
	}
}


int BSearch(int* Data, int begin, int end, int target)
{
	SerchTime++;

	if (begin > end)
	{
		return -1;
	}
	else
	{
		int middle = (begin + end) / 2;
		if (Data[middle] == target)
		{
			return middle;
		}
		if (Data[middle] > target)
		{
			return BSearch(Data, begin, middle - 1, target);
		}
		else
		{
			return BSearch(Data, middle + 1, end, target);
		}
	}
}


int main()
{
	int Data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	//RSearch(Data, 10, 3);
	cout << BSearch(Data, 0, 9, 3) << endl;
	cout << SerchTime << endl;

	q
}