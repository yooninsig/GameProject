#pragma once
#include "GameStage.h"
#include "SDL_ttf.h"

class EndingStage : public Stage
{
protected:
	//0 : Ŭ����, 1 : ���ӿ���, 3 : ���� Ȯ�� ȭ��.
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
