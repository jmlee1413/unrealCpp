#pragma once
#include "List.h"

template<typename T>
class LQueue : public List<T>
{
public:
	LQueue()
	{

	}

	~LQueue()
	{

	}

	void Enqueue(T Value)
	{
		List<T>::PushBack(Value);
	}

	T Dequeue()
	{
		T Temp = *List<T>::begin();
		List<T>::Remove(List<T>::begin());
		return Temp;
	}
};

