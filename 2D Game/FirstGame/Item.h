#pragma once
#include "Creature.h"
#include "Hero.h"

class Item : public GameObject
{public:
	const static int ITEM_SIZE = 50;

protected:
	//1 : 미콘, 2 : 수학, 3 : 컴공, 4 : 화학, 5 : aPlus
	int type;

public:
	Item(int type, int x, int y);
	~Item();

	void SetType(int t);
	int GetType();

	void Draw();
	void Effect(Hero* hero);
};