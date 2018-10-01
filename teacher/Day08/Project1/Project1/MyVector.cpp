#include "MyVector.h"
#include <memory.h>
#include <iostream>


MyVector::MyVector()
{
	Capacity = 10;
	Size = 0;

	Value = new int[Capacity];
}


MyVector::~MyVector()
{
	delete[] Value;
}

void MyVector::PushBack(int NewValue)
{
	if (Capacity <= Size) //����������� ���ڶ�ϱ� �뷮 �߰�, ���� ����, ����, �̵�
	{
		Capacity = Capacity * 2;
		int* Temp = new int[Capacity];
		memcpy(Temp, Value, sizeof(int)*Size);
		Temp[Size] = NewValue;
		delete[] Value;
		Value = Temp; //Temp�� Value�� ���� ���� ����Ŵ
		Size++;
		//std::cout << "Allocate" << std::endl;
	}
	else //���� �ڷ� ��ġ�ڿ� �߰���
	{
		Value[Size] = NewValue;
		Size++;
	}

}

int MyVector::GetValue(int GetIndex)
{
	if (Size > GetIndex)
	{
		return Value[GetIndex];
	}
	
	return -1;
}

int MyVector::GetSize()
{
	return Size;
}

void MyVector::Erase(int DeleteIndex)
{
	if (DeleteIndex < 0 || DeleteIndex > Size)
	{
		return;
	}
	//for (int i = DeleteIndex; i < Size-1; ++i)
	//{
	//	Value[i] = Value[i + 1];
	//}
	memcpy(&Value[DeleteIndex], &Value[DeleteIndex + 1],
		sizeof(int) * (Size - DeleteIndex - 1));

	Size--;
}

int MyVector::Find(int SearchValue)
{
	for (int i = 0; i < Size; ++i)
	{
		if (Value[i] == SearchValue)
		{
			return i;
		}
	}
	return -1;
}
