#pragma once
class Engine
{
public:
	Engine();
	~Engine();

	void run();

	bool bIsRunning;

private:
	//���ܳ��´�
	int Input();
	void Process(int KeyCode);
	void Render();
};

