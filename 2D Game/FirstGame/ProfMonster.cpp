#include "ProfMonster.h"
#include "SDL_image.h"
#include "TextureManager.h"

extern SDL_Renderer *g_renderer;
extern int ground_height;
extern int g_window_width;
extern int g_cur_time_ms;

ProfMonster::ProfMonster()
{
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 15;
	attackPower = 1;
	xpos = g_window_width / 10 * 5;
	ypos = ground_height - NormalCreatureHeight * 3;
	width = Monster::NormalCreatureWidth * 3;
	height = Monster::NormalCreatureHeight * 3;

}

ProfMonster::ProfMonster(int x) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	len = 300;
	status = 2;
	health = 15;
	attackPower = 1;
	xpos = g_window_width / 10 * 5;
	ypos = ground_height - NormalCreatureHeight * 3;
	width = Monster::NormalCreatureWidth * 3;
	height = Monster::NormalCreatureHeight * 3;

	attackSound = Mix_LoadWAV("../music/bossAttack.wav");
	if (attackSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}

	xpos = x;
}


ProfMonster::~ProfMonster()
{

}

void ProfMonster::Draw() {
	int spriteIndex = 0;
	TextureManager* tm = TextureManager::GetSingleton();

	if (status == 8 || status == 9) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "prof_attack" + std::to_string((long long)spriteIndex);
	}

	else if (status == 2 || status == 3) {
		spriteIndex = (frame_time_ms / 480) % 2;
		spriteId = "prof_move" + std::to_string((long long)spriteIndex);
	}

	else if (status == 0 || status == 1) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "prof_move" + std::to_string((long long)spriteIndex);
	}


	if (status % 2 == 0) {
		tm->DrawSpriteRef("prof", spriteId, xpos, ypos, width, height);
	}
	else {
		tm->DrawSprite("prof", spriteId, xpos, ypos, width, height);
	}
}

void ProfMonster::FrameControl() {
	if (status == 8 || status == 9) {
		if (frame_time_ms >= 2000) {
			(status == 8) ? status = 2 : status = 3;
			frame_time_ms = 0;
		}
	}

	frame_time_ms += 30;
}

void ProfMonster::throwMissile(std::list<Missile*>* missile) {
	/*Missile* m;
	if (status == 8) {
		m = new Missile(1, 0);
		m->SetWidth(Missile::MISSILE_SIZE);
		m->SetHeight(Missile::MISSILE_SIZE);
		m->SetXpos(xpos - Missile::MISSILE_SIZE);
		m->SetYpos(ypos + 35);

	}*/
	for (int i = 0; i < 12; i++) {
		Missile* m;
		m = new Missile(3, 3);
		m->SetWidth(Missile::MISSILE_SIZE);
		m->SetHeight(Missile::MISSILE_SIZE);
		m->SetXpos(rand() % 130 + i * 180 - 2 * 180);
		m->SetYpos(rand() % 250);
		missile->push_back(m);
	}
}

void ProfMonster::Attacked(Creature* m) {
	invince_time_ms = 0;
	if ((xpos + width) / 2 < (m->GetXpos() + m->GetWidth()) / 2) {
		xpos -= 80;
		status = 1;
		len = 200;
	}

	else {
		xpos += 80;
		status = 2;
		len = 200;
	}

	health -= m->GetAttackPower();

}