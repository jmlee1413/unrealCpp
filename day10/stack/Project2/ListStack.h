#pragma once
#include "ListT.h"

// �յڳ�尡�ִ� ����
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

	bool IsEmpty(); // �׋��׋� �ø��Ŷ� full�� �ǹ̰�����
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
	Data.Remove(Data.rbegin()); //list����� ���ľ��ϴµ� ����̾����� ������Ѵ�
	return Temp;
}

template<typename T>
inline bool ListStack<T>::IsEmpty()
{
	return (Data.GetSize() == 0);
}
