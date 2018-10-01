#pragma once
template<typename T>
class Node
{
public:
	T Data;
	Node<T>* Next;
	Node<T>* Prev;
};

template<typename T>
class List
{
public:
	List<T>();
	~List<T>();

	class Iterator //List의 반복자, ++, Next
	{
	public:
		Iterator() {}
		Iterator(Node<T>* init) { Current = init; } 
		//Iterator(Node* init = nullptr) { Current = init; } 

		Iterator& operator++() //A++
		{
			Current = Current->Next;
			return *this;
		}

		bool operator!=(const Iterator& rhs)
		{
			return (Current != rhs.Current);
		}

		T& operator*()
		{
			return Current->Data;
		}

		Node<T>* GetCurrent() { return Current; }

	protected:
		Node<T>* Current;
	};

	void PushBack(T Value);
	void PushFront(T Value);

	Iterator begin() { return Iterator(Head->Next); }
	Iterator end() { return Iterator(Tail); }



	Node<T>* RBegin()
	{
		return Head;
	}

	Node<T>* REnd()
	{
		return Tail->Prev;
	}

	Iterator Remove(Iterator DeleteNode)
	{
		if (DeleteNode.GetCurrent() == nullptr ||
			DeleteNode.GetCurrent() == Head ||
			DeleteNode.GetCurrent() == Tail)
		{
			return nullptr;
		}
		Node<T>* PrevNode = DeleteNode.GetCurrent()->Prev;

		DeleteNode.GetCurrent()->Prev->Next = DeleteNode.GetCurrent()->Next;
		DeleteNode.GetCurrent()->Next->Prev = DeleteNode.GetCurrent()->Prev;

		delete DeleteNode.GetCurrent();

		Size--;

		return Iterator(PrevNode);
	}

	void RemoveAll();

	void InsertBefore(Node<T>* Pointer, T Value);
	void InsertAfter(Node<T>* Pointer, T Value);

	Iterator Find(T Value)
	{
		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (*iter == Value)
			{
				return iter;
			}
		}
		
		//찾는게 없다.
		return nullptr;
	}
	Node<T>* RFind(T Value);

protected:
	Node<T>* Head;
	Node<T>* Tail;
	int Size;
};

template<typename T>
List<T>::List()
{
	Head = new Node<T>();
	Tail = new Node<T>();
	Head->Next = Tail;
	Tail->Prev = Head;
	Size = 0;
}

template<typename T>
List<T>::~List()
{
	RemoveAll();

	delete Head;
	delete Tail;
}

template<typename T>
void List<T>::PushBack(T Value)
{
	InsertBefore(Tail, Value);
}

template<typename T>
void List<T>::PushFront(T Value)
{
	InsertAfter(Head, Value);
}



template<typename T>
void List<T>::RemoveAll()
{
	for (auto Iter = begin(); Iter != end(); ++Iter)
	{
		Iter = Remove(Iter); //Remove 할때는 정방향 탐색만 가능
	}

	Size = 0;
}

template<typename T>
void List<T>::InsertBefore(Node<T>* Pointer, T Value)
{
	if (Pointer == nullptr ||
		Pointer == Head)
	{
		return;
	}
	Node<T>* NewNode = new Node<T>();
	NewNode->Data = Value;
	Node<T>* OldPrevNode = Pointer->Prev;
	Pointer->Prev = NewNode;
	NewNode->Prev = OldPrevNode;
	OldPrevNode->Next = NewNode;
	NewNode->Next = Pointer;

	Size++;
}

template<typename T>
void List<T>::InsertAfter(Node<T>* Pointer, T Value)
{
	if (Pointer == nullptr ||
		Pointer == Tail)
	{
		return;
	}
	Node<T>* NewNode = new Node<T>();
	NewNode->Data = Value;
	Node<T>* OldHeadNext = Pointer->Next;
	Pointer->Next = NewNode;
	NewNode->Next = OldHeadNext;
	OldHeadNext->Prev = NewNode;
	NewNode->Prev = Pointer;

	Size++;
}


template<typename T>
Node<T> * List<T>::RFind(T Value)
{
	//for (Node* Cursor = REnd(); Cursor != RBegin(); Cursor = Cursor->Prev)
	//{
	//	if (Cursor->Data == Value)
	//	{
	//		return Cursor;
	//	}
	//}

	return nullptr;
}