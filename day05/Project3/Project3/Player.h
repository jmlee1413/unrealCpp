#pragma once
#include "Job.h" // enum은 include해야되나봄
#include "Character.h"

// 상속
class Player : public Character // public으로 상속하겠다
{
public:
	Player();
	~Player();

	// 상속하면 다 없어져도 됨
	//int x;
	//int y;

	//class Ejob job;으로 안됨 enum이라서
	EJob job;

	//void Move(int KeyCode, class Map* map);

	virtual void Draw() override;
	// override : 상속받은건데 원본도있고 내것도 따로 있겠다는 뜻
	// 자식에서 override는 써도되고 안써도되는데
	// 부모에서 virtual은 꼭써야된다

	virtual void Init() override;
};

