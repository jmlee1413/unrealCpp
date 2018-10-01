#pragma once
#include "Character.h"
#include <vector>

class Engine
{
public:
	Engine();
	~Engine();

	void Run(); // run�� ���ܳ��� �ټ���

protected:
	void Input();

	void Tick();

	void Render();

	//class Player* player;
	//class Goblin* goblin;
	//class Slime* slime;

	bool bIsRunning = true;

	//Character* characters[100]; // ���⼭ ������ �迭 �����
	//int TotalCharacterCount;
	std::vector<class Character*> characters;
	// �������̵� �����ε�
	// �������̵�: ��ӽõ����
	// �����ε�: ���� �Լ��� ���ڸ� �ٸ��Թ޴´�
};

