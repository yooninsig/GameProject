#include "FirstStage.h"
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
#include "SecondStage.h"
#include "GameFunc.h"
#include "SDL_mixer.h"
#include "Item.h"

extern Stage *stage;
extern SDL_Renderer *g_renderer;
extern int ground_height;

FirstStage::FirstStage() {
	bg_width = 3920;
	//폰트 적용.
	//gameFont = TTF_OpenFont("../Resources/HangeulNuriB.ttf", 100);

	//텍스쳐 매니저
	TextureManager* tm = TextureManager::GetSingleton();
	bgm = Mix_LoadMUS("../music/first_stage.mp3");
	Mix_PlayMusic(bgm, -1);

	//텍스쳐
	tm->LoadTexture("bg", "../Resources/bg_out_image.png");
	tm->LoadTexture("hero", "../Resources/hero_image.png", 255, 255, 255);
	tm->LoadTexture("bird", "../Resources/bird_image.png", 255, 255, 255);
	tm->LoadTexture("item", "../Resources/item_image.png", 255, 255, 255);
	tm->LoadTexture("liter", "../Resources/liter_std_image.png", 255, 255, 255);

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

	//까마귀 spriterect
	{
		tm->AddSpriteRect("bird_stop0", 0, 0, 95, 100);
		tm->AddSpriteRect("bird_attack0", 95, 0, 105, 100);
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

	//문과생 spriterect
	{
		tm->AddSpriteRect("liter_move0", 0, 0, 100, 120);
		tm->AddSpriteRect("liter_move1", 200, 0, 100, 120);
		tm->AddSpriteRect("liter_stop0", 100, 0, 100, 120);
		tm->AddSpriteRect("liter_attack0", 300, 0, 100, 120);
	}

	//주인공 생성.
	hero = new Hero();

	//몬스터 생성.
	SettingMonster();

	//아이템 생성
	SettingItem();

	clearTime = 0;
	killCount = 0;
}


FirstStage::~FirstStage() {
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
	if (bgm)
		Mix_FreeMusic(bgm);
}

void FirstStage::NextStage() {
	stage = new SecondStage();
	GameStage* s = dynamic_cast<GameStage*> (stage);
	hero->SetXpos(30);
	s->SetClearTime(clearTime);
	s->SetKillCount(killCount);
	s->SetHero(hero);
}

bool FirstStage::isClear() {
	return xpos == bg_width - 640 && hero->GetXpos() >= 1000;

}

void FirstStage::SettingItem() {
	//1 : 미콘, 2 : 수학, 3 : 컴공, 4 : 화학, 5 : aPlus
	item.push_back(new Item(5, 105, 344));
	item.push_back(new Item(5, 255, 344));
	item.push_back(new Item(5, 405, 344));
	item.push_back(new Item(5, 565, 344));
	item.push_back(new Item(5, 715, 344));
	item.push_back(new Item(5, 865, 344));

	item.push_back(new Item(5, 1442, 344));
	item.push_back(new Item(5, 1592, 344));
	item.push_back(new Item(5, 1742, 344));

	item.push_back(new Item(5, 2540, 344));
	item.push_back(new Item(5, 2690, 344));
	item.push_back(new Item(5, 2840, 344));

	item.push_back(new Item(5, 3340, 344));
	item.push_back(new Item(5, 3490, 344));
	item.push_back(new Item(2, 3640, 344));
	item.push_back(new Item(5, 3790, 344));
	item.push_back(new Item(5, 3940, 344));

	item.push_back(new Item(5, 4740, 344));
	item.push_back(new Item(5, 4890, 344));
	item.push_back(new Item(5, 5040, 344));

	item.push_back(new Item(1, 5540, 344));

	item.push_back(new Item(5, 6340, 344));
	item.push_back(new Item(5, 6490, 344));
	item.push_back(new Item(5, 6640, 344));
	item.push_back(new Item(5, 6790, 344));
	item.push_back(new Item(5, 6940, 344));
}

void FirstStage::SettingMonster() {
	monster.push_back(new LiterMonster(1000));
	monster.push_back(new LiterMonster(2000));
	monster.push_back(new LiterMonster(2800));
	monster.push_back(new LiterMonster(3800));
	monster.push_back(new LiterMonster(4500));
	monster.push_back(new LiterMonster(5200));
	monster.push_back(new LiterMonster(5700));
	monster.push_back(new LiterMonster(6700));
}