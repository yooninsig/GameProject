#pragma once
#include "Monster.h"
#include "Hero.h"
#include "Missile.h"
#include <list>

class ProfMonster : public Monster
{
protected:
	int len;
public:
	ProfMonster();
	ProfMonster(int x);
	~ProfMonster();

	void Draw();
	void FrameControl();
	void throwMissile(std::list<Missile*>* missile);
	void Attacked(Creature* m);

};
