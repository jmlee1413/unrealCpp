#pragma once
#include "ListT.h"

// 앞뒤노드가있는 스택
template<typename T>
class ListStack
{
public:
	ListStack()
	{

	}
	~ListStack()
	{

	}

	void Push(T Value);
	int Pop();

	bool IsEmpty(); // 그떄그떄 늘릴거라 full은 의미가없다
	int GetSize() { return Data.GetSize(); }
protected:
	ListT<T> Data;

};

template<typename T>
void ListStack<T>::Push(T Value)
{
	Data.PushBack(Value);
}

template<typename T>
int ListStack<T>::Pop()
{
	T Temp = *(Data.rbegin());
	Data.Remove(Data.rbegin()); //list기능을 고쳐야하는데 방법이없으니 상속을한다
	return Temp;
}

template<typename T>
inline bool ListStack<T>::IsEmpty()
{
	return (Data.GetSize() == 0);
}
