#pragma once
#include "Missile.h"
#include "TextureManager.h"

Missile::Missile(int missile_type, int missile_dir) {
	type = missile_type;
	dir = missile_dir;
	damage = 1;
	(missile_type == 3)? len = 500 : len = 250;
}

Missile::~Missile() {

}

int Missile::GetType() {
	return type;
}

void Missile::SetType(int t) {
	type = t;
}

int Missile::GetDir() {
	return dir;
}

void Missile::SetDir(int d) {
	dir = d;
}

int Missile::GetDamage() {
	return damage;
}

void Missile::SetDamage(int d) {
	damage = d;
}

int Missile::GetLen() {
	return len;
}

void Missile::SetLen(int l) {
	len = l;
}


void Missile::Draw() {
	TextureManager* tm = TextureManager::GetSingleton();
	
	if (type == 0) {
		tm->DrawSprite("item", "missile_poop0", xpos, ypos, 50, 50);
	}
	else if (type == 1) {
		tm->DrawSprite("item", "missile_hi0", xpos, ypos, 50, 50);
	}

	else if (type == 2) {
		tm->DrawSprite("item", "missile_donkey0", xpos, ypos, 50, 50);
	}

	else if (type == 3) {
		tm->DrawSprite("item", "missile_cplus0", xpos, ypos, 50, 50);
	}
	return;
}

void Missile::Move() {
	if (dir == 0) {
		xpos -= 8;
	}

	else if (dir == 1) {
		xpos += 8;
	}

	else if (dir == 2) {
		ypos -= 8;
	}

	else if (dir == 3) {
		ypos += 8;
	}

	len -= 5;
	return;
}
