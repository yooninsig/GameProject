#include <iostream>
#include "SDL_image.h"
#include "Creature.h"
#include "GameFunc.h"
#include "Missile.h"

GameObject::GameObject(){

}
GameObject::~GameObject() {

}

int GameObject::GetXpos() {
	return xpos;
}

void GameObject::SetXpos(int x) {
	xpos = x;
}
int GameObject::GetYpos() {
	return ypos;
}
void GameObject::SetYpos(int y) {
	ypos = y;
}

int GameObject::GetWidth() {
	return width;
}
void GameObject::SetWidth(int w) {
	width = w;
}

int GameObject::GetHeight() {
	return height;
}
void GameObject::SetHeight(int h) {
	height = h;
}


Creature::Creature() {
}
Creature::~Creature() {

}
void Creature::SetStatus(int st) {
	status = st;
}	
//0 : ���� ����, 1 : ������ ����, 2 : ���� �̵�, 3 : ������ �̵�, 4 : ���� ����, 5 : ���� ��� ����, 6 : ���� �ϴ� ����.
int Creature::GetStatus() {
	return status;
}
std::string  Creature::GetSpriteId() {
	return spriteId;
}
void Creature::SetSpriteId(std::string id) {
	spriteId = id;
}
int Creature::GetAttackPower() {
	return attackPower;
}
void Creature::SetAttackPower(int power) {
	attackPower = power;
}
int Creature::GetInvinceTime() {
	return invince_time_ms;
}
void Creature::SetInvinceTime(int frame) {
	invince_time_ms = frame;
}
int Creature::GetHealth() {
	return health;
}
void Creature::SetHealth(int hp) {
	health = hp;
}
int Creature::GetFrameTime() {
	return frame_time_ms;
}
void Creature::SetFrameTime(int time) {
	frame_time_ms = time;
}

bool Creature::isIn(int x, int y, int w, int h) {
	bool is_in_width = false;
	bool is_in_height = false;

	if (width >= w) {
		is_in_width = ((x >= xpos && x <= xpos + width) || (x + w) >= xpos && (x + w) <= (xpos + width));
	}
	else if(width < w) {
		is_in_width = ((xpos >= x && xpos <= x + w) || (xpos + width) >= x && (xpos + width) <= (x + w));
	}

	if (height >= h) {
		is_in_height = ((y >= ypos && y <= ypos + height) || (y + h) >= ypos && (y + h) <= (ypos + height));
	}
	else if(height < h){
		is_in_height = ((ypos >= y && ypos <= y + h) || (ypos + height) >= y && (ypos + height) <= (y + h));
	}

	return is_in_width && is_in_height;
}

bool Creature::isDead() {
	return health <= 0;
}