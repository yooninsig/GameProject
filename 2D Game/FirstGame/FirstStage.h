#pragma once
#include "GameStage.h"

class FirstStage : public GameStage
{
public:
	FirstStage();
	~FirstStage();

	void NextStage();
	bool isClear();
	void SettingItem();
	void SettingMonster();
};

