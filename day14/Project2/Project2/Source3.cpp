//#include <iostream>
//#include <vector>
//#include <math.h>
//using namespace std;
//
//class Dot
//{
//public:
//	Dot(int newx=0, int newy=0) { x = newx; y = newy; }
//	int x;
//	int y;
//};
//
//class Circle
//{
//public:
//	Circle(int newx, int newy, int newlength) 
//	{ 
//		x = newx; y = newy; length = newlength; 
//	}
//	int x;
//	int y;
//	int length;
//
//};
//
//void LineMeetCirlce(Dot start, Dot end, Circle newcircle)
//{
//	//// (���� ��start�Ÿ� - ������)�� �� �������� �Ÿ����� ũ�� �浹����
//	//double dotlength = sqrt((end.y - start.y)*(end.y - start.y) + (end.x - start.x)*(end.x - start.x));
//	//double circleline = sqrt((newcircle.y - start.y)*(newcircle.y - start.y) + (newcircle.x - start.x)*(newcircle.x - start.x));
//	//if (circleline - newcircle.length > dotlength)
//	//{
//	//	cout << "�浹x" << endl;
//	//	return;
//	//}
//
//	// ������ ���� �������ϱ�
//	double m = (end.y - start.y) / (end.x - start.x);
//	double a = m;
//	double b = -1;
//	double c = -m * start.x + start.y;
//	double  d = sqrt((a*newcircle.x + b * newcircle.y + c)*(a*newcircle.x + b * newcircle.y + c) / (a*a) + (b*b));
//
//	if (d <= newcircle.length)
//	{
//		cout << "�浹" << endl;
//	}
//	else
//	{
//		cout << "�浹x" << endl;
//	}
//	return;
//}
//
//int main()
//{
//	Dot lstart = Dot(0, 0);
//	Dot lend = Dot(10, 10);
//	Circle c1 = Circle(5,5,5);
//	LineMeetCirlce(lstart, lend, c1);
//
//	Dot lstart2 = Dot(0, 0);
//	Dot lend2 = Dot(10, 10);
//	Circle c2 = Circle(20, 20, 1);
//	LineMeetCirlce(lstart2, lend2, c2);
//
//	return 0;
//}