//트리 자식을가지는것
#include <iostream>
#include <list>
using namespace std;

class Node
{
public:
	Node(int Init = 0)
	{
		Data = Init;
	}

	Node* Parent;
	int Data;

	list<Node*> Chlid; //동적할려고

	Node* GetChild(int Index)
	{
		list<Node*>::iterator child = Chlid.begin();
		for (int i = 0; i < Index; ++i)
		{
			child++;
		}
		return *child;
	}
};

class Tree
{
public:
	Node* Root;
	void AddChild(Node* Where, int Value)
	{
		Node* NewNode = new Node(Value);
		Where->Chlid.push_back(NewNode);
		NewNode->Parent = Where;
	}

	int GetChildCoumt(Node* Where)
	{
		return Where->Chlid.size();
	}

	
};

int main()
{
	Node* Root = new Node(1);
	Tree* TestTree = new Tree();
	TestTree->Root = Root;

	Node* childNode = new Node(2);
	TestTree->AddChild(TestTree->Root, 2);
	TestTree->AddChild(Root->GetChild(0), 3);
	TestTree->AddChild(TestTree->Root, 4);
	TestTree->AddChild(Root->GetChild(1), 5);

	return 0;
}