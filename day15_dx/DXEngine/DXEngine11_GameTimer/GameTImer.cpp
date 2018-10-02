#include "GameTImer.h"



GameTImer::GameTImer()
{
}


GameTImer::~GameTImer()
{
}

void GameTImer::StartTime()
{
	LARGE_INTEGER frequencyCount;

	// 하드웨어 진동수 hz
	QueryPerformanceFrequency(&frequencyCount);// 데이터를채워준다

	// 초당 진동횟수
	countsPerSecond = (double)frequencyCount.QuadPart;

	// 틱( tick = frame = update )
	QueryPerformanceCounter(&frequencyCount);
	countStart = frequencyCount.QuadPart;
}

double GameTImer::GetTime() const
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	double time = (double)((currentTime.QuadPart - countStart) / countsPerSecond);

	return time;
}

double GameTImer::DeltaTime()
{
	// 틱 단위의 현재시간
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// 현재 프레임에서 이전프레임까지 몇틱이지났는지 계산
	__int64 tickCount = currentTime.QuadPart - prevFrameTime;

	prevFrameTime = currentTime.QuadPart;

	//예외처리
	if (tickCount < 0.f)
	{
		tickCount = 0.f;
	}

	//프레임시간을 초단위로 변환
	double deltaTime = (double)(tickCount / countsPerSecond);

	if (deltaTime < 0.f)
	{
		deltaTime = 0.f;
	}

	return deltaTime;
}

void GameTImer::UpdateTimer()
{
	//틱 단위로 프레임 수 증가시키기
	++frameCount;
	//1초가 지나면 타이머 초기화
	if (GetTime() > 1.f)
	{
		Reset();
	}
}

void GameTImer::Reset()
{
	fps = frameCount;
	frameCount = 0;
	StartTime();
}

int GameTImer::GetFPS() const
{
	return fps;
}
