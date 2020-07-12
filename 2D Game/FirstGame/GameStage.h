#pragma once

#include "SDL_image.h"
#include <list>
#include "SDL_ttf.h"
#include "Creature.h"
#include "Missile.h"
#include "Monster.h"
#include "Hero.h"
#include "SDL_mixer.h"
#include "Item.h"

class Stage {
protected:
	int xpos;
	Mix_Music *bgm;
	TTF_Font *gameFont;
	Mix_Chunk *buttonSound;

public:
	
	virtual void HandleEvents() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void DrawBackGround() = 0;
};

class GameStage : public Stage {
protected:
	Hero *hero;
	std::list<Monster*> monster;
	std::list<Missile*> missile;
	std::list<Item*> item;
	Mix_Chunk* getSound;
	int xpos;
	int killCount;
	int clearTime;
	int bg_width;

public:
	GameStage();
	~GameStage();


	virtual void NextStage() = 0;
	virtual void SettingMonster() = 0;
	virtual void SettingItem() = 0;

	Creature* GetHero();
	void SetHero(Hero* h);
	int GetClearTime();
	void SetClearTime(int c);
	int GetKillCount();
	void SetKillCount(int c);

	void HandleEvents();
	void Render();
	void Update();
	void DrawBackGround();
	void DrawScoreA();
	void DrawHeader();
	int TotalScore();
	virtual bool isClear() = 0;

	void Scroll(int dir);
};