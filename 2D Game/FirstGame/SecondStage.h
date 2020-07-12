#pragma once
#include "GameStage.h"

class SecondStage : public GameStage
{
public:
	SecondStage();
	~SecondStage();

	void NextStage();
	bool isClear();
	void SettingItem();
	void SettingMonster();
};

