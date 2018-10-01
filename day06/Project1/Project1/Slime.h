#pragma once
#include <string>
#include "Monster.h"

class Slime: public Monster
{
public:
	Slime();
	virtual ~Slime();

	virtual void Tick() override;
	virtual void Draw() override;
};

