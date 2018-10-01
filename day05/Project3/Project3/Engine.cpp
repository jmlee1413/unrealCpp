#include "Engine.h"
#include "Map.h"
#include "Goal.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

Engine::Engine()
{
	// ���� �ʱ�ȭ�� �����ڿ���
	bIsRunning = true;

	map = new Map(); // ����� �̸� ����������
	player = new Player();
	goal = new Goal();
	monster = new Monster();

	InitGoalPosition();
	InitMonsterPosition();

}


Engine::~Engine()
{
	// ������� �Ųٷ� ����°� ����
	delete monster;
	monster = nullptr;

	delete goal;
	goal = nullptr;

	delete player;
	player = nullptr;

	delete map;
	map = nullptr;
}

void Engine::Run()
{
	while (bIsRunning)
	{
		int KeyCode = Input();
		Process(KeyCode);
		Render();
	}
}

int Engine::Input()
{
	return _getch();
}

void Engine::Process(int KeyCode)
{
	// ������ �� ��
	// ĳ���� �̵�
	player->Move( map, KeyCode);
	monster->Move(map); // ������ �� ������ ���״� ���Ͱ� ����������

	// ��������
	IsComplete();
	IsFail();
	IsQuit(KeyCode);
}

void Engine::StopEngine()
{
	bIsRunning = false;
}

void Engine::IsQuit(int KeyCode)
{
	if (KeyCode == 'q' || KeyCode == 'Q')
	{
		bIsRunning = false;
	}
}

void Engine::IsComplete()
{
	if (player->X == goal->X && player->Y == goal->Y)
	{
		//win
		StopEngine();
	}

}

void Engine::IsFail()
{
	if (player->X == monster->X && player->Y == monster->Y)
	{
		//lose
		StopEngine();
	}
}

void Engine::Render()
{
	system("cls");

	map->Draw();
	// �ֿܼ� ���� ���� �׸��� �� ���� �÷��̾ �׸����̴�
	// ���� ���ӿ����� �׸��� ����
	goal->Draw();

	player->Draw();

	monster->Draw();
	
}

void Engine::InitGoalPosition()
{
	for (int y = 0; y < map->sizeY; y++)
	{
		for (int x = 0; x < map->sizeX; x++)
		{
			if (map->map[y][x] == '3')
			{
				goal->X = x;
				goal->Y = y;
			}
		}
	}
}

void Engine::InitMonsterPosition()
{
	for (int y = 0; y < map->sizeY; y++)
	{
		for (int x = 0; x < map->sizeX; x++)
		{
			if (map->map[y][x] == '4')
			{
				monster->X = x;
				monster->Y = y;
			}
		}
	}
}
