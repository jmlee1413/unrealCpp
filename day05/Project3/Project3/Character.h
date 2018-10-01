#pragma once
#define UP 0x48 
#define DOWN 0x50 
#define LEFT 0x4B 
#define RIGHT 0x4D


// player, monster에 겹치는 기능이 많으므로
// 캐릭터 클래스를 만들어서 상속시키도록 하겠다.

// player 100개가 있고 각각의 move함수가 있는경우
// 100개의 파일을 고쳐야함
// character상속받으면 하나만 고치면 player는 자동으로 고쳐진다
class Character
{
public: // 밖에서 쓰겠따는 뜻 + 상속을 해주겠다는 뜻
	// private은 상속돼도 자식이 기능 못씀

	Character();
	~Character();

	int X;
	int Y;

	virtual void Move(class Map* map, int KeyCode );
	virtual void Draw(); 
	// virtual은 자식에서 기능을 재정의하겠다는 뜻
	// 부모 기능을 지우지마라는 뜻
	// 근데 많이 쓰면 포인터 많아져서 느려짐
	// 없으면 자식에서 덮어씌우겠다는뜻
	// 헤더에만 써주면됨

	virtual void Init();

// 상속은 해주겠으나 다른놈은 쓰면안된다 상속받은 클래스 내에서만 쓸수있음
//protected:
//	void clear();

};

