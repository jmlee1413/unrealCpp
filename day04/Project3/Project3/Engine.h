#pragma once
class Engine
{
public:
	Engine();
	~Engine();

	void run();

	bool bIsRunning;

private:
	//¼û°Ü³õ´Â´Ù
	int Input();
	void Process(int KeyCode);
	void Render();
};

