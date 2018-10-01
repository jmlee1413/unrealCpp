#pragma once
#include "List.h"

template <typename T>
class ListQueue : public ListT<T>
{
public:
	ListQueue()
	{

	}
	~ListQueue()
	{

	}

	void EnQueue(T Value)
	{
		ListT<T>::PushBack(Value);
	}
	T DeQueue()
	{
		NodeT<T> Temp = ListT<T>::Head;
		ListT<T>::Remove(ListT<T>::Head->Next);
		return *Temp;
	}

};

