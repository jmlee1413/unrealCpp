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
	bool Push(int Value); //bool로 스택이 찼는지 안찼는지 검사
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

