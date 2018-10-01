#include "Engine.h"
#include <iostream>

using namespace std;

Engine::Engine()
{
	bIsRunning = true;
	cout << "엔진생성" << endl;
}


Engine::~Engine()
{
}

void Engine::run()
{
	while (bIsRunning)
	{
		cout << "Running" << endl;
		int KeyCode = Input();
		Process(KeyCode);
		Render();
	}
}

int Engine::Input()
{
}

void Engine::Process(int KeyCode)
{
}

void Engine::Render()
{
}
