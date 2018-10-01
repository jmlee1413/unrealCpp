#include <stdio.h>
#include <iostream>
#include <bitset>
#include <conio.h>

using namespace std;

typedef unsigned char byte;
typedef int int32;
// 게임만들떄 그냥 이렇게 바꿔버림
// int가 뭔int인지모르니까

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
//	printf("몇개의 수를 입력할것인가\n");
//	scanf("%d", &count);
//	long long input[3];
//	long long result[3];
//	long long temp = 2;
//
//	for (int j = 0; j < count; j++)
//	{
//		printf("%d번쨰 수\n", j+1);
//		scanf("%lld", &input[j]);
//		temp = 2;
//		 곱하기는 엄청오래걸린다 비트연산으로바꿔야댐
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
//	 ^연산자: a^b 두값이 다를때 1을 반환
//	 |연산자: a|b 둘중하나가 참일떄 1을 반환
//	 &연산자: a&b 둘다 참일떄 1을 반환
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
//	//0010 -> 3 합한것처럼나온다
//	std::cout << (a|b) << std::endl;
//
//	std::cout << bitset<4>(a) << endl;
//	// 2진수로 바꿔서 표현
//
//	// a = a << 1; a에있는 비트를 왼쪽으로 한자리 이동
//	a = a << 1;
//	std::cout << bitset<4>(a) << endl;
//
//	// 오른쪽으로 두자리이동 남는건 버린다
//	a = a >> 2;
//	std::cout << bitset<4>(a) << endl;
//
//	// 8비트로찍어보면 왼쪽으로 가잇다
//	// 근데 한번 넘어갔으면 사라짐
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
//	cout << "방향키를 입력하시오" << endl;
//	//unsigned char a = 1;
//	byte a = 0x01;
//	cout << bitset<8>(a) << endl;
//	int pos = 0;
//	//pos를 하나만들어서 검사하기
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
////비트마스크
//#define O1 0x01 // 0000 0001  1<<0
//#define O2 0x02 // 0000 0010  1<<1
//#define O3 0x04 // 0000 0100  1<<2
//#define O4 0x08 // 0000 1000  1<<3
//#define O5 0x10 // 0001 0000  1<<4
//#define O6 0x20 // 0010 0000  1<<5
//#define O7 0x40 // 0100 0000  1<<6
//#define O8 0x80 // 1000 0000  1<<7
////8가지 옵션을 한바이트로 저장할수있다
//
//int main()
//{
//	byte option = O1 | O2 | O5;
//	// 옵션 키기
//	if (option & (O2 | O4)) // 2,4번중 하나가 옵션에 포함되는지?
//	{
//		cout << "true" << endl;
//	}
//
//	//2*2*2 보다는
//	//1<<2 식으로 바꿀수있다
//
//	return 0;
//}


#include <vector>

//2의승수 구하는문제 비트연산으로 해보기
int main()
{
	int N = 0;
	unsigned long long InputNumber;
	unsigned long long Result;

	vector <unsigned long long> X; // 배열인데 갯수를 늘릴수있다

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
			// longlong은 LL 써줘야함 기본은 int이기 떄문에
			// pow(2,bit) 쓰는것보다 빠르다
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



