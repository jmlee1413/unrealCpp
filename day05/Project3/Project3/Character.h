#pragma once
#define UP 0x48 
#define DOWN 0x50 
#define LEFT 0x4B 
#define RIGHT 0x4D


// player, monster�� ��ġ�� ����� �����Ƿ�
// ĳ���� Ŭ������ ���� ��ӽ�Ű���� �ϰڴ�.

// player 100���� �ְ� ������ move�Լ��� �ִ°��
// 100���� ������ ���ľ���
// character��ӹ����� �ϳ��� ��ġ�� player�� �ڵ����� ��������
class Character
{
public: // �ۿ��� ���ڵ��� �� + ����� ���ְڴٴ� ��
	// private�� ��ӵŵ� �ڽ��� ��� ����

	Character();
	~Character();

	int X;
	int Y;

	virtual void Move(class Map* map, int KeyCode );
	virtual void Draw(); 
	// virtual�� �ڽĿ��� ����� �������ϰڴٴ� ��
	// �θ� ����� ����������� ��
	// �ٵ� ���� ���� ������ �������� ������
	// ������ �ڽĿ��� �����ڴٴ¶�
	// ������� ���ָ��

	virtual void Init();

// ����� ���ְ����� �ٸ����� ����ȵȴ� ��ӹ��� Ŭ���� �������� ��������
//protected:
//	void clear();

};

