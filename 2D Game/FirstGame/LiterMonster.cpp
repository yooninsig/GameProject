#include "SDL_image.h"
#include "LiterMonster.h"
#include "TextureManager.h"
#include "GameFunc.h"
#include "MIssile.h"

extern SDL_Renderer *g_renderer;
extern int ground_height;
extern int g_window_width;

LiterMonster::LiterMonster() {
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 2;
	attackPower = 1;
	xpos = g_window_width / 10 * 5;
	ypos = ground_height - NormalCreatureHeight;
	width = Monster::NormalCreatureWidth;
	height = Monster::NormalCreatureHeight;
}

LiterMonster::LiterMonster(int x) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 2;
	attackPower = 1;
	ypos = ground_height - NormalCreatureHeight;
	width = Monster::NormalCreatureWidth;
	height = Monster::NormalCreatureHeight;

	attackSound = Mix_LoadWAV("../music/litAttack.wav");
	if (attackSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}

	xpos = x;
}

LiterMonster::~LiterMonster() {
	
}

void LiterMonster::Draw() {
	int spriteIndex = 0;
	TextureManager* tm = TextureManager::GetSingleton();

	if (status == 8 || status == 9) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "liter_attack" + std::to_string((long long)spriteIndex);
	}

	else if (status == 2 || status == 3) {
		spriteIndex = (frame_time_ms / 480) % 2;
		spriteId = "liter_move" + std::to_string((long long)spriteIndex);
	}

	else if (status == 0 || status == 1) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "liter_stop" + std::to_string((long long)spriteIndex);
	}

	if (status % 2 == 0) {
		tm->DrawSpriteRef("liter", spriteId, xpos, ypos, width, height);
	}
	else {
		tm->DrawSprite("liter", spriteId, xpos, ypos, width, height);
	}
}

void LiterMonster::FrameControl() {
	if (status == 8 || status == 9) {
		if (frame_time_ms >= 2000) {
			(status == 8) ? status = 2 : status = 3;
			frame_time_ms = 0;
		}
	}

	frame_time_ms += 30;
}

void LiterMonster::throwMissile(std::list<Missile*>* missile) {
	Missile* m;
	if (status == 8) {
		m = new Missile(1, 0);
		m->SetWidth(Missile::MISSILE_SIZE);
		m->SetHeight(Missile::MISSILE_SIZE);
		m->SetXpos(xpos - Missile::MISSILE_SIZE);
		m->SetYpos(ypos + 35);

	}
	else {
		m = new Missile(1, 1);
		m->SetWidth(Missile::MISSILE_SIZE);
		m->SetHeight(Missile::MISSILE_SIZE);
		m->SetXpos(xpos + Monster::NormalCreatureWidth);
		m->SetYpos(ypos + 35);
	}
	missile->push_back(m);
}