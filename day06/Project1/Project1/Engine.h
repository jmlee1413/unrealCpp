#pragma once
#include "Character.h"
#include <vector>

class Engine
{
public:
	Engine();
	~Engine();

	void Run(); // run만 남겨놓고 다숨김

protected:
	void Input();

	void Tick();

	void Render();

	//class Player* player;
	//class Goblin* goblin;
	//class Slime* slime;

	bool bIsRunning = true;

	//Character* characters[100]; // 여기서 포인터 배열 만들고
	//int TotalCharacterCount;
	std::vector<class Character*> characters;
	// 오버라이드 오버로딩
	// 오버라이드: 상속시덮어쓴다
	// 오버로딩: 같은 함수에 인자를 다르게받는다
};

