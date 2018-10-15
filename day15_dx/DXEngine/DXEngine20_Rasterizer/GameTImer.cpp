#include "GameTImer.h"
#include "DXApp.h"


GameTimer::GameTimer()
{
}


GameTimer::~GameTimer()
{
}

void GameTimer::StartTime()
{
	LARGE_INTEGER frequencyCount;

	// �ϵ���� ������(hz) ����.
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = (double)frequencyCount.QuadPart;

	// ƽ(Tick = Frame).
	QueryPerformanceCounter(&frequencyCount);
	countStart = frequencyCount.QuadPart;
}

double GameTimer::GetTime() const
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	double time
		= (double)((currentTime.QuadPart - countStart)
			/ countsPerSecond);

	return time;
}

double GameTimer::DeltaTime()
{
	// ƽ ���� ���� �ð� ���ϱ�.
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// ���� �����ӿ��� ���� �����ӱ��� ƽ ������ �󸶳� �������� ���.
	__int64 tickCount = currentTime.QuadPart - prevFrameTime;

	// ���� ������ �ð� ����.
	prevFrameTime = currentTime.QuadPart;

	// ���� ó��.
	if (tickCount < 0.0f)
		tickCount = 0.0f;

	// ������ �ð��� ��(����) �ð����� ��ȯ.
	double deltaTime = (double)(tickCount / countsPerSecond);

	// ���� ó��.
	if (deltaTime < 0.0)
		deltaTime = 0.0;

	return deltaTime;
}

void GameTimer::UpdateTimer(DXApp* app)
{
	//ƽ ������ ������ �� ������Ű��
	++frameCount;
	//1�ʰ� ������ Ÿ�̸� �ʱ�ȭ
	if (GetTime() > 1.f)
	{
		Reset(app);
	}
}

void GameTimer::Reset(DXApp* app)
{
	fps = frameCount;
	frameCount = 0;
	StartTime();

	// fps�� �ֿܼ� ���
	OutputDebugString(L"FPS: ");
	wchar_t buffer[256];
	_itow_s(fps, buffer, 10);
	OutputDebugString(buffer);
	OutputDebugString(L"\n");

	
	// â�̸��� ���
	float mspf = 1.0f / fps; // frame �� ms�ð�
	std::wostringstream outstream;
	outstream.precision(6);
	outstream << app->GetAppName() << L" " 
		<< L"Fps: " << fps << L" "
		<< L"Frame Time: " << mspf << L"(s)";
	SetWindowText(app->GetWindowHandle(), outstream.str().c_str());

}

int GameTimer::GetFPS() const
{
	return fps;
}
