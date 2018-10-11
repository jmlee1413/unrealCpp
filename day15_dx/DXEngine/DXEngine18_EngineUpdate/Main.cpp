#include <Windows.h>
#include "Engine.h"

// 윈도우 메인함수 고대로 가져옴
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	LPSTR IpCmdLine,
	int nCmdLine)
{
	Engine engine(hinstance);

	if (engine.Init() == false)
		return 0;

	return engine.Run();
}
