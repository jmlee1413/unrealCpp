#include <iostream>
#include <string>
#include <stack>
using namespace std;

void Sum(int n)
{
	int sum = 0;
	for (int i = 0; i <= 10; ++i)
	{
		sum += i;
	}
	cout << sum << endl;
}

int RSum(int n)
{
	if (n == 0)
	{
		return n;
	}

	return n+RSum(n - 1);

}

void RPrint(string msg)
{
	for (int i = msg.length()-1; i >= 0; i--)
	{
		cout << msg[i];
	}
}

void RRPrint(string msg)
{
	if (msg.length() == 0)
	{
		return;
	}
	RRPrint(msg.substr(1));
	cout << msg[0];
}

int SumArray(int* num, int size)
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += num[i];
	}
	return sum;
}

int RSumArray(int* num, int size)
{
	if (size == 0)
	{
		return 0;
	}
	return num[size-1] + RSumArray(num, size - 1);
}

int StrLength(string str)
{
	//무한반복
	//while(1)
	//for(;;)
	for (int i = 0; ; ++i)
	{
		if (str[i] == '\0')
		{
			return i ;
		}
	}
}

int RStrLength(char* str)
{
	if (str[0] == '\0')
	{
		return 0;
	}
	return 1+ RStrLength(str+1);
}

void ToBinary(int n)
{
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

string RToBinary(string output, int num)
{
	if (num == 0)
	{
		return output;
	}
	output = to_string(num % 2) + output;

	return RToBinary(output, num / 2);
}

void RToBinary2(int n)
{
	if (n <= 1)
	{
		cout << n;
	}
	else
	{
		RToBinary2(n / 2);
		cout << n % 2;
	}
}

int RFactorial(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return n* RFactorial(n - 1);
}

int Factorial(int n)
{
	int sum = 1;
	for (int i = 1; i <= n; i++)
	{
		sum *= i;
	}
	return sum;
}

int Search(int* Data, int size, int target)
{
	for (int i = 0; i < size; i++)
	{
		if (Data[i] == target)
		{
			return i;
		}
	}
	return -1;
}

int RSearch(int* Data, int size, int target)
{
	if (size == 0)
	{
		return -1;
	}
	if (*(Data+size-1) == target)
	{
		return size-1;
	}

	return RSearch(Data, size - 1, target);
}

int RSearch2(int* Data, int begin, int end, int target)
{
	if (begin > end)
	{
		return -1;
	}
	else if (Data[begin] == target)
	{
		return begin;
	}
	return RSearch2(Data, begin + 1, end, target);
}

int RSearch3(int* Data, int begin, int end, int target)
{
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
		int index = RSearch3(Data, begin, middle-1, target);
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


int RSearch4(int* Data, int begin, int end, int target)
{
	timecount += 1;
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
			return RSearch3(Data, begin, middle - 1, target);
		}
		else
		{
			return RSearch3(Data, middle + 1, end, target);
		}
	}
}

int timecount = 0;
int main()
{
	int Data[] = { 1,2,3,4,5,6,7,8,9,10 };
	cout << RSearch3(Data, 0, 10, 3) << endl;
	cout << timecount;
}