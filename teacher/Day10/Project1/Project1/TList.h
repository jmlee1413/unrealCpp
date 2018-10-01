#pragma once
template<typename T>
class TNode
{
public:
	T Data;
	TNode<T>* Next;
	TNode<T>* Prev;

	//int& operator* ()
	//{
	//	return this;
	//}
};

template<typename T>
class TList
{
public:
	TList();
	~TList();

	class Iterator
	{
		TNode<T>* current;
	public:
		Iterator(TNode<T>* init = nullptr) : current(init) {}

		Iterator& operator++()
		{
			current = current->Next;
			return *this;
		}

		T& operator* ()
		{
			return current->Data;
		}

		bool operator !=(const Iterator& i)
		{
			return (current != i.current);
		}
	};

	void PushBack(T Value);
	void PushFront(T Value);

	Iterator begin() { return Iterator(Head->Next); }

	Iterator end() { return Iterator(Tail); }

	TNode<T>* Begin()
	{
		return Head->Next;
	}

	TNode<T>* End()
	{
		return Tail;
	}

	TNode<T>* RBegin()
	{
		return Head;
	}

	TNode<T>* REnd()
	{
		return Tail->Prev;
	}

	TNode<T>* Remove(TNode<T>* DeleteNode);

	void RemoveAll();

	void InsertBefore(TNode<T>* Pointer, T Value);
	void InsertAfter(TNode<T>* Pointer, T Value);

	TNode<T>* Find(T Value);
	TNode<T>* RFind(T Value);

protected:
	TNode<T>* Head;
	TNode<T>* Tail;
	int Size;
};

template<typename T>
TList<T>::TList()
{
	Head = new TNode<T>();
	Tail = new TNode<T>();
	Head->Next = Tail;
	Tail->Prev = Head;
	Size = 0;
}
template<typename T>
TList<T>::~TList()
{
	RemoveAll();

	delete Head;
	delete Tail;
}
template<typename T>
void TList<T>::PushBack(T Value)
{
	InsertBefore(Tail, Value);
}

template<typename T>
void TList<T>::PushFront(T Value)
{
	InsertAfter(Head, Value);
}

template<typename T>
TNode<T>* TList<T>::Remove(TNode<T>* DeleteNode)
{
	if (DeleteNode == Head ||
		DeleteNode == Tail ||
		DeleteNode == nullptr)
	{
		return nullptr;
	}
	TNode<T>* NextNode = DeleteNode->Prev;

	DeleteNode->Prev->Next = DeleteNode->Next;
	DeleteNode->Next->Prev = DeleteNode->Prev;

	delete DeleteNode;

	Size--;

	return NextNode;
}

template<typename T>
void TList<T>::RemoveAll()
{
	TNode<T>* FindNode = Head;
	for (TNode<T>* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		Cursor = Remove(Cursor); //Remove 할때는 정방향 탐색만 가능
	}

	Size = 0;
}

template<typename T>
void TList<T>::InsertBefore(TNode<T>* Pointer, T Value)
{
	if (Pointer == nullptr ||
		Pointer == Head)
	{
		return;
	}
	TNode<T>* NewNode = new TNode<T>();
	NewNode->Data = Value;
	TNode<T>* OldPrevNode = Pointer->Prev;
	Pointer->Prev = NewNode;
	NewNode->Prev = OldPrevNode;
	OldPrevNode->Next = NewNode;
	NewNode->Next = Pointer;

	Size++;
}

template<typename T>
void TList<T>::InsertAfter(TNode<T>* Pointer, T Value)
{
	if (Pointer == nullptr ||
		Pointer == Tail)
	{
		return;
	}
	TNode<T>* NewNode = new TNode<T>();
	NewNode->Data = Value;
	TNode<T>* OldHeadNext = Pointer->Next;
	Pointer->Next = NewNode;
	NewNode->Next = OldHeadNext;
	OldHeadNext->Prev = NewNode;
	NewNode->Prev = Pointer;

	Size++;
}

template<typename T>
TNode<T> * TList<T>::Find(T Value)
{
	TNode<T>* FindNode = Head;
	for (TNode<T>* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}

	//찾는게 없다.
	return nullptr;
}

template<typename T>
TNode<T> * TList<T>::RFind(T Value)
{
	for (TNode<T>* Cursor = REnd(); Cursor != RBegin(); Cursor = Cursor->Prev)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}

	return nullptr;
}
