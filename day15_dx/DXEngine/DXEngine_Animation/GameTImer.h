#pragma once
#include <Windows.h>
//#include "DXApp.h"
// dxapp에서 gametimer 인클루드 중
// 여기서 또하지말고 class DxApp 선언해서 해결
#include <string>
#include <sstream>
#include <fstream>

class DXApp;

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	void StartTime();
	double GetTime() const;
	double DeltaTime();

	void UpdateTimer(DXApp* app);
	void Reset(DXApp* app);
	int GetFPS() const;

private:
	double countsPerSecond = 0.f;
	__int64 countStart = 0;
	int frameCount = 0;
	int fps = 0;

	__int64 prevFrameTime = 0;
};

