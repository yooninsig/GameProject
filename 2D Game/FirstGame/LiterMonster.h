#pragma once
#include "Monster.h"
#include "Missile.h"
#include <list>
#include "Hero.h"

class LiterMonster : public Monster {
protected:
	
public:
	LiterMonster();
	LiterMonster(int x);
	~LiterMonster();

	void Draw();
	void FrameControl();
	void throwMissile(std::list<Missile*>* missile);
};