#pragma once
#include "Job.h" // enum�� include�ؾߵǳ���
#include "Character.h"

// ���
class Player : public Character // public���� ����ϰڴ�
{
public:
	Player();
	~Player();

	// ����ϸ� �� �������� ��
	//int x;
	//int y;

	//class Ejob job;���� �ȵ� enum�̶�
	EJob job;

	//void Move(int KeyCode, class Map* map);

	virtual void Draw() override;
	// override : ��ӹ����ǵ� �������ְ� ���͵� ���� �ְڴٴ� ��
	// �ڽĿ��� override�� �ᵵ�ǰ� �Ƚᵵ�Ǵµ�
	// �θ𿡼� virtual�� ����ߵȴ�

	virtual void Init() override;
};

