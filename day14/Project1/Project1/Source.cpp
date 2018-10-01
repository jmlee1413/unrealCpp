#include <iostream>
using namespace std;
// map과 같은기능

class Node
{
public:
	Node(int Init = 0)
	{
		Data = Init; 
		Parent = nullptr;
		LeftChild = nullptr;
		RightChild = nullptr;
	}
	Node* Parent;
	int Data;
	Node* LeftChild;
	Node* RightChild;
};

class BSTree // binary search tree
{
public:
	BSTree() { Root = nullptr; }
	Node* GetRoot() { return Root; }
	void Insert(int Value)
	{
		Node* Current = Root;
		if (Root == nullptr)
		{
			Root = new Node(Value);
		}
		else
		{
			while (Current != nullptr)
			{
				if (Root->Data > Value)
				{
					if (Current->LeftChild == nullptr)
					{
						Node* NewNode = new Node(Value);
						Current->LeftChild = NewNode;
						NewNode->Parent = Current;
						Current = nullptr;
					}
					else
					{
						Current = Current->LeftChild;
					}
				}
				else
				{
					if (Current->RightChild == nullptr)
					{
						Node* NewNode = new Node(Value);
						Current->RightChild = NewNode;
						NewNode->Parent = Current;
						Current = nullptr;
					}
					else
					{
						Current = Current->RightChild;
					}
				}
			}
		}
	}

	Node* Find(int Value)
	{
		Node* Current = Root;
		while (Current != nullptr)
		{
			if (Current->Data == Value)
			{
				return Current;
			}
			else if (Value < Current->Data)
			{
				Current = Current->LeftChild;
			}
			else if (Value > Current->Data)
			{
				Current = Current->RightChild;
			}
		}
		return nullptr;
	}

	// 전위탐색
	// 언제 프린트하느냐의 차이
	void PreOrder(Node* SearchNode)
	{
		if (SearchNode != nullptr)
		{
			cout << SearchNode->Data << endl;
			if (SearchNode->LeftChild)
			{
				PreOrder(SearchNode->LeftChild);
			}
			if (SearchNode->RightChild)
			{
				PreOrder(SearchNode->RightChild);
			}
		}
	}

	void InOrder(Node* SearchNode) //중위탐색
	{
		if (SearchNode != nullptr)
		{
			if (SearchNode->LeftChild)
			{
				PreOrder(SearchNode->LeftChild);
			}
			cout << SearchNode->Data << endl;
			if (SearchNode->RightChild)
			{
				PreOrder(SearchNode->RightChild);
			}
		}
	}

	void PostOrder(Node* SearchNode) //후위탐색
	{
		if (SearchNode != nullptr)
		{
			if (SearchNode->LeftChild)
			{
				PreOrder(SearchNode->LeftChild);
			}
			if (SearchNode->RightChild)
			{
				PreOrder(SearchNode->RightChild);
			}
			cout << SearchNode->Data << endl;
		}
	}
protected:
	Node* Root;
};



int main()
{
	BSTree b;
	b.Insert(10);
	b.Insert(2);
	b.Insert(1);
	b.Insert(9);

	return 0;
}