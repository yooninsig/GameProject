#pragma once
#include "GameStage.h"

class IntroStage : public Stage
{
protected:
	// 0 : ��Ʈ��, 1 : ���ӼҰ�1, 2 : ���ӼҰ�2
	int phase;

public:
	IntroStage();
	~IntroStage();

	void Render();
	void HandleEvents();
	void Update();
	void DrawBackGround();
};