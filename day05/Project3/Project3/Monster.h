#include "Character.h"

#pragma once
class Monster : public Character
{
public:
	Monster();
	~Monster();

	// 상속하면 없어져도됨
	//int x;
	//int y;
	//virtual void Init() override;
	virtual void Move(class Map* map, int KeyCode = 0) override; // 맵을 포인터로 읽어온다
	// move호출할떄 keycode=0 쓰면 keycode에 뭐 안넣어줘도된다


	virtual void Draw() override;
	// character를 상속받았지만 monster를 상속하는 클래스가있는경우
	// 재정의할수있도록 virtual 추가
};

