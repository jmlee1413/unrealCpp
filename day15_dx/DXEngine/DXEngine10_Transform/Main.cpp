#include <Windows.h>
#include "Engine.h"

// ������ �����Լ� ���� ������
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
