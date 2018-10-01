#pragma once
template<typename T>
class Queue
{
public:
	Queue(int InitCapacity = 10)
	{
		Head = -1;
		Tail = -1;
		CurrentSize = 0;
		Capacity = InitCapacity;
		Data = new T[InitCapacity];
	}
	~Queue()
	{
		delete[] Data;
	}

	void Enqueue(T Value)
	{
		if (CurrentSize == Capacity)
		{
			return;
		}

		if (Head == -1)
		{
			Head = 0;
		}

		Tail++;
		Data[Tail%Capacity] = Value;


		CurrentSize++;
	}

	T Dequeue()
	{
		if (CurrentSize == 0)
		{
			return Queue<T>::Empty;
		}

		T Temp = Data[Head];
		Head++;
		Head = Head % Capacity;
		CurrentSize--;
		
		return Temp;
	}

	static T Empty;

protected:
	T *Data;
	int CurrentSize;
	int Head;
	int Tail;
	int Capacity;

};

template<typename T>
T Queue<T>::Empty;





