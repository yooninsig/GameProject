#include "SecondStage.h"
#include "GameStage.h"
#include "Hero.h"
#include "LiterMonster.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include <atlstr.h>
#include <string>
#include "Creature.h"
#include "SDL_main.h"
#include <list>
#include "ThirdStage.h"
#include "GameFunc.h"
#include "OldMonster.h"
#include "SDL_mixer.h"

extern Stage *stage;


SecondStage::SecondStage() {
	bg_width = 4800;
	//폰트 적용.
	gameFont = TTF_OpenFont("../Resources/HangeulNuriB.ttf", 100);

	//텍스쳐 매니저
	TextureManager* tm = TextureManager::GetSingleton();

	//텍스쳐
	tm->LoadTexture("bg", "../Resources/bg_dasol_image.png");
	tm->LoadTexture("hero", "../Resources/hero_image.png", 255, 255, 255);
	tm->LoadTexture("bird", "../Resources/bird_image.png", 255, 255, 255);
	tm->LoadTexture("item", "../Resources/item_image.png", 255, 255, 255);
	tm->LoadTexture("old", "../Resources/old_std_image.png", 255, 255, 255);

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

	//복학생 spriterect
	{
		tm->AddSpriteRect("old_move0", 0, 0, 100, 120);
		tm->AddSpriteRect("old_move1", 200, 0, 100, 120);
		tm->AddSpriteRect("old_stop0", 100, 0, 100, 120);
		tm->AddSpriteRect("old_attack0", 300, 0, 100, 120);
	}

	//까마귀 spriterect
	{
		tm->AddSpriteRect("bird_stop0", 0, 0, 95, 100);
		tm->AddSpriteRect("bird_attack0", 95, 0, 105, 100);
	}

	//몬스터 생성.
	SettingMonster();

	//아이템 생성
	SettingItem();

	//변수들 초기화
	xpos = 0;

	bgm = Mix_LoadMUS("../music/second_stage.mp3");
	Mix_PlayMusic(bgm, -1);

}


SecondStage::~SecondStage() {
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
	if (bgm)
		Mix_FreeMusic(bgm);

}

void SecondStage::NextStage() {
	stage = new ThirdStage();
	GameStage* s = dynamic_cast<GameStage*> (stage);
	hero->SetXpos(30);
	s->SetClearTime(clearTime);
	s->SetKillCount(killCount);
	s->SetHero(hero);
}

bool SecondStage::isClear() {
	return xpos == bg_width - 640 && hero->GetXpos() >= 800;
}

void SecondStage::SettingItem() {
	//1 : 미콘, 2 : 수학, 3 : 컴공, 4 : 화학, 5 : aPlus
	item.push_back(new Item(5, 100, 340));
	item.push_back(new Item(5, 250, 350));
	item.push_back(new Item(5, 400, 350));

	item.push_back(new Item(3, 900, 350));

	item.push_back(new Item(5, 1400, 350));
	item.push_back(new Item(5, 1550, 350));
	item.push_back(new Item(5, 1700, 350));
	item.push_back(new Item(5, 1850, 350));
	item.push_back(new Item(5, 2000, 350));

	item.push_back(new Item(2, 2500, 350));
	item.push_back(new Item(5, 2650, 350));
	item.push_back(new Item(5, 2800, 350));
	item.push_back(new Item(5, 2950, 350));
	item.push_back(new Item(1, 3100, 350));

	item.push_back(new Item(5, 4100, 350));
	item.push_back(new Item(5, 4250, 350));
	item.push_back(new Item(5, 4400, 350));
	item.push_back(new Item(5, 4550, 350));
	item.push_back(new Item(5, 4700, 350));

	item.push_back(new Item(5, 5200, 350));
	item.push_back(new Item(5, 5350, 350));
	item.push_back(new Item(5, 5500, 350));
	item.push_back(new Item(1, 5650, 350));

	item.push_back(new Item(5, 6150, 350));
	item.push_back(new Item(5, 6300, 350));
	item.push_back(new Item(5, 6450, 350));

	item.push_back(new Item(5, 6950, 350));
	item.push_back(new Item(5, 7100, 350));
	item.push_back(new Item(5, 7250, 350));
	item.push_back(new Item(5, 7400, 350));
	item.push_back(new Item(5, 7550, 350));

	item.push_back(new Item(5, 8550, 350));
	item.push_back(new Item(5, 8700, 350));
	item.push_back(new Item(5, 8850, 350));
}

void SecondStage::SettingMonster() {
	monster.push_back(new OldMonster(1000));
	monster.push_back(new OldMonster(2000));
	monster.push_back(new OldMonster(3000));
	monster.push_back(new OldMonster(3700));
	monster.push_back(new OldMonster(4200));
	monster.push_back(new OldMonster(5200));
	monster.push_back(new OldMonster(6200));
	monster.push_back(new OldMonster(6900));
	monster.push_back(new OldMonster(7900));
	monster.push_back(new OldMonster(8900));
}