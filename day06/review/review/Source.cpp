#include <stdio.h>
#include <iostream>
#include <bitset>
#include <conio.h>

using namespace std;

typedef unsigned char byte;
typedef int int32;
// ���Ӹ��鋚 �׳� �̷��� �ٲ����
// int�� ��int�����𸣴ϱ�

#define LEFT 0x4B 
#define RIGHT 0x4D


//
//int clamp(int x, int min, int max)
//{
//	if (x < min)
//	{
//		x = min;
//	}
//	else if (x > max)
//	{
//		x = max;
//	}
//	else
//	{
//		x = x;
//	}
//	return x;
//}
//
//int main()
//{
//	int count;
//	printf("��� ���� �Է��Ұ��ΰ�\n");
//	scanf("%d", &count);
//	long long input[3];
//	long long result[3];
//	long long temp = 2;
//
//	for (int j = 0; j < count; j++)
//	{
//		printf("%d���� ��\n", j+1);
//		scanf("%lld", &input[j]);
//		temp = 2;
//		 ���ϱ�� ��û�����ɸ��� ��Ʈ�������ιٲ�ߴ�
//		while (input[j] > 2)
//		{
//			temp = temp * 2;
//			if (input[j] < temp)
//			{
//				result[j] = temp;
//				break;
//			}
//			printf("%lld\n", temp);
//		}
//		printf("recieving: %lld %lld \n", input[j], result[j]);
//	}
//
//	printf("Result : %lld", result[0] ^ result[1] ^ result[2]);
//	 ^������: a^b �ΰ��� �ٸ��� 1�� ��ȯ
//	 |������: a|b �����ϳ��� ���ϋ� 1�� ��ȯ
//	 &������: a&b �Ѵ� ���ϋ� 1�� ��ȯ
//
//
//
//
//
//
//
//	unsigned char a = 0x03;
//	unsigned char b = 0x02;
//
//	//0011
//	//0010 -> 2
//	std::cout << (a&b) << std::endl;
//
//	//0011
//	//0010 -> 3 ���Ѱ�ó�����´�
//	std::cout << (a|b) << std::endl;
//
//	std::cout << bitset<4>(a) << endl;
//	// 2������ �ٲ㼭 ǥ��
//
//	// a = a << 1; a���ִ� ��Ʈ�� �������� ���ڸ� �̵�
//	a = a << 1;
//	std::cout << bitset<4>(a) << endl;
//
//	// ���������� ���ڸ��̵� ���°� ������
//	a = a >> 2;
//	std::cout << bitset<4>(a) << endl;
//
//	// 8��Ʈ������ �������� ���մ�
//	// �ٵ� �ѹ� �Ѿ���� �����
//	a = a << 4;
//	std::cout << bitset<8>(a) << endl;
//
//
//
//
//
//
//
//
//	cout << "����Ű�� �Է��Ͻÿ�" << endl;
//	//unsigned char a = 1;
//	byte a = 0x01;
//	cout << bitset<8>(a) << endl;
//	int pos = 0;
//	//pos�� �ϳ����� �˻��ϱ�
//
//	while (true)
//	{
//		int key = _getch();
//		if (key == LEFT)
//		{
//			//if (bitset<8>(a << 1) != 0)
//			//{
//			//	a = a << 1;
//			//	cout << bitset<8>(a) << endl;
//			//}
//			pos++;
//			pos = clamp(pos, 0, 7);
//			cout << bitset<8>(1 << pos) << endl;
//		}
//		else if (key == RIGHT)
//		{
//			//if ((a >> 1) >= 1)
//			//{
//			//	a = a >> 1;
//			//	cout << bitset<8>(a) << endl;
//			//}
//			pos--;
//			pos = clamp(pos, 0, 7);
//			cout << bitset<8>(1 << pos) << endl;
//		}
//		else if (key == 'q')
//		{
//			break;
//		}
//		
//	}
//
//
//
//
//	return 0;
//}
//
//
//
////��Ʈ����ũ
//#define O1 0x01 // 0000 0001  1<<0
//#define O2 0x02 // 0000 0010  1<<1
//#define O3 0x04 // 0000 0100  1<<2
//#define O4 0x08 // 0000 1000  1<<3
//#define O5 0x10 // 0001 0000  1<<4
//#define O6 0x20 // 0010 0000  1<<5
//#define O7 0x40 // 0100 0000  1<<6
//#define O8 0x80 // 1000 0000  1<<7
////8���� �ɼ��� �ѹ���Ʈ�� �����Ҽ��ִ�
//
//int main()
//{
//	byte option = O1 | O2 | O5;
//	// �ɼ� Ű��
//	if (option & (O2 | O4)) // 2,4���� �ϳ��� �ɼǿ� ���ԵǴ���?
//	{
//		cout << "true" << endl;
//	}
//
//	//2*2*2 ���ٴ�
//	//1<<2 ������ �ٲܼ��ִ�
//
//	return 0;
//}


#include <vector>

//2�ǽ¼� ���ϴ¹��� ��Ʈ�������� �غ���
int main()
{
	int N = 0;
	unsigned long long InputNumber;
	unsigned long long Result;

	vector <unsigned long long> X; // �迭�ε� ������ �ø����ִ�

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> InputNumber;
		X.push_back(InputNumber);
	}

	for (int i = 0; i < X.size(); ++i)
	{
		unsigned long long choice = 0;
		for (int bit = 1; bit < 64; bit++)
		{
			choice = 1LL << bit;
			// longlong�� LL ������� �⺻�� int�̱� ������
			// pow(2,bit) ���°ͺ��� ������
			if (choice >= X[i])
			{
				if (i == 0)
				{
					Result = choice;
				}
				else
				{
					Result ^= choice;
				}
				break;
			}
		}
	}

	cout << Result << endl;
	return 0;
}



