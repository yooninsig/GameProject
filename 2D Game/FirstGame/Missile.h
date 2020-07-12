#pragma once
#include "Creature.h"

class Missile : public GameObject
{
public:
	const static int MISSILE_SIZE = 50;
protected:
	//0 : 왼쪽, 1 : 오른쪽, 2 : 위, 3 : 아래
	int dir;
	//0 : 똥, 1 : 하이, 2 : 말, 3 : 씨플
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
