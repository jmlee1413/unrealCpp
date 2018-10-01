#pragma once
#include <string>

template <typename T>
class Queue
{
public:
	Queue(int InitCapacity=10)
	{
		//���� �����ڿ� �ʱ�ȭ�۾�
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
		//�������� ��� �޸�ī���ϸ� �δ㽺����
		//�ε����� �������

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
	//ť�� ��ٸ��� ����϶�� ����ǵ�
	//ť ����� �ʹ�������� ť�� �ǹ̰����� �����ѻ�����ʿ���


};

//string�ǰ�� return -1�Ҷ� ���������ܼ�
template <typename T>
T Queue<T>::Empty;
