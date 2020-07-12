#pragma once
#include "Monster.h"
#include "Hero.h"
#include "Missile.h"
#include <list>

class OldMonster : public Monster {
protected:
	int len;

public:
	OldMonster();
	OldMonster(int x);
	~OldMonster();

	void Draw();
	void FrameControl();
	void throwMissile(std::list<Missile*>* missile);

};