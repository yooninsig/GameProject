#pragma once
#include "GameStage.h"
#include "SDL_ttf.h"

class EndingStage : public Stage
{
protected:
	//0 : 클리어, 1 : 게임오버, 3 : 점수 확인 화면.
	int ending;
	int end_buff;
	int myScore;
public:
	EndingStage();
	EndingStage(int ending, int score);
	~EndingStage();

	void Render();
	void HandleEvents();
	void Update();
	void DrawBackGround();
};
