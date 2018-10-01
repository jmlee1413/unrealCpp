//#include <iostream>
//using namespace std;
//
//#define PATH 0
//#define WALL 1
//#define VISITED 2
//#define GOBACK 3
//
//#define MAX 5
//
//int Maze[MAX][MAX] = {
//	{0, 1, 1, 1, 0},
//	{0, 0, 0, 0, 0},
//	{1, 0, 1, 1, 1},
//	{1, 0, 1, 1, 1},
//	{1, 0, 0, 0, 0}
//};
//
//void PrintPath()
//{
//	for (int y = 0; y < MAX; ++y)
//	{
//		for (int x = 0; x < MAX; ++x)
//		{
//			if (Maze[y][x] == VISITED)
//			{
//				cout << x << " " << y << endl;
//			}
//		}
//	}
//}
//
//bool RFindPath(int currentx,int currenty)
//{
//	if (currentx < 0 || currentx > MAX ||
//		currenty < 0 || currenty > MAX)
//	{
//		return false;
//	}
//	else if (Maze[currenty][currentx] != PATH)
//	{
//		return false;
//	}
//	else if (currentx == MAX-1 && currenty == MAX-1)
//	{
//		Maze[currenty][currentx] = VISITED;
//		return true;
//	}
//	else
//	{
//		Maze[currenty][currentx] = VISITED;
//		if (RFindPath(currentx, currenty - 1) ||
//			RFindPath(currentx+1, currenty ) ||
//			RFindPath(currentx, currenty+1 ) ||
//			RFindPath(currentx-1, currenty ))
//		{
//			
//			return true;
//		}
//
//		Maze[currenty][currentx] = GOBACK;
//		return false;
//		
//	}
//}
//
//int main()
//{
//	RFindPath(0, 0);
//	PrintPath();
//	return 0;
//}