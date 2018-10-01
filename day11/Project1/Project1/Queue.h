#pragma once
#include <string>

template <typename T>
class Queue
{
public:
	Queue(int InitCapacity=10)
	{
		//보통 생성자에 초기화작업
		Head = -1;
		Tail = -1;
		CurrentSize = 0;
		Capacity = InitCapacity;
		Data = new T[Capacity];
	}

	~Queue()
	{
		delete[] Data;
	}

	void EnQueue(T Value)
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
		//if (CurrentSize == 0)
		//{
		//	return 0;
		//}
		if (CurrentSize==0)
		{
			//full
			return Queue<T>::Empty;
		}


		//memcpy(&Data[0], &Data[1], sizeof(int)*(CurrentSize-1));
		//서버에서 계속 메모리카피하면 부담스럽다
		//인덱스로 계산해줌

		T Temp = Data[Head];
		Head++;
		Head = Head % Capacity;
		CurrentSize--;

		return Temp;
	}

	static T Empty;

protected:
	int Head;
	int Tail;
	T* Data;
	int CurrentSize;
	int Capacity = 3;
	//큐는 기다릴때 대기하라고 만든건데
	//큐 사이즈가 너무길어지면 큐의 의미가없다 적절한사이즈가필요함


};

//string의경우 return -1할때 에러가생겨서
template <typename T>
T Queue<T>::Empty;
