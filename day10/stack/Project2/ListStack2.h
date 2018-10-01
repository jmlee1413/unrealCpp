#pragma once
#include "ListT.h"

//������ ����Ʈ�� ����ؼ� �����Ѵ�
template <typename T>
class ListStack2 : public ListT<T> //����� �� ����غ��ÿ�
{
public:
	ListStack2(){}
	~ListStack2(){}

	void Push(T Value)
	{
		ListT<T>::PushBack(Value);
	}

	T Pop()
	{
		T Temp = ListT<T>::Tail->Prev->Data;
		RemoveNode(ListT<T>::Tail->Prev);
		return Temp;
	}

	bool IsEmpty() { return (ListT<T>::Size == 0); }

protected:
	void RemoveNode(NodeT<T>* deleteNode) //Stack ��
	{
		if (deleteNode == ListT<T>::Head)
		{
			return;
		}

		deleteNode->Prev->Next = deleteNode->Next;
		deleteNode->Next->Prev = deleteNode->Prev;

		delete deleteNode;
		ListT<T>::Size--;
	}
};

