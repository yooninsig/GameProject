#pragma once
#include "Creature.h"
#include "Missile.h"
#include <list>
#include "Hero.h"
#include "SDL_mixer.h"

class Monster : public Creature
{
public:
	static const int NormalCreatureWidth = 80;
	static const int NormalCreatureHeight = 100;
protected:
	int len;
	Mix_Chunk* attackSound;

public:
	Monster();
	~Monster();

	virtual void Draw() = 0;
	virtual void throwMissile(std::list<Missile*>* missile) = 0;
	virtual void FrameControl() = 0;
	void Move_Xpos();
	void Attack(Hero* hero);
	bool isDistance(Hero* hero);
	bool AttackableStatus();
	void Attacked(Creature* m);
};