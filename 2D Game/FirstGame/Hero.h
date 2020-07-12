#pragma once
#include "Creature.h"
#include "Missile.h"
#include "SDL_mixer.h"

class Hero : public Creature {
protected:
	int yvel;
	//0 : ���, 1 : ����, 2 : �İ�
	int itemType;
	int aPlus;
	Mix_Chunk* attackedSound;
	Mix_Chunk* basicSound;
	Mix_Chunk* mathSound;
	Mix_Chunk* comSound;

public:
	Hero();
	~Hero();
	
	int GetYvel();
	void SetYvel(int y);
	int GetItemType();
	void SetItemType(int t);
	int GetAplus();
	void SetAplus(int a);

	void Draw();
	void Move_Xpos();
	void Move_Ypos();
	void Attack();
	void Attacked(Creature* monster);
	void Attacked(Missile* missile);
	void Jump();
	bool isMoveable();
	void FrameControl();
};