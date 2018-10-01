#pragma once
class Engine
{
public:
	Engine();
	~Engine();

	void Run();

	class Map* map; // ��򰡿� Map�̶�°��ִ� ��������
	// �׷��� ���� ������� #include "Map.h" �Ƚᵵ��
	// new�� �ȸ�������ϱ� �����⸸ �����. �����δ� �ȸ��������
	// map�� ��� 2�Ⱑ�������ϸ� ���⼭�����ȵ�

	class Goal* goal;

	class Player* player;

	class Monster* monster;

private:
	//���ܳ��´�
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

