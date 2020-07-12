#include "SDL_image.h"
#include "Hero.h"
#include <stdlib.h>
#include "TextureManager.h"
#include "GameStage.h"
#include "GameFunc.h"
#include "Missile.h"
#include "SDL_mixer.h"

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;
extern int ground_height;
extern int g_window_width;

Hero::Hero() {
	invince_time_ms = 0;
	frame_time_ms = 0;
	yvel = 0;
	status = 1;
	xpos = 30;
	ypos = ground_height - Monster::NormalCreatureHeight;
	width = Monster::NormalCreatureWidth;
	height = Monster::NormalCreatureHeight;
	attackPower = 1;
	health = 5;
	itemType = 0;
	aPlus = 0;

	attackedSound = Mix_LoadWAV("../music/attacked.wav");
	if (attackedSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}
	basicSound = Mix_LoadWAV("../music/basicAttack.wav");
	if (basicSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}
	mathSound = Mix_LoadWAV("../music/mathAttack.wav");
	if (mathSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}
	comSound = Mix_LoadWAV("../music/comAttack.wav");
	if (comSound == NULL) {
		printf("Couldn't open %s \n", Mix_GetError());
	}
}

Hero::~Hero() {
	
}

void Hero::SetYvel(int y) {
	yvel = y;
}

int Hero::GetYvel() {
	return yvel;
}

int Hero::GetItemType() {
	return itemType;
}

void Hero::SetItemType(int t) {
	itemType = t;
}

int Hero::GetAplus() {
	return aPlus;
}
void Hero::SetAplus(int a) {
	aPlus = a;
}


void Hero::Draw() {
	int spriteIndex;

	TextureManager* tm = TextureManager::GetSingleton();

	//공격 받은 상태.
	if (status == 4 || status == 5) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "hero_attacked" + std::to_string((long long)spriteIndex);
	}

	//공격 대기 상태.
	else if (status == 6 || status == 7) {
		spriteIndex = (frame_time_ms / 30) % 1;

		if (itemType == 0) {
			spriteId = "hero_attack" + std::to_string((long long)spriteIndex);
		}

		else if (itemType == 1) {
			spriteId = "hero_ruler_attack" + std::to_string((long long)spriteIndex);
		}

		else if (itemType == 2) {
			spriteId = "hero_mouse_attack" + std::to_string((long long)spriteIndex);
		}
	}

	//공격 중인 상태.
	else if (status == 8 || status == 9) {
		spriteIndex = (frame_time_ms / 30) % 1 + 1;

		if (itemType == 0) {
			spriteId = "hero_attack" + std::to_string((long long)spriteIndex);
		}
		else if (itemType == 1) {
			spriteId = "hero_ruler_attack" + std::to_string((long long)spriteIndex);
		}
		else if (itemType == 2) {
			spriteId = "hero_mouse_attack" + std::to_string((long long)spriteIndex);
		}
	}

	//점프 중
	else if (yvel > 0) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "hero_jump" + std::to_string((long long)spriteIndex);
	}

	//하강 중
	else if (yvel < 0) {
		spriteIndex = (frame_time_ms / 30) % 1;
		spriteId = "hero_drop" + std::to_string((long long)spriteIndex);
	}

	//정지 상태
	else if (status == 0 || status == 1) {
		spriteIndex = (frame_time_ms / 30) % 1;

		if (itemType == 0) {
			spriteId = "hero_move" + std::to_string((long long)spriteIndex);
		}
		else if (itemType == 1) {
			spriteId = "hero_ruler_stop" + std::to_string((long long)spriteIndex);
		}
		else if (itemType == 2) {
			spriteId = "hero_mouse_stop" + std::to_string((long long)spriteIndex);
		}
	}

	//무빙 중
	else if(status == 2 || status == 3) {
		spriteIndex = (frame_time_ms / 240) % 4;
		spriteId = "hero_move" + std::to_string((long long)spriteIndex);
	}

	if (status == 6) {
		if (itemType == 2) {
			tm->DrawSpriteRef("hero", spriteId, xpos, ypos, width + 85, height);
		}
		else {
			tm->DrawSpriteRef("hero", spriteId, xpos, ypos, width + 40, height);
		}
	}

	else if (status == 7) {
		if (itemType == 2) {
			tm->DrawSprite("hero", spriteId, xpos - 85, ypos, width + 85, height);
		}
		else {
			tm->DrawSprite("hero", spriteId, xpos - 40, ypos, width + 40, height);
		}
	}

	else if (status == 8) {
		if (itemType == 2) {
			tm->DrawSpriteRef("hero", spriteId, xpos - 90, ypos, width + 90, height);
		}
		else {
			tm->DrawSpriteRef("hero", spriteId, xpos - 40, ypos, width + 40, height);
		}
	}

	else if (status == 9) {
		if (itemType == 2) {
			tm->DrawSprite("hero", spriteId, xpos, ypos, width + 90, height);
		}
		else {
			tm->DrawSprite("hero", spriteId, xpos, ypos, width + 40, height);
		}
	}

	else if (status % 2 == 0) {
		tm->DrawSpriteRef("hero", spriteId, xpos, ypos, width, height);
	}

	else {
		tm->DrawSprite("hero", spriteId, xpos, ypos, width, height);
	}

}

void Hero::Attacked(Creature* c) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	Mix_PlayChannel(-1, attackedSound, 0);
	if ((xpos + width) / 2 < (c->GetXpos() + c->GetWidth()) / 2) {
		xpos -= 90;
		status = 5;
	}

	else {
		xpos += 90;
		status = 4;
	}

	health -= c->GetAttackPower();
	itemType = 0;
	attackPower = 1;

}

void Hero::Attacked(Missile* m) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	Mix_PlayChannel(-1, attackedSound, 0);
	if ((xpos + width) / 2 < (m->GetXpos() + m->GetWidth()) / 2) {
		xpos -= 90;
		status = 5;
	}

	else {
		xpos += 90;
		status = 4;
	}

	health -= 1;
	itemType = 0;
	attackPower = 1;

}

void Hero::Move_Xpos() {
	if (status == 2) {
		//왼쪽
		if (xpos > 0) {
			xpos -= 6;
		}
	}

	else if (status == 3) {
		//오른쪽
		if (xpos < g_window_width - width) {
			xpos += 6;
		}
	}
}

void Hero::Move_Ypos() {
	if (yvel != 0) {
		ypos -= yvel;
		yvel -= 4;
	}
}

void Hero::Jump() {
	frame_time_ms = 0;
	yvel = 39;
}

bool Hero::isMoveable() {
	return !(status == 4 || status == 5);
}

void Hero::FrameControl() {
	//공격 맞은 상태에서 해제
	if (status == 4) {
		if (frame_time_ms >= 300) {
			status = 0;
			frame_time_ms = 0;
		}
	}

	else if (status == 5) {
		if (frame_time_ms >= 300) {
			status = 1;
			frame_time_ms = 0;
		}
	}

	else if (status == 6) {
		if (frame_time_ms >= 300) {
			status = 8;
			frame_time_ms = 0;
		}
	}

	else if (status == 7) {
		if (frame_time_ms >= 300) {
			status = 9;
			frame_time_ms = 0;
		}
	}

	else if (status == 8) {
		if (frame_time_ms >= 300) {
			status = 0;
			frame_time_ms = 0;
		}
	}

	else if (status == 9) {
		if (frame_time_ms >= 300) {
			status = 1;
			frame_time_ms = 0;
		}
	}

	frame_time_ms += 30;
}

void Hero::Attack() {
	frame_time_ms = 0;
	if (itemType == 0) {
		Mix_PlayChannel(-1, basicSound, 0);
	}
	else if (itemType == 1) {
		Mix_PlayChannel(-1, mathSound, 0);
	}
	else if (itemType == 2) {
		Mix_PlayChannel(-1, comSound, 0);
	}

	if (status % 2 == 0) {
		status = 6;
	}
	else {
		status = 7;
	}
}
