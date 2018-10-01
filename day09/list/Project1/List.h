#pragma once
#include "ListT.h"

//추가삭제가 많은 자료
//하나 하나를 노드라고 함
class Node
{
public:
	int Data;
	Node* Next; //다음노드를 가르킴
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


	// 이터레이터 만들기
	class Iterator // List의 반복자, ++ , Next
	{
	public:
		Iterator() {}
		Iterator(Node* Init) { Current = Init; } //복사생성자

		~Iterator() {}

		Iterator& operator++() //자기자신을 리턴할떄는 래퍼런스로
		{
			Current = Current->Next;
			return *this; //포인터니까 값으로 바꿔주세요
		}
		bool operator!=(const Iterator& rhs) //인스턴스로 받으면 값이 바뀔수도있으니 const붙인다
		{
			return (Current != rhs.Current);
		}
		int& operator*() //데이터리턴
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

	//반대로 탐색하는 경우
	Node* rBegin() { return Head; }
	Node* rEnd() { return Tail->Prev; }

	Node* Remove(Node * deleteNode);
	void RemoveAll();

	Node* Find(int Value);
	Node* RFind(int Value);

	// 함수앞 바꾸지마라
	// 함수뒤 계산만하고 안바꿀꺼다
	// (const) 인자 안 안에서 안바꿀꺼다
private:
	Node* Head;
	Node* Tail;
	int Size;
};

