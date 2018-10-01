#pragma once
#include "Character.h"
class Monster:public Character
{
public:
	Monster();
	virtual ~Monster();

protected:
	void GiveItem();
};

