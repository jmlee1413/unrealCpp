//#include <iostream>
//using namespace std;
//#include <vector>
//
//int main()
//{
//	vector<int> list1 = { 1,2,3 };
//	vector<vector<int>> outlist;
//
//	//1
//	for (int i = 0; i < list1.size(); ++i)
//	{
//		vector<int> templist = { list1[i] };
//		outlist.push_back(templist);
//	}
//	//2
//	for (int i = 0; i < list1.size(); ++i)
//	{
//		vector<int> templist = { list1[i], list1[(i+1)%3] };
//		outlist.push_back(templist);
//	}
//	//3
//	outlist.push_back(list1);
//
//	for (int i = 0; i < outlist.size(); ++i)
//	{
//		for (int j = 0; j < outlist[i].size(); ++j)
//		{
//			cout << outlist[i][j];
//		}
//		cout << endl;
//	}
//
//	return 0;
//}