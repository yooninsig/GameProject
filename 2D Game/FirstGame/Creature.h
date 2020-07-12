#pragma once

#include <iostream>
#include "SDL_image.h"
#include <string>

class GameObject
{
protected:
	int xpos;
	int ypos;
	int width;
	int height;

public:
	GameObject();
	~GameObject();

	int GetXpos();
	void SetXpos(int x);
	int GetYpos();
	void SetYpos(int y);
	int GetWidth();
	void SetWidth(int w);
	int GetHeight();
	void SetHeight(int h);

};

class Creature :public GameObject{

protected:
	//주인공 -> 0 : 왼쪽 정지, 1 : 오른쪽 정지, 2 : 왼쪽 이동, 3 : 오른쪽 이동, 4 : 왼쪽으로 아야, 5 : 오른쪽으로 아야, 6 : 왼쪽 공격 대기 상태, 7 : 오른쪽 공격 대기
	//8 : 왼쪽 공격상태, 9 : 오른쪽 공격 상태
	int status;
	int health;
	int attackPower;

	//무적 프레임 타임.
	int invince_time_ms;

	//캐릭터들 프레임 타임
	int frame_time_ms;
	std::string spriteId;

public:
	Creature();
	~Creature();

	int GetStatus();
	void SetStatus(int st);
	std::string GetSpriteId();
	void SetSpriteId(std::string id);
	int GetAttackPower();
	void SetAttackPower(int power);
	int GetInvinceTime();
	void SetInvinceTime(int frame);
	int GetFrameTime();
	void SetFrameTime(int time);
	int GetHealth();
	void SetHealth(int hp);

	virtual void Draw() = 0;
	virtual void Move_Xpos() = 0;

	bool isDead();
	virtual void Attacked(Creature* creature) = 0;
	bool isIn(int x, int y, int w, int h);
};