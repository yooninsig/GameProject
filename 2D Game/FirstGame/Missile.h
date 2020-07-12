#pragma once
#include "Creature.h"

class Missile : public GameObject
{
public:
	const static int MISSILE_SIZE = 50;
protected:
	//0 : ����, 1 : ������, 2 : ��, 3 : �Ʒ�
	int dir;
	//0 : ��, 1 : ����, 2 : ��, 3 : ����
	int type;
	int damage;
	int len;
public:
	Missile(int type, int dir);
	~Missile();

	int GetType();
	void SetType(int t);
	int GetDir();
	void SetDir(int d);
	int GetDamage();
	void SetDamage(int d);
	int GetLen();
	void SetLen(int l);

	void Draw();
	void Move();
};
