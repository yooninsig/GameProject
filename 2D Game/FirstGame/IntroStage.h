#pragma once
#include "GameStage.h"

class IntroStage : public Stage
{
protected:
	// 0 : 인트로, 1 : 게임소개1, 2 : 게임소개2
	int phase;

public:
	IntroStage();
	~IntroStage();

	void Render();
	void HandleEvents();
	void Update();
	void DrawBackGround();
};