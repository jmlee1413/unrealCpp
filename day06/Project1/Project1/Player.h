#pragma once
#include "Character.h"
#include <string>


class Player : public Character
{
public:
	// 생성자 꼭 잇어야된다 나중에 player끼리 복사/비교할라면
	Player();
	virtual ~Player();

	void Input();
	virtual void Tick() override;
	virtual void Draw() override;

protected:
	void Skill1();
};

