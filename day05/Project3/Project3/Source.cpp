#include "Engine.h"
#include "Map.h"

int main()
{
	//Engine e;
	//e.run();

	Engine* e = new Engine();
	e->Run();
	delete e;
	e = nullptr; // ����Ʈ �� ������ e���� �ʱ�ȭ���ش�

	//Map* m = new Map();
	//m->Draw();

	return 0;
}