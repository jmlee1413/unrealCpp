#include "List.h"



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



//void List::Insert(int Value)
//{
//	if (Head == nullptr)
//	{ 
//		//�ڷᰡ ������
//		Head = new Node();
//		Head->Data = Value;
//		Head->Next = nullptr;
//		Size++;
//	}
//	else
//	{
//		if (Head->Next == nullptr)
//		{
//			//�ڷᰡ �ϳ� ������
//			Node* NewNode = new Node();
//			NewNode->Data = Value;
//			NewNode->Next = nullptr;
//			Head->Next = NewNode;
//			Size++;
//		}
//		else
//		{
//			Node* NewNode = new Node();
//			NewNode->Data = Value;
//			NewNode->Next = nullptr;
//
//			Node* InsertPoint = Head;
//			while (InsertPoint->Next)
//			{
//				InsertPoint = InsertPoint->Next;
//			}
//
//			InsertPoint->Next = NewNode;
//			Size++;
//		}
//	}
//
//}

void List::PushBack(int Value)
{
	//1. �߰� �� ��� ����
	//Node* NewNode = new Node();
	//NewNode->Data = Value;

	////2.Tail�� �� ��� ���
	//Node* OldPrevNode = Tail->Prev;

	////3. Tail�� �ճ�带 �߰� �� ��� ����
	//Tail->Prev = NewNode;

	////4. �߰��� ����� �ճ�带 ����Tail �ճ��� ����(NewNode = Tail->Prev);
	//NewNode->Prev = OldPrevNode;

	////5. ���� Tail�� �ճ���� ������ New���� ����
	//OldPrevNode->Next = NewNode;

	////6. ���� �߰��� ����� ���� ��忬��(Tail)
	//NewNode->Next = Tail;

	//Size++;

	InsertBefore(Tail, Value);
}

void List::PushFront(int Value)
{
	//Node* NewNode = new Node();
	//NewNode->Data = Value;
	//Node* OldHeadNext = Head->Next;
	//Head->Next = NewNode;
	//NewNode->Next = OldHeadNext;
	//OldHeadNext->Prev = NewNode;
	//NewNode->Prev = Head;

	//Size++;
	InsertAfter(Head, Value);
}

Node* List::Remove(Node* DeleteNode)
{
	if (DeleteNode == Head ||
		DeleteNode == Tail ||
		DeleteNode == nullptr)
	{
		return nullptr;
	}
	Node* NextNode = DeleteNode->Prev;

	DeleteNode->Prev->Next = DeleteNode->Next;
	DeleteNode->Next->Prev = DeleteNode->Prev;

	delete DeleteNode;

	Size--;

	return NextNode;
}

void List::RemoveAll()
{
	Node* FindNode = Head;
	for (Node* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		Cursor = Remove(Cursor); //Remove �Ҷ��� ������ Ž���� ����
	}

	Size = 0;
}

void List::InsertBefore(Node* Pointer, int Value)
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

void List::InsertAfter(Node* Pointer,int Value)
{
	if (Pointer == nullptr ||
		Pointer == Tail)
	{
		return;
	}
	Node* NewNode = new Node();
	NewNode->Data = Value;
	Node* OldHeadNext = Pointer->Next;
	Pointer->Next = NewNode;
	NewNode->Next = OldHeadNext;
	OldHeadNext->Prev = NewNode;
	NewNode->Prev = Pointer;

	Size++;
}

Node * List::Find(int Value)
{
	Node* FindNode = Head;
	for (Node* Cursor = Begin(); Cursor != End(); Cursor = Cursor->Next)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}

	//ã�°� ����.
	return nullptr;
}

Node * List::RFind(int Value)
{
	for (Node* Cursor = REnd(); Cursor != RBegin(); Cursor = Cursor->Prev)
	{
		if (Cursor->Data == Value)
		{
			return Cursor;
		}
	}

	return nullptr;
}