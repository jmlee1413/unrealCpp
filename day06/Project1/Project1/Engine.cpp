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
	std::cout << "��������" << std::endl;

	bIsRunning = true;

	//TotalCharacterCount = 6; // ���⿡ ĳ���� 6���� ������
	//characters[0] = new Player();
	//characters[1] = new Goblin();
	//characters[2] = new Slime();
	//characters[3] = new Slime();
	//characters[4] = new Slime();
	//characters[5] = new Slime();

	//���ʹ� ����°� �ڵ����� ��������
	characters.push_back(new Player());
	//characters.push_back(new Goblin());
	//characters.push_back(new Slime());

	srand(time(nullptr)); // rand �ٸ��� ��������
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
	std::cout << "��������" << std::endl;
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
		// �������Ӿ� ó��
		int keycode = _getch();
		if (keycode == 'q')
		{
			bIsRunning = false;
		}
	}
}

void Engine::Input( )
{
	cout << "�Է¹޴���" << endl;
	// �𸮾� �� ù��°�� �÷��̾�
	//((Player*)characters[0])->Input();

	dynamic_cast<Player*>(characters[0])->Input();
	//Player* player = dynamic_cast<Player*>(characters[0])->Input();
	//�� ����Ǵ� ����
	//�ѹ� �غ��� �߸������� nullptr �����ش�
	// if (characters[0] != nullptr)
	//{ characters[0]->Input();}

	//ù��°�� �÷��̾��� �����Ͽ� �����ֵ�
}

void Engine::Tick() // �𸮾󿡼��� Tick
{
	cout << "�������� ���� ó��" << endl;
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
	cout << "ȭ�鿡�׸���" << endl;
	//player->Draw();
	//goblin->Draw();
	//slime->Draw();
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->Draw();
	}
}
