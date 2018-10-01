#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> CutList(int* target, int start, int end)
{
	start--; end--;
	vector<int> temp;
	{
		for (int i = start; i <= end; ++i)
		{
			temp.push_back(target[i]);
		}
		sort(temp.begin(), temp.end());
	}
	return temp;
}

int main()
{
	int target[] = { 1, 5, 2, 6, 3, 7, 4 };
	int l2[] = { 2, 5, 3 };
	int l3[] = { 4, 4, 1 };
	int l4[] = { 1, 7, 3 };
	vector<int> commands;

	/*vector<int> out1 = CutList(l1, l2[0], l2[1]);
	commands.push_back(out1[l2[2]-1]);*/

	commands.push_back(CutList(target, l2[0], l2[1])[l2[2] - 1]);
	commands.push_back(CutList(target, l3[0], l3[1])[l3[2]-1]);
	commands.push_back(CutList(target, l4[0], l4[1])[l4[2]-1]);

	for (int i = 0; i < commands.size(); ++i)
	{
		cout << commands[i] << " ";
	}

	return 0;
}
