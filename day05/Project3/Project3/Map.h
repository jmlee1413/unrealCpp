#pragma once
#include <string>

class Map
{
public:
	Map();
	~Map();

	int sizeX;
	int sizeY;
	std::string name; // Ŭ�������� �׳� std ����

	std::string map[20];

	void Draw();
	bool IsWall(int x, int y);
	void InitMap();
	
};

