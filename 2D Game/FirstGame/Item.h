#pragma once
#include "Creature.h"
#include "Hero.h"

class Item : public GameObject
{public:
	const static int ITEM_SIZE = 50;

protected:
	//1 : ����, 2 : ����, 3 : �İ�, 4 : ȭ��, 5 : aPlus
	int type;

public:
	Item(int type, int x, int y);
	~Item();

	void SetType(int t);
	int GetType();

	void Draw();
	void Effect(Hero* hero);
};