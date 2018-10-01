#include "Map.h"
#include <iostream>
#include <fstream> // ���������

Map::Map()
{
	sizeX = 20;
	sizeY = 20;
	InitMap();
}

Map::~Map()
{
}

void Map::Draw()
{
	//std::cout << map[0][1] << std::endl; // []�� �迭�̾ƴ϶� ���ڿ� ���۷�����
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			if (map[y][x] == '1')
			{
				std::cout << map[y][x];
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

bool Map::IsWall(int x, int y)
{
	if (x<0 || y<0 || x >= sizeX || y >= sizeY)
	{
		return true;
	}
	else
	{
		return map[y][x] == '1';
	}
}

void Map::InitMap()
{
	// map[10][10]���� �ҷ��� �̹� �ʱ�ȭ�� ���־
	// map[0][1] �� �ؾ��ϴ� ��Ȳ�̶� �׳� ��Ʈ������
	//map[0] = "1111111111";
	//map[1] = "1000000001";
	//map[2] = "1000000001";
	//map[3] = "1001111001";
	//map[4] = "1000000001";
	//map[5] = "1000000001";
	//map[6] = "1001111001";
	//map[7] = "1000000001";
	//map[8] = "1000000031";
	//map[9] = "1111111111";

	////���Ϸ� ���� �о����
	//FILE* fp;
	//fp = fopen("map.txt", "r");
	//if (fp)
	//{
	//	for (int i = 0; i < 20; ++i)
	//	{
	//		char Buffer[1024] = { 0 };
	//		fgets(Buffer, 1023, fp);
	//		map[i] = Buffer;
	//	}
	//}

	//fclose(fp);

	
	std::ifstream infile("map.txt");
	for (int i = 0; i < 20; i++)
	{
		std::getline(infile, map[i]);
	}
	infile.close();
}
