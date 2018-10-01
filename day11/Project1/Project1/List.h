#pragma once
#include "List.h"

template <typename T>
class NodeT
{
public:
	T Data;
	NodeT<T>* Next;
	NodeT<T>* Prev;

};

template <typename T>
class ListT
{
public:
	ListT();
	virtual ~ListT(); //virtual 붙여야 자식것도 호출된다

	class Iterator
	{
	public:
		Iterator() {}
		Iterator(NodeT<T>* Init) { Current = Init; }
		~Iterator() {}

		NodeT<T>* GetCurrent() { return Current; }
		Iterator& operator++()
		{
			Current = Current->Next;
			return *this;
		}
		bool operator!=(const Iterator& rhs)
		{
			return (Current != rhs.Current);
		}
		T& operator*() //데이터리턴
		{
			return Current->Data;
		}

	protected:
		NodeT<T>* Current;
	};

	class ReverseIterator
	{
	public:
		ReverseIterator() {}
		ReverseIterator(NodeT<T>* Init) { Current = Init; }
		~ReverseIterator() {}

		NodeT<T>* GetCurrent() { return Current; }
		ReverseIterator& operator++()
		{
			Current = Current->Prev;
			return *this;
		}
		bool operator!=(const ReverseIterator& rhs)
		{
			return (Current != rhs.Current);
		}
		T& operator*() //데이터리턴
		{
			return Current->Data;
		}

	protected:
		NodeT<T>* Current;
	};

	int GetSize() { return Size; }

	void PushBack(T Value)
	{
		InsertFront(Tail, Value);
	}
	void PushFront(T Value)
	{
		InsertBack(Head, Value);
	}

	void InsertBack(NodeT<T>* Pointer, T Value)
	{
		if (Pointer == nullptr ||
			Pointer == Tail)
		{
			return;
		}

		NodeT<T>* NewNode = new NodeT<T>();
		NewNode->Data = Value;

		NodeT<T>* OldNode = Pointer->Next;
		Pointer->Next = NewNode;
		NewNode->Next = OldNode;

		OldNode->Prev = NewNode;
		NewNode->Prev = Pointer;
		Size++;
	}

	void InsertFront(NodeT<T>* Pointer, T Value)
	{
		if (Pointer == nullptr ||
			Pointer == Head)
		{
			return;
		}

		NodeT<T>* NewNode = new NodeT<T>();
		NewNode->Data = Value;

		NodeT<T>* OldPrevNode = Pointer->Prev;
		Pointer->Prev = NewNode;
		NewNode->Prev = OldPrevNode;

		OldPrevNode->Next = NewNode;
		NewNode->Next = Pointer;
		Size++;
	}

	Iterator Begin() { return Iterator(Head->Next); }
	Iterator End() { return Iterator(Tail); }

	Iterator rBegin() { return Iterator(Tail->Prev); }
	Iterator rEnd() { return Iterator(Head); }

	ReverseIterator rbegin() { return ReverseIterator(Tail->Prev); }
	ReverseIterator rend() { return ReverseIterator(Head); }

	Iterator Remove(Iterator deleteNode)
	{
		if (deleteNode.GetCurrent() == nullptr ||
			deleteNode.GetCurrent() == Head ||
			deleteNode.GetCurrent() == Tail)
		{
			return nullptr;
		}
		NodeT<T>* PrevNode = deleteNode.GetCurrent()->Prev;

		deleteNode.GetCurrent()->Prev->Next = deleteNode.GetCurrent()->Next;
		deleteNode.GetCurrent()->Next->Prev = deleteNode.GetCurrent()->Prev;

		delete deleteNode.GetCurrent();
		Size--;

		return Iterator(PrevNode);
	}

	void RemoveAll()
	{
		for (auto iter = Begin(); iter != End(); ++iter)
		{
			iter = Remove(iter);
		}
		Size = 0;
	}

	Iterator Find(T Value)
	{
		for (Iterator iter = Begin(); iter != End(); ++iter)
		{
			if (*iter == Value)
			{
				return iter;
			}
		}
		return nullptr;
	}

	Iterator RFind(T Value)
	{
		for (auto iter = rbegin(); iter != rend(); --iter)
		{
			if (*iter == Value)
			{
				return iter;
			}
		}
		return nullptr;
	}

private:
	NodeT<T>* Head;
	NodeT<T>* Tail;
	int Size;
};

template<typename T>
ListT<T>::ListT()
{
	Head = new NodeT<T>();
	Tail = new NodeT<T>();
	Head->Next = Tail;
	Tail->Prev = Head;
	Size = 0;
}

template<typename T>
inline ListT<T>::~ListT()
{
	RemoveAll();
	delete Head;
	delete Tail;
}
