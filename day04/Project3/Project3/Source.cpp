#include "Engine.h"

int main()
{
	//Engine e;
	//e.run();

	Engine* e = new Engine();
	e->run();
	delete e;

	return 0;
}