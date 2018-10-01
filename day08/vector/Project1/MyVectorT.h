#pragma once
template <typename T>
class MyVectorT
{
public:
	MyVectorT()
	{
		Size = 0;
		Capacity = 10;

		Value = new T[Capacity];
	}
	~MyVectorT()
	{
		delete[] Value;
	}

	void PushBack(T NewValue);
	T& GetValue(int GetIndex);
	int GetSize();
	void Erase(int DeleteIndex);
	int Find(T SearchValue);

	T operator[] (int Index) // 함수 오버라이드하기
	{
		return GetValue(Index);
	}

	bool operator == (const MyVectorT<T>& Right)
	{
		for (int i = 0; i < GetSize(); ++i)
		{
			if (GetValue[i] != Right.GetValue(i))
			{
				return false;
			}
		}
	}

	static T Empty;

protected:
	int Size;
	T* Value;
	int Capacity;

};

template<typename T>
void MyVectorT<T>::PushBack(T NewValue) // 함수 기니까 inline 지운다
{
	if (Capacity <= Size)
	{
		Capacity *= 2;
		T* Temp = new T[Capacity]; 
		memcpy(Temp, Value, sizeof(T)*Size); 
		Temp[Size] = NewValue;
		delete[] Value;
		Value = Temp;
		Size++;
		
	}
	else 
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

	return Empty; //문자열일떄를 대비해서
}

template<typename T>
inline int MyVectorT<T>::GetSize()
{
	return Size;
}

template<typename T>
void MyVectorT<T>::Erase(int DeleteIndex)
{
	if (DeleteIndex < 0 || DeleteIndex>Size)
	{
		return;
	}

	memcpy(&Value[DeleteIndex], &Value[DeleteIndex + 1],
		sizeof(T)*(Size - DeleteIndex - 1));

	Size--;
}

template<typename T>
int MyVectorT<T>::Find(T SearchValue)
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