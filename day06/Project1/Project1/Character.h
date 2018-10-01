#pragma once
#include <string>

class Character
{
public:
	Character();
	virtual ~Character(); // virtual 붙여줘야 자식 삭제도 콜된다

	virtual void Tick();

	virtual void Draw();

	//accessor
	void SetName(std::string newName);
	std::string GetName();

protected:
	std::string name; // 글자수제한 특수문제제한
	// 이름은 예외처리해서 쓸거라서 private으로 넣는다
	void Move();

};

