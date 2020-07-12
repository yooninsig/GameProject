#include "Item.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include <string>

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;

Item::Item(int item_type, int x, int y) {
	xpos = x;
	ypos = y;
	type = item_type;
	width = Item::ITEM_SIZE;
	height = Item::ITEM_SIZE;
}

Item::~Item() {

}

//1 : 미콘, 2 : 수학, 3 : 컴공, 4 : 화학, 5 : aPlus
void Item::SetType(int t) {
	type = t;
}

int Item::GetType() {
	return type;
}

void Item::Draw() {
	TextureManager* tm = tm->GetSingleton();
	std::string spriteId;

	switch (type) {
	case 1:
		spriteId = "item_media0";
		break;

	case 2:
		spriteId = "item_math0";
		break;

	case 3:
		spriteId = "item_comp0";
		break;

	case 4:
		spriteId = "item_chemi0";
		break;

	case 5:
		spriteId = "item_aplus0";
		break;

	default: return;
	}


	tm->DrawSprite("item", spriteId, xpos, ypos, Item::ITEM_SIZE, Item::ITEM_SIZE);
}

void Item::Effect(Hero* hero) {
	switch (type) {
	case 1:
		hero->SetHealth(hero->GetHealth() + 1);
		return;

	case 2:
		//수학
		hero->SetItemType(1);
		hero->SetAttackPower(2);
		return;

	case 3:
		//컴공
		hero->SetItemType(2);
		hero->SetAttackPower(1);
		return;

	case 4:
		hero->SetInvinceTime(-8200);
		return;

	case 5:
		hero->SetAplus(hero->GetAplus() + 1);
		break;

	default:
		return;
	}
}