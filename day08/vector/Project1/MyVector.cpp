#include "MyVector.h"
#include <string.h>


MyVector::MyVector()
{
	Size = 0;
	Capacity = 10;

	Value = new int[Capacity];
	//�ϴܻ���
}


MyVector::~MyVector()
{
	delete[] Value;
}

void MyVector::PushBack( int NewValue )
{
	if (Capacity <= Size)
	{
		Capacity *= 2;
		int* Temp = new int[Capacity]; // new ������ �����⶧���� �׳� �˳��ϰ� ���ϱ��ع��Ǵ�
		//for (int i = 0; i < Size; ++i)
		//{
		//	Temp[i] = Value[i];
		//}
		memcpy(Temp, Value, sizeof(int)*Size); // �޸� ��°�� ����
		Temp[Size] = NewValue;
		delete[] Value; //value ������ ������� �ƴ϶� ����Ű���ִ� �迭�� �������
		// new�� delete�� ���⼭�� �����Ǵϱ� �Ѿ��
		Value = Temp; //Temp�� Value�� �������� ����Ŵ
		Size++;
		//Value = new int[Size];
		//for (int i = 0; i < Size; ++i)
		//{
		//	Value[i] = Temp[i];
		//}
		//delete[] Temp;
		// ���� temp�� ���� for������ �ִ°Ŷ�
		// value = temp ���ִ°Ŷ� �Ȱ�
		// value�� temp ������ ����Ű�� ��
		// delete[] value;  �ϰ� �־��൵ �Ȱ�
	}
	else // capacity ������
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

	//int* Temp = new int[DeleteIndex];
	//int* Temp2 = new int[Size - DeleteIndex];
	////for (int i = 0; i < DeleteIndex; ++i)
	////{
	////	Temp[i] = Value[i];
	////}
	//memcpy(Value, Temp, sizeof(int)*DeleteIndex); // �޸� ��°�� ����
	////*(Value) = *Temp;
	//*(Value + DeleteIndex) = *Temp2;
	if (DeleteIndex < 0 || DeleteIndex>Size)
	{
		return;
	}

	memcpy(&Value[DeleteIndex], &Value[DeleteIndex + 1], 
		sizeof(int)*(Size - DeleteIndex - 1));

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
