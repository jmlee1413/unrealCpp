#pragma once
class Stack
{
public:
	Stack(int StackSize = 10)
	{
		Data = new int[StackSize];
		Capacity = StackSize;
		Size = 0;
	}
	~Stack()
	{
		delete[] Data;
	}
	int GetSize() { return Size; }
	bool Push(int Value); //bool�� ������ á���� ��á���� �˻�
	int Pop();

	bool IsEmpty()
	{
		return (Size == 0);
	}

	bool IsFull()
	{
		return (Size == Capacity);
	}

	bool Resize(int NewSize);

protected:
	int* Data;
	int Capacity;
	int Size;
};

