#include "Vector.h"
#include "string"

template <typename T>
Vector<T>::Vector()
{
	Capacity = 10;
	Data = new T[Capacity];
	Size = 0;
}

template <typename T>
Vector<T>::~Vector()
{
}

template <typename T>
void Vector<T>::PushBack(T Value)
{
	if (Size < Capacity)
	{
		Data[Size] = Value;
		Size++;
	}
	else
	{
		T* Temp = new T[Capacity * 2];
		memcpy(Temp, Data, sizeof(T)*Size);
		Data[Size] = Value;
		Data = Temp;
		Size++;
	}
}

template <typename T>
void Vector<T>::Remove(int index)
{
	if (index >= Size)
	{
		return;
	}
	memcpy(&Data[index], &Data[index + 1], sizeof(T)*(Size-index-1));
	Size--;
}

template <typename T>
int Vector<T>::Find(T Value)
{
	return 0;
}
