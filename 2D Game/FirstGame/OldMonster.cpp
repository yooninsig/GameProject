#include "SDL_image.h"
#include "OldMonster.h"
#include "TextureManager.h"
#include <time.h>
#include "GameFunc.h"

extern int ground_height;
extern int g_window_width;
extern int g_cur_time_ms;

OldMonster::OldMonster() {
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 3;
	attackPower = 1;
	xpos = g_window_width / 10 * 5;
	ypos = ground_height - NormalCreatureHeight;
	width = Monster::NormalCreatureWidth;
	height = Monster::NormalCreatureHeight;

}

OldMonster::OldMonster(int x) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 3;
	attackPower = 1;
	ypos = ground_height - NormalCreatureHeight;
	width = Monster::NormalCreatureWidth;
	height = Monster::NormalCreatureHeight;

	attackSound = Mix_LoadWAV("../music/oldAttack.wav");
	if (attackSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}

	xpos = x;
}

OldMonster::~OldMonster() {

}

void OldMonster::Draw() {
	int spriteIndex = 0;
	TextureManager* tm = TextureManager::GetSingleton();

	if (status == 8 || status == 9) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "old_attack" + std::to_string((long long)spriteIndex);
	}

	else if (status == 2 || status == 3) {
		spriteIndex = (frame_time_ms / 480) % 2;
		spriteId = "old_move" + std::to_string((long long)spriteIndex);
	}

	else if (status == 0 || status == 1) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "old_move" + std::to_string((long long)spriteIndex);
	}


	if (status % 2 == 0) {
		tm->DrawSpriteRef("old", spriteId, xpos, ypos, width, height);
	}
	else {
		tm->DrawSprite("old", spriteId, xpos, ypos, width, height);
	}
}
void OldMonster::FrameControl() {
	if (status == 8 || status == 9) {
		if (frame_time_ms >= 2000) {
			(status == 8) ? status = 2 : status = 3;
			frame_time_ms = 0;
		}
	}

	frame_time_ms += 30;
}

void OldMonster::throwMissile(std::list<Missile*>* missile) {
	Missile* m1;
	Missile* m2;
	Missile* m3;

	m1 = new Missile(2, 0);
	m1->SetWidth(Missile::MISSILE_SIZE);
	m1->SetHeight(Missile::MISSILE_SIZE);
	m1->SetXpos(xpos - Missile::MISSILE_SIZE);
	m1->SetYpos(ypos + 35);
	missile->push_back(m1);

	m2 = new Missile(2, 1);
	m2->SetWidth(Missile::MISSILE_SIZE);
	m2->SetHeight(Missile::MISSILE_SIZE);
	m2->SetXpos(xpos + Monster::NormalCreatureWidth);
	m2->SetYpos(ypos + 35);
	missile->push_back(m2);

	m3 = new Missile(2, 2);
	m3->SetWidth(Missile::MISSILE_SIZE);
	m3->SetHeight(Missile::MISSILE_SIZE);
	m3->SetXpos(xpos);
	m3->SetYpos(ypos - Missile::MISSILE_SIZE);
	missile->push_back(m3);
}