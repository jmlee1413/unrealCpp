#pragma once
#include <Windows.h>

class GameTImer
{
public:
	GameTImer();
	~GameTImer();

	void StartTime();
	double GetTime() const;
	double DeltaTime();

	void UpdateTimer();
	void Reset();
	int GetFPS() const;

private:
	double countsPerSecond = 0.f;
	__int64 countStart = 0;
	int frameCount = 0;
	int fps = 0;

	__int64 prevFrameTime = 0;
};

