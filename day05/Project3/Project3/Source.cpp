#include "Engine.h"
#include "Map.h"

int main()
{
	//Engine e;
	//e.run();

	Engine* e = new Engine();
	e->Run();
	delete e;
	e = nullptr; // 딜리트 후 포인터 e까지 초기화해준다

	//Map* m = new Map();
	//m->Draw();

	return 0;
}