#include <iostream> // <utility> �����Ѵ�
#include <stdlib.h>

using namespace std;

void BubbleSort(int* data, int size)
{
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = 0; j < size-1; ++j) //�� ���� j �񱳴�� j+1
		{
			if (data[j] > data[j+1])
			{
				swap(data[j], data[j+1]);
			}

		}
	}
}

//�Լ������ڷ� �ѱ��
void SelectionSort(int* data, int size, bool (*fp)(int,int))
{
	for (int i = 0; i < size - 1; ++i) //���� i
	{
		for (int j = i+1; j < size; ++j) //�񱳴�� i+1
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
	int pivot = data[end]; // ���Ƿ� �Ǻ��� ���������� ������
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
		//�ڷᳪ���� ���� partition���� ����
		int pivot = partition(data, begin, end);
		QuickSort(data, begin, pivot - 1);
		QuickSort(data, pivot + 1, end);
	}

}

int main()
{
	//bubble �پ��մ¾ֵ� �¿� �ΰ��� ��
	//selection ó���� ������ ó���� ���������� ó���� ���������� ��
	int data[] = { 2,4,5,3,1 };
	//BubbleSort(data, 5);
	//SelectionSort(data, 5, cmp);
	//��Լ��� �ѱ���Ŀ����� ������ ������ ���İ����ϴ�


	//�Լ�������
	//��������Ʈ����Ѵ�
	//�Լ��� ���ڷ� �ѱ���ִ�
	//void(*fp)(int, int); //���̵����� �޴��Լ��̸��� ��Ʈ��Ʈ
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