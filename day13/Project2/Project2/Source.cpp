#include <iostream> // <utility> 포함한다
#include <stdlib.h>

using namespace std;

void BubbleSort(int* data, int size)
{
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = 0; j < size-1; ++j) //비교 기준 j 비교대상 j+1
		{
			if (data[j] > data[j+1])
			{
				swap(data[j], data[j+1]);
			}

		}
	}
}

//함수를인자로 넘긴다
void SelectionSort(int* data, int size, bool (*fp)(int,int))
{
	for (int i = 0; i < size - 1; ++i) //기준 i
	{
		for (int j = i+1; j < size; ++j) //비교대상 i+1
		{
			if (fp(data[i], data[j]))
			{
				swap(data[i], data[j]);
			}

		}
	}
}

void test(int a, int b)
{
	cout << a+ b << endl;
}

bool cmp(int a, int b)
{
	return a < b;
}

int partition(int* data, int begin, int end)
{

	cout << endl;
	int pivot = data[end]; // 임의로 피봇을 마지막으로 잡은것
	int min = begin - 1;
	for (int max = begin; max <= end - 1; ++max)
	{
		if (data[max] <= pivot)
		{
			min++;
			swap(data[min], data[max]);
		}
	}
	swap(data[min + 1], data[end]);
	return min+1;
}

void QuickSort(int* data, int begin, int end)
{

	if (begin < end)
	{
		//자료나누기 정렬 partition에서 다함
		int pivot = partition(data, begin, end);
		QuickSort(data, begin, pivot - 1);
		QuickSort(data, pivot + 1, end);
	}

}

int main()
{
	//bubble 붙어잇는애들 좌우 두개씩 비교
	//selection 처음꺼 옆에꺼 처음꺼 옆에옆에꺼 처음꺼 옆옆옆에꺼 비교
	int data[] = { 2,4,5,3,1 };
	//BubbleSort(data, 5);
	//SelectionSort(data, 5, cmp);
	//어떤함수를 넘기느냐에따라 정방향 역방향 정렬가능하다


	//함수포인터
	//딜리게이트라고도한다
	//함수를 인자로 넘길수있다
	//void(*fp)(int, int); //보이드형태 받는함수이름모름 인트인트
	//fp = test;
	//test(1, 2);
	//fp(1, 2);

	//sort(data, data + 5, greater<int>());

	QuickSort(data, 0, 4);
	for (auto i : data)
	{
		cout << i << " ";
	}

	return 0;
}