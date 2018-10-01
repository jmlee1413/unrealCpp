#include "List.h"
#include <iostream>

List::List()
{
	Head = new Node();
	Tail = new Node();
	Head->Next = Tail;
	Tail->Prev = Head;
	Size = 0;
}


List::~List()
{
	RemoveAll();
	delete Head;
	delete Tail;
}

//
//void List::Insert(int Value)
//{
//	if (Head->Next == Tail)
//	{
//		Node* NewNode = new Node();
//		NewNode->Data = Value;
//		Head->Next = NewNode;
//		NewNode->Next = Tail;
//		Size++;
//	}
//	else
//	{
//		Node* NewNode = new Node();
//		NewNode->Data = Value;
//		NewNode->Next = Tail;
//		
//		Node* current = GetHead();
//		while(current->Next && current->Next != Tail)
//		{
//			current = current->Next;
//		}
//		current->Next = NewNode;
//		Size++;
//	}
//}

void List::PushBack(int Value)
{
	//Node* NewNode = new Node();
	//NewNode->Data = Value;
	//
	//Node* OldPrevNode = Tail->Prev;
	//Tail->Prev = NewNode;
	//NewNode->Prev = OldPrevNode;

	//OldPrevNode->Next = NewNode;
	//NewNode->Next = Tail;
	//Size++;
	InsertFront(Tail, Value);
}

void List::PushFront(int Value)
{
	/*Node* NewNode = new Node();
	NewNode->Data = Value;

	Node* OldNode = Head->Next;
	Head->Next = NewNode;
	NewNode->Next = OldNode;

	OldNode->Prev = NewNode;
	NewNode->Prev = Head;
	Size++;*/
	InsertBack(Head, Value);
}

void List::InsertBack(Node * Pointer, int Value)
{
	if (Pointer == nullptr ||
		Pointer == Tail)
	{
		return;
	}

	Node* NewNode = new Node();
	NewNode->Data = Value;

	Node* OldNode = Pointer->Next;
	Pointer->Next = NewNode;
	NewNode->Next = OldNode;

	OldNode->Prev = NewNode;
	NewNode->Prev = Pointer;
	Size++;
}

void List::InsertFront(Node * Pointer, int Value)
{
	if (Pointer == nullptr ||
		Pointer == Head)
	{
		return;
	}

	Node* NewNode = new Node();
	NewNode->Data = Value;

	Node* OldPrevNode = Pointer->Prev;
	Pointer->Prev = NewNode;
	NewNode->Prev = OldPrevNode;

	OldPrevNode->Next = NewNode;
	NewNode->Next = Pointer;
	Size++;
}

//void List::Remove(int Index)
//{
//	if (Index == 0)
//	{
//		Node* current = Head->Next;
//		current = current->Next;
//		Size--;
//	}
//	else
//	{
//		if (Index < Size)
//		{
//			Node* current = Head->Next;
//			for (int i = 0; i < Index-1; ++i)
//			{
//				current = current->Next;
//			}
//			current->Next = current->Next->Next;
//			Size--;
//		}
//	}
//}

Node* List::Remove(Node* deleteNode)
{
	if (deleteNode == Head ||
		deleteNode == Tail ||
		deleteNode == nullptr)
	{
		return nullptr;
	}

	//그냥지워버리면 연결정보가 날라간다
	//지우기전에 다음노드를 저장하고 지우고나서 리턴
	Node* NextNode = deleteNode->Next;

	deleteNode->Prev->Next = deleteNode->Next;
	deleteNode->Next->Prev = deleteNode->Prev;

	delete deleteNode;
	Size--;

	return NextNode;
}

void List::RemoveAll()
{
	for (Node* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		Cursor = Remove(Cursor);
	}
	Size = 0;
}

Node* List::Find(int Value)
{
	//Node* current = Head->Next;
	//int index = 0;
	//while (current)
	//{
	//	if (current->Data == Value)
	//	{
	//		
	//		return index;
	//	}
	//	else
	//	{
	//		current = current->Next;
	//		index++;
	//	}
	//}
	//return -1;
	for (Node* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}

}

Node* List::RFind(int Value)
{
	//Node* current = GetTail();
	//Node* prev = GetHead()->Next;
	//int index = -1;

	//for(int i=0; i<Size-1; ++i)
	//{
	//	if (current->Data == Value)
	//	{
	//		return index;
	//	}
	//	else
	//	{
	//		while ((prev->Next != current) && (prev->Next != Tail))
	//		{
	//			prev = prev->Next;
	//		}
	//		current = prev;
	//		index++;
	//	}
	//}

	for (Node* Cursor = rEnd(); Cursor != rBegin(); Cursor = Cursor->Prev)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}
}
