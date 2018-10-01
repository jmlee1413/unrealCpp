#pragma once

template <typename T>
class Vector
{
public:
	Vector();
	~Vector();

	class Iterator
	{
	public:
		Iterator(Vector<T>* Init, int index=0) 
		{
			Current = Init; 
			CurrentIndex = index;
		};

		Iterator& operator++ ()
		{
			CurrentIndex++;
			return *this;
		}
		bool operator!=(const Iterator& rhs)
		{
			return (Current != rhs.Current);
		}
		T& operator*()
		{
			return (Current->GetValue(CurrentIndex));
		}

	protected:
		Vector<T>* Current;
		int CurrentIndex;
	};

	void PushBack(T Value);
	void Remove(int index);
	int Find(T Value);

	int GetSize() { return Size; };
	T& GetValue(int index) { return Data[index]; }

	Iterator begin() 
	{
		return Iterator(this, 0); 
	};
	Iterator end() 
	{ 
		return Iterator(this, GetSize()); 
	};


protected:
	T* Data;
	int Size;
	int Capacity;
};

