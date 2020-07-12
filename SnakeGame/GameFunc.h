#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
typedef struct Data { 
	int X;
	int Y;
}Data;
typedef struct Node {
	Data data;
	Node* next;
	Node* prev;
}Node;


class Stage
{
public:
	Stage();
	~Stage();
	void SnakeInit();
	void CrushWall();
	Node* AddHead();
	void DeleteTail(); //그리고 지우고 그리고 지우는 것을 구현하기 위해
	void HitSnake();
	void ItemPos();
	void EatItem();

	void HandleEvents();
	void Update();
	void Render();

private:
	bool started_;
	int direction_;
	int pos_x;
	int pos_y;
	int pixel_size_;
	int Item_;
	int cnt;

	Node* snake;
	Node* head;
	Node* tail;
	SDL_Texture * item_texture_;
	SDL_Rect item_source_rectangle_;
	SDL_Rect item_destination_rectangle_;

	SDL_Texture* head_texture_;
	SDL_Rect head_source_rectangle_;
	SDL_Rect head_destination_rectangle_;

	SDL_Texture* tail_texture_;
	SDL_Rect tail_source_rectangle_;
	SDL_Rect tail_destination_rectangle_;

	SDL_Texture* bg_texture_;
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;

};
