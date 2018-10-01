#pragma once
class Engine
{
public:
	Engine();
	~Engine();

	void Run();

	class Map* map; // 어딘가에 Map이라는게있다 만들어놔라
	// 그러면 여기 헤더에는 #include "Map.h" 안써도됨
	// new로 안만들었으니까 껍데기만 만든것. 실제로는 안만들어졌음
	// map이 사실 2기가라고생각하면 여기서만들면안됨

	class Goal* goal;

	class Player* player;

	class Monster* monster;

private:
	//숨겨놓는다
	int Input();
	void Process(int KeyCode);
	void StopEngine();
	void IsQuit(int KeyCode);
	void IsComplete();
	void IsFail();
	void Render();
	void InitGoalPosition();
	void InitMonsterPosition();

	bool bIsRunning;
};

