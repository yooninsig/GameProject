#pragma once
#include "GameStage.h"

class ThirdStage : public GameStage
{
public:
	ThirdStage();
	~ThirdStage();

	void NextStage();
	bool isClear();
	void SettingItem();
	void SettingMonster();
};

