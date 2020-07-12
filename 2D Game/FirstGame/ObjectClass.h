#pragma once
#include "SDL_image.h"
#include "GameFunc.h"

class Creature {
protected:
	SDL_Rect creature_des_rect;
	SDL_Texture *creature_texture;
	int status;
	int xpos;
	int ypos;
	int xvel;
	int yvel;
	int health_point;
	int attack_power;

public:
	void Draw();
	void GetAttacked(int damage);
	void Move();
};
