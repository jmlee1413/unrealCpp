#include <string>
#include <iostream>
#include <stdio.h>
#include <bitset>

using namespace std;

string ToBinary(string output, int num, int length)
{
	if (num == 0)
	{
		while (output.length() < length)
		{
			output = "0" + output;
		}
		return output;
	}
	output = to_string(num % 2) + output;

	return ToBinary(output, num / 2, length);
}
//
//string GetMap(int num, string* arr1 ,string* arr2)
//{
//	string output = "";
//	for (int i = 0; i < num; ++i)
//	{
//		output = "";
//		for (int j = 0; j < num; ++j)
//		{
//			if (arr1[i][j] == '0' && arr2[i][j] == '0')
//			{
//				output += " ";
//			}
//			else
//			{
//				output += "#";
//			}
//		}
//		cout << output << endl;
//	}
//	return output;
//}

string* FindMap(int num, int* arr1, int* arr2)
{
	int* arr3 = new int[num];
	string* result = new string[num];
	for (int i = 0; i < num; ++i)
	{
		arr3[i] = arr1[i] | arr2[i];
		result[i] = bitset<16>(arr3[i]).to_string();
		result[i] = result[i].substr(16 - num, num);

		for (int len = 0; len < result[i].length(); ++len)
		{
			result[i][len] = result[i][len] == '1' ? '#' : ' ';
		}
	}
	delete[] arr3;
	return result;
}

int main()
{
	int num;
	
	cout << "array °¹¼ö¸¦ ÀÔ·Â" << endl;
	cin >> num;

	string* outarr1 = new string[num];
	string* outarr2 = new string[num];

	int* arr1;
	int* arr2;

	if (num == 5)
	{
		arr1 = new int[5]{ 9,20,28,18,11 };
		arr2 = new int[5]{ 30,1,21,7,28 };
	}
	else if (num == 6)
	{
		arr1 = new int[6]{ 46, 33, 33 ,22, 31, 50 };
		arr2 = new int[7]{ 27 ,56, 19, 14, 14, 10 };
	}

	/*for (int i = 0; i < num; ++i)
	{
		outarr1[i] = ToBinary("", arr1[i], num);
	}

	for (int i = 0; i < num; ++i)
	{
		outarr2[i] = ToBinary("", arr2[i], num);
	}
*/
	//GetMap(num, outarr1, outarr2);

	string* result = FindMap(num, arr1, arr2);

	for (int i = 0; i <num; i++)
	{
		cout << result[i] << endl;
	}

	delete[] result;
	return 0;
}

