#include "MyVector.h"
#include <string.h>


MyVector::MyVector()
{
	Size = 0;
	Capacity = 10;

	Value = new int[Capacity];
	//일단생성
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
		int* Temp = new int[Capacity]; // new 연산이 느리기때문에 그냥 넉넉하게 곱하기해버렷다
		//for (int i = 0; i < Size; ++i)
		//{
		//	Temp[i] = Value[i];
		//}
		memcpy(Temp, Value, sizeof(int)*Size); // 메모리 통째로 복사
		Temp[Size] = NewValue;
		delete[] Value; //value 변수가 사라진게 아니라 가르키고있던 배열이 사라진것
		// new와 delete가 여기서는 대응되니까 넘어간다
		Value = Temp; //Temp와 Value가 같은곳을 가르킴
		Size++;
		//Value = new int[Size];
		//for (int i = 0; i < Size; ++i)
		//{
		//	Value[i] = Temp[i];
		//}
		//delete[] Temp;
		// 새로 temp를 만들어서 for문으로 넣는거랑
		// value = temp 해주는거랑 똑같
		// value가 temp 영역을 가르키게 함
		// delete[] value;  하고 넣어줘도 똑같
	}
	else // capacity 내에서
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
	//memcpy(Value, Temp, sizeof(int)*DeleteIndex); // 메모리 통째로 복사
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
