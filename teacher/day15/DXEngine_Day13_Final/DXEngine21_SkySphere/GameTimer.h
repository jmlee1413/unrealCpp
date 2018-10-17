#pragma once

#include <Windows.h>
//#include "DXApp.h"
#include <string>
#include <sstream>
#include <fstream>

class DXApp;

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	// ���� Ÿ�̸� ���� �޼ҵ�.
	void StartTime();
	double GetTime() const;
	double DeltaTime();

	void UpdateTimer(DXApp* app);
	void Reset(DXApp* app);
	int GetFPS() const;

private:

	// Ÿ�̸� ���� ����.
	double countsPerSecond = 0.0;
	__int64 countStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 prevFrameTime = 0;
};