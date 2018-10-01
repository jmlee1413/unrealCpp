#pragma once
class Node
{
public:
	int Data;
	Node* Next;
	Node* Prev;

	//iterator ++ ±¸Çö
	//Node& operator++()
	//{
	//	return *Next;
	//}
};

class List
{
public:
	List();
	~List();

	//void Insert(int Value);
	void PushBack(int Value);
	void PushFront(int Value);

	Node* Begin()
	{
		return Head->Next;
	}

	Node* End()
	{
		return Tail;
	}

	Node* RBegin()
	{
		return Head;
	}

	Node* REnd()
	{
		return Tail->Prev;
	}

	Node* Remove(Node* DeleteNode);

	void RemoveAll();

	void InsertBefore(Node* Pointer, int Value);
	void InsertAfter(Node* Pointer, int Value);

	Node* Find(int Value);
	Node* RFind(int Value);

protected:
	Node* Head;
	Node* Tail;
	int Size;
};

