#pragma once
template<typename T>
class MyVectorT
{
public:
	MyVectorT();
	~MyVectorT();

	void PushBack(T NewValue);
	T& GetValue(int GetIndex);
	int GetSize();
	void Erase(int DeleteIndex);
	int Find(T SearchValue);

	static T Empty;

	T& operator[] (int Index)
	{
		return GetValue(Index);
	}

	class Iterator
	{
	private:
		MyVectorT<T>* Current;
		int CurrentIndex;
	public:
		Iterator(MyVectorT<T>* init = nullptr, int initIndex = 0)
		{
			Current = init;
			CurrentIndex = initIndex;
		}

		Iterator& operator++()
		{
			CurrentIndex++;
			return *this;
		}

		T& operator*()
		{
			return Current->GetValue(CurrentIndex);
		}

		bool operator!= (const Iterator& rhs)
		{
			return (CurrentIndex != rhs.CurrentIndex);
		}

	};

	Iterator begin()
	{
		return  Iterator(this, 0);
	}

	Iterator end()
	{
		return Iterator(this, GetSize());
	}

protected:
	int Size;
	T* Value;

	int Capacity;
};

template<typename T>
inline MyVectorT<T>::MyVectorT()
{
	Capacity = 10;
	Size = 0;

	Value = new T[Capacity];
}

template<typename T>
inline MyVectorT<T>::~MyVectorT()
{
	delete[] Value;
}

template<typename T>
void MyVectorT<T>::PushBack(T NewValue)
{
	if (Capacity <= Size) //저장공간보다 모자라니깐 용량 추가, 새로 생성, 복사, 이동
	{
		Capacity = Capacity * 2;
		T* Temp = new T[Capacity];
		for (int i = 0; i < Size; ++i)
		{
			Temp[i] = Value[i];
		}
		//memcpy(Temp, Value, sizeof(T)*Size);
		Temp[Size] = NewValue;
		delete[] Value;
		Value = Temp; //Temp와 Value가 같은 곳을 가르킴
		Size++;
		//std::cout << "Allocate" << std::endl;
	}
	else //현재 자료 위치뒤에 추가만
	{
		Value[Size] = NewValue;
		Size++;
	}
}

template<typename T>
inline T& MyVectorT<T>::GetValue(int GetIndex)
{
	if (Size > GetIndex)
	{
		return Value[GetIndex];
	}

	return Empty;
}

template<typename T>
inline int MyVectorT<T>::GetSize()
{
	return Size;
}

template<typename T>
inline void MyVectorT<T>::Erase(int DeleteIndex)
{
	if (DeleteIndex < 0 || DeleteIndex > Size)
	{
		return;
	}
	for (int i = DeleteIndex; i < Size-1; ++i)
	{
		Value[i] = Value[i + 1];
	}
	//memcpy(&Value[DeleteIndex], &Value[DeleteIndex + 1],
	//	sizeof(T) * (Size - DeleteIndex - 1));

	Size--;
}

template<typename T>
inline int MyVectorT<T>::Find(T SearchValue)
{
	for (int i = 0; i < Size; ++i)
	{
		if (Value[i] == SearchValue)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
T MyVectorT<T>::Empty;