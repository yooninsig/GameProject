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
	//���ΰ� -> 0 : ���� ����, 1 : ������ ����, 2 : ���� �̵�, 3 : ������ �̵�, 4 : �������� �ƾ�, 5 : ���������� �ƾ�, 6 : ���� ���� ��� ����, 7 : ������ ���� ���
	//8 : ���� ���ݻ���, 9 : ������ ���� ����
	int status;
	int health;
	int attackPower;

	//���� ������ Ÿ��.
	int invince_time_ms;

	//ĳ���͵� ������ Ÿ��
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