#pragma once
#include "Character.h"
#include <string>


class Player : public Character
{
public:
	// ������ �� �վ�ߵȴ� ���߿� player���� ����/���Ҷ��
	Player();
	virtual ~Player();

	void Input();
	virtual void Tick() override;
	virtual void Draw() override;

protected:
	void Skill1();
};

