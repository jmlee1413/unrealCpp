#include "Character.h"

#pragma once
class Monster : public Character
{
public:
	Monster();
	~Monster();

	// ����ϸ� ����������
	//int x;
	//int y;
	//virtual void Init() override;
	virtual void Move(class Map* map, int KeyCode = 0) override; // ���� �����ͷ� �о�´�
	// moveȣ���ҋ� keycode=0 ���� keycode�� �� �ȳ־��൵�ȴ�


	virtual void Draw() override;
	// character�� ��ӹ޾����� monster�� ����ϴ� Ŭ�������ִ°��
	// �������Ҽ��ֵ��� virtual �߰�
};

