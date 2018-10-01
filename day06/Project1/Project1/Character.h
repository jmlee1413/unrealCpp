#pragma once
#include <string>

class Character
{
public:
	Character();
	virtual ~Character(); // virtual �ٿ���� �ڽ� ������ �ݵȴ�

	virtual void Tick();

	virtual void Draw();

	//accessor
	void SetName(std::string newName);
	std::string GetName();

protected:
	std::string name; // ���ڼ����� Ư����������
	// �̸��� ����ó���ؼ� ���Ŷ� private���� �ִ´�
	void Move();

};

