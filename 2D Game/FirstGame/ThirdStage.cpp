#include "ThirdStage.h"
#include "GameStage.h"
#include "Hero.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include <atlstr.h>
#include <string>
#include "Creature.h"
#include "SDL_main.h"
#include <list>
#include "EndingStage.h"
#include "GameFunc.h"
#include "ProfMonster.h"
#include "SDL_mixer.h"

extern Stage *stage;
extern int max_score;


ThirdStage::ThirdStage() {
	bg_width = 1600;
	//폰트 적용.
	gameFont = TTF_OpenFont("../Resources/HangeulNuriB.ttf", 100);

	//텍스쳐 매니저
	TextureManager* tm = TextureManager::GetSingleton();

	//텍스쳐
	tm->LoadTexture("bg", "../Resources/bg_in_image.png");
	tm->LoadTexture("hero", "../Resources/hero_image.png", 255, 255, 255);
	tm->LoadTexture("bird", "../Resources/bird_image.png", 255, 255, 255);
	tm->LoadTexture("item", "../Resources/item_image.png", 255, 255, 255);
	tm->LoadTexture("prof", "../Resources/prof_image.png", 255, 255, 255);

	//히어로 spriterect
	{
		tm->AddSpriteRect("hero_move1", 0, 0, 100, 120);
		tm->AddSpriteRect("hero_move3", 200, 0, 100, 120);
		tm->AddSpriteRect("hero_attack0", 0, 120, 150, 120);
		tm->AddSpriteRect("hero_attack1", 150, 120, 163, 120);
		tm->AddSpriteRect("hero_move0", 100, 0, 100, 120);
		tm->AddSpriteRect("hero_move2", 100, 0, 100, 120);
		tm->AddSpriteRect("hero_jump0", 300, 0, 100, 120);
		tm->AddSpriteRect("hero_drop0", 400, 0, 100, 120);
		tm->AddSpriteRect("hero_attacked0", 315, 120, 100, 120);
		tm->AddSpriteRect("hero_ruler_attack0", 0, 360, 145, 120);
		tm->AddSpriteRect("hero_ruler_attack1", 145, 360, 155, 120);
		tm->AddSpriteRect("hero_mouse_attack0", 0, 240, 188, 120);
		tm->AddSpriteRect("hero_mouse_attack1", 190, 240, 200, 120);
		tm->AddSpriteRect("hero_ruler_stop0", 300, 360, 100, 120);
		tm->AddSpriteRect("hero_mouse_stop0", 390, 240, 100, 120);
	}

	//아이템 spriterect
	{
		tm->AddSpriteRect("item_heart0", 0, 0, 100, 100);
		tm->AddSpriteRect("item_aplus0", 100, 0, 100, 100);
		tm->AddSpriteRect("item_face0", 200, 0, 100, 100);
		tm->AddSpriteRect("item_media0", 0, 100, 100, 100);
		tm->AddSpriteRect("item_math0", 100, 100, 100, 100);
		tm->AddSpriteRect("item_comp0", 200, 100, 100, 100);
		tm->AddSpriteRect("item_chemi0", 300, 100, 100, 100);
		tm->AddSpriteRect("item_bomb0", 0, 200, 100, 100);
		tm->AddSpriteRect("missile_poop0", 100, 200, 100, 100);
		tm->AddSpriteRect("missile_hi0", 200, 200, 100, 100);
		tm->AddSpriteRect("missile_donkey0", 300, 200, 100, 100);
		tm->AddSpriteRect("missile_cplus0", 400, 200, 100, 100);
	}

	//교수님 spriterect
	{
		tm->AddSpriteRect("prof_move0", 0, 0, 100, 120);
		tm->AddSpriteRect("prof_move1", 200, 0, 100, 120);
		tm->AddSpriteRect("prof_stop0", 100, 0, 100, 120);
		tm->AddSpriteRect("prof_attack0", 300, 0, 100, 120);
	}

	//까마귀 spriterect
	{
		tm->AddSpriteRect("bird_stop0", 0, 0, 95, 100);
		tm->AddSpriteRect("bird_attack0", 95, 0, 105, 100);
	}

	//주인공 생성.
	hero = new Hero();

	//몬스터 생성.
	SettingMonster();

	//아이템 생성
	SettingItem();

	//변수들 초기화
	xpos = 0;
	bgm = Mix_LoadMUS("../music/boss_stage.mp3");
	Mix_PlayMusic(bgm, -1);

}


ThirdStage::~ThirdStage() {
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
	if (bgm)
		Mix_FreeMusic(bgm);

}

void ThirdStage::NextStage() {
	stage = new EndingStage(0, (TotalScore() >= 0)? TotalScore() : 0);
}

bool ThirdStage::isClear() {
	return monster.empty();
}

void ThirdStage::SettingItem() {
	//1 : 미콘, 2 : 수학, 3 : 컴공, 4 : 화학, 5 : aPlus
	item.push_back(new Item(4, 1000, 340));
	item.push_back(new Item(1, 1500, 340));
}

void ThirdStage::SettingMonster() {
	monster.push_back(new ProfMonster(1600));
}