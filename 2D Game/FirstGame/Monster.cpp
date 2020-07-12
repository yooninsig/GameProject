#include "Monster.h"
#include "SDL_mixer.h"



Monster::Monster() {

}


Monster::~Monster() {

}

void Monster::Move_Xpos(){
	if (status == 2) {
		//¿ÞÂÊ
		xpos -= 3;
		len -= 5;
		if (len <= 0) {
			len = rand() % 50 + 200;
			SetStatus(3);
		}
	}

	else if (status == 3) {
		//¿À¸¥ÂÊ
		xpos += 3;
		len -= 5;
		if (len <= 0) {
			len = rand() % 50 + 200;
			SetStatus(2);
		}
	}
}
void Monster::Attack(Hero* hero){
	frame_time_ms = 0;
	Mix_PlayChannel(-1, attackSound, 0);
	if (hero->GetXpos() >= xpos) {
		status = 9;
	}
	else {
		status = 8;
	}
}

bool Monster::isDistance(Hero* hero){
	if (hero->GetXpos() - xpos < 550 && hero->GetXpos() - xpos > - 550)
		return true;

	return false;
}

bool Monster::AttackableStatus() {
	return (status != 8 || status != 9) && frame_time_ms > 2500;
}

void Monster::Attacked(Creature* c) {
	invince_time_ms = 0;
	frame_time_ms = 0;
	if ((xpos + width) / 2 < (c->GetXpos() + c->GetWidth()) / 2) {
		xpos -= 80;
		status = 1;
	}

	else {
		xpos += 80;
		status = 2;
	}

	health -= c->GetAttackPower();

}