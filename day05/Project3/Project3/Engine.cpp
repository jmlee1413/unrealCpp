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
	// 변수 초기화는 생성자에서
	bIsRunning = true;

	map = new Map(); // 헤더에 미리 만들어놨던것
	player = new Player();
	goal = new Goal();
	monster = new Monster();

	InitGoalPosition();
	InitMonsterPosition();

}


Engine::~Engine()
{
	// 만든순서 거꾸로 지우는게 좋다
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
	// 엔진이 할 일
	// 캐릭터 이동
	player->Move( map, KeyCode);
	monster->Move(map); // 엔진이 맵 정보를 줄테니 몬스터가 움직여봐라

	// 게임판정
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
	// 콘솔에 맵을 먼저 그리고 그 위에 플레이어를 그릴것이다
	// 실제 게임엔진이 그리는 순서
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
