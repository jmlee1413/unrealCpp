#pragma once
#include "ListT.h"

//�߰������� ���� �ڷ�
//�ϳ� �ϳ��� ����� ��
class Node
{
public:
	int Data;
	Node* Next; //������带 ����Ŵ
	Node* Prev;

	//Node* operator ++()
	//{
	//	return Next;
	//}
};


class List
{
public:
	List();
	~List();


	// ���ͷ����� �����
	class Iterator // List�� �ݺ���, ++ , Next
	{
	public:
		Iterator() {}
		Iterator(Node* Init) { Current = Init; } //���������

		~Iterator() {}

		Iterator& operator++() //�ڱ��ڽ��� �����ҋ��� ���۷�����
		{
			Current = Current->Next;
			return *this; //�����ʹϱ� ������ �ٲ��ּ���
		}
		bool operator!=(const Iterator& rhs) //�ν��Ͻ��� ������ ���� �ٲ���������� const���δ�
		{
			return (Current != rhs.Current);
		}
		int& operator*() //�����͸���
		{
			return Current->Data;
		}

	protected:
		Node* Current;
	};


	Iterator begin() { return Iterator(Head->Next); }
	Iterator end() { return Iterator(Tail); }

	//void Insert(int Value);
	void PushBack(int Value);
	void PushFront(int Value);

	void InsertBack(Node* Pointer, int Value);
	void InsertFront(Node* Pointer, int Value);

	Node* Begin() { return Head->Next; }
	Node* End() { return Tail; }

	//�ݴ�� Ž���ϴ� ���
	Node* rBegin() { return Head; }
	Node* rEnd() { return Tail->Prev; }

	Node* Remove(Node * deleteNode);
	void RemoveAll();

	Node* Find(int Value);
	Node* RFind(int Value);

	// �Լ��� �ٲ�������
	// �Լ��� ��길�ϰ� �ȹٲܲ���
	// (const) ���� �� �ȿ��� �ȹٲܲ���
private:
	Node* Head;
	Node* Tail;
	int Size;
};

