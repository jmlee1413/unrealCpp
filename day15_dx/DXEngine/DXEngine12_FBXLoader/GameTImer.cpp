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

	// �ϵ���� ������ hz
	QueryPerformanceFrequency(&frequencyCount);// �����͸�ä���ش�

	// �ʴ� ����Ƚ��
	countsPerSecond = (double)frequencyCount.QuadPart;

	// ƽ( tick = frame = update )
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
	// ƽ ������ ����ð�
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// ���� �����ӿ��� ���������ӱ��� ��ƽ���������� ���
	__int64 tickCount = currentTime.QuadPart - prevFrameTime;

	prevFrameTime = currentTime.QuadPart;

	//����ó��
	if (tickCount < 0.f)
	{
		tickCount = 0.f;
	}

	//�����ӽð��� �ʴ����� ��ȯ
	double deltaTime = (double)(tickCount / countsPerSecond);

	if (deltaTime < 0.f)
	{
		deltaTime = 0.f;
	}

	return deltaTime;
}

void GameTImer::UpdateTimer()
{
	//ƽ ������ ������ �� ������Ű��
	++frameCount;
	//1�ʰ� ������ Ÿ�̸� �ʱ�ȭ
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
