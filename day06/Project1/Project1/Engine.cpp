#include "Engine.h"
#include "Player.h"
#include "conio.h"
#include "Goblin.h"
#include "Slime.h"
#include "Character.h"
#include <iostream>
#include <time.h>

using namespace std;

Engine::Engine()
{
	std::cout << "엔진생성" << std::endl;

	bIsRunning = true;

	//TotalCharacterCount = 6; // 여기에 캐릭터 6개가 들어갈것임
	//characters[0] = new Player();
	//characters[1] = new Goblin();
	//characters[2] = new Slime();
	//characters[3] = new Slime();
	//characters[4] = new Slime();
	//characters[5] = new Slime();

	//벡터는 지우는건 자동으로 지워진다
	characters.push_back(new Player());
	//characters.push_back(new Goblin());
	//characters.push_back(new Slime());

	srand(time(nullptr)); // rand 다르게 나오도록
	int GoblinCount = rand() % 5;
	int SlimeCount = rand() % 5;
	for (int i = 0; i < GoblinCount; i++)
	{
		characters.push_back(new Goblin());
	}
	for (int i = 0; i < GoblinCount; i++)
	{
		characters.push_back(new Slime());
	}

	//player = new Player();
	//goblin = new Goblin();
	//slime = new Slime();
}


Engine::~Engine()
{
	std::cout << "엔진삭제" << std::endl;
	//delete slime;
	//delete goblin;
	//delete player;

	for (int i = 0; i < characters.size(); i++)
	{
		delete characters[i];
	}
}

void Engine::Run()
{
	while (bIsRunning) //Game loop, Message Loop
	{
		Input();
		Tick();
		Render();
		cout << "------------------------------------\n" << endl;
		// 한프레임씩 처리
		int keycode = _getch();
		if (keycode == 'q')
		{
			bIsRunning = false;
		}
	}
}

void Engine::Input( )
{
	cout << "입력받는중" << endl;
	// 언리얼도 맨 첫번째가 플레이어
	//((Player*)characters[0])->Input();

	dynamic_cast<Player*>(characters[0])->Input();
	//Player* player = dynamic_cast<Player*>(characters[0])->Input();
	//로 실행되는 형식
	//한번 해보고 잘못됐으면 nullptr 돌려준다
	// if (characters[0] != nullptr)
	//{ characters[0]->Input();}

	//첫번째가 플레이어라는 가정하에 쓸수있따
}

void Engine::Tick() // 언리얼에서는 Tick
{
	cout << "매프레임 엔진 처리" << endl;
	//player->Tick();
	//goblin->Tick();
	//slime->Tick();

	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->Tick();
	}
}

void Engine::Render()
{
	cout << "화면에그린다" << endl;
	//player->Draw();
	//goblin->Draw();
	//slime->Draw();
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->Draw();
	}
}
