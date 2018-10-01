#include "Stack.h"
#include <string>
using namespace std;


bool Stack::Resize(int NewSize)
{
	if (NewSize != Capacity && NewSize > 0)
	{
		int* Temp = new int[NewSize];
		if (Temp == nullptr)
		{
			return false;
		}//temp ���������� �޸𸮰����ڶ����

		/*if (NewSize > Size)
		{
			memcpy(Temp, Data, sizeof(int)*Size);
		}
		else if (NewSize < Size)
		{
			memcpy(Temp, Data, sizeof(int)*NewSize);
			Size = NewSize;
		}*/
		Size = Size > NewSize ? NewSize : Size; // true �� �տ��� false�� �ڿ���
		memcpy(Temp, Data, sizeof(int)*Size);

		Capacity = NewSize;
		delete[] Data;
		Data = Temp;
	}
	return true;
}

bool Stack::Push(int Value)
{
	if (Size == Capacity)
	{
		return false;
	}

	Data[Size] = Value;
	Size++;

	return false;
}

int Stack::Pop()
{
	if (--Size < 0)
	{
		return -1;
	}

	return Data[Size];
}