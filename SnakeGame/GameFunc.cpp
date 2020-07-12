#include "GameFunc.h"
#include "ClassPhase.h"
#include "SDL_image.h"
#include <iostream>
#include <time.h>
#include<SDL_mixer.h>
#include "SDL_ttf.h"



extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern Mix_Music *bgm;

Stage::Stage()
{
	Stage::SnakeInit();

	SDL_Surface* item_temp_surface = IMG_Load("../Resources/item.png");
	SDL_SetColorKey(item_temp_surface, 1, SDL_MapRGB(item_temp_surface->format, 255, 255, 255));

	item_texture_ = SDL_CreateTextureFromSurface(g_renderer, item_temp_surface);
	SDL_FreeSurface(item_temp_surface);

	SDL_QueryTexture(item_texture_, NULL, NULL, &item_source_rectangle_.w, &item_source_rectangle_.h);
	item_destination_rectangle_.x = item_source_rectangle_.x = 0;
	item_destination_rectangle_.y = item_source_rectangle_.y = 0;
	item_destination_rectangle_.w = item_source_rectangle_.w;
	item_destination_rectangle_.h = item_source_rectangle_.h;

	Item_ = 1;
	Stage::ItemPos();

	SDL_Surface* head_surface = IMG_Load("../Resources/head.png");
	SDL_SetColorKey(head_surface, 1, SDL_MapRGB(head_surface->format, 255, 255, 255));

	head_texture_ = SDL_CreateTextureFromSurface(g_renderer, head_surface);
	SDL_FreeSurface(head_surface);

	SDL_QueryTexture(head_texture_, NULL, NULL, &head_source_rectangle_.w, &head_source_rectangle_.h);
	head_destination_rectangle_.x = head_source_rectangle_.x = 0;
	head_destination_rectangle_.y = head_source_rectangle_.y = 0;
	head_destination_rectangle_.w = head_source_rectangle_.w;
	head_destination_rectangle_.h = head_source_rectangle_.h;

	SDL_Surface* tail_surface = IMG_Load("../Resources/tail.png");
	SDL_SetColorKey(tail_surface, 1, SDL_MapRGB(tail_surface->format, 255, 255, 255));
	tail_texture_ = SDL_CreateTextureFromSurface(g_renderer, tail_surface);
	SDL_FreeSurface(tail_surface);

	SDL_QueryTexture(tail_texture_, NULL, NULL, &tail_source_rectangle_.w, &tail_source_rectangle_.h);
	tail_destination_rectangle_.x = tail_source_rectangle_.x = 0;
	tail_destination_rectangle_.y = tail_source_rectangle_.y = 0;
	tail_destination_rectangle_.w = tail_source_rectangle_.w;
	tail_destination_rectangle_.h = tail_source_rectangle_.h;

	SDL_Surface* bg_surface = IMG_Load("../Resources/background.jpg");
	bg_destination_rectangle_.x = bg_source_rectangle_.x = 0;
	bg_destination_rectangle_.y = bg_source_rectangle_.y = 0;
	bg_destination_rectangle_.w = bg_source_rectangle_.w = bg_surface->w;
	bg_destination_rectangle_.h = bg_source_rectangle_.h = bg_surface->h;

	bg_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
}

Stage::~Stage()
{
	SDL_DestroyTexture(item_texture_);
	SDL_DestroyTexture(head_texture_);
	SDL_DestroyTexture(tail_texture_);
	SDL_DestroyTexture(bg_texture_);
	if (bgm)
		Mix_FreeMusic(bgm);
	while (cnt > 0) {
		Stage::DeleteTail();
		cnt--;
	}


}
void Stage::SnakeInit()
{
	pos_x = 360;
	pos_y = 360;

	head_destination_rectangle_.x = pos_x;
	head_destination_rectangle_.y = pos_y;
	pixel_size_ = 30;
	direction_ = 1;
	cnt = 1; 

	snake = new Node;
	snake->data.X = pos_x;
	snake->data.Y = pos_y;
	head = snake;
	tail = snake;

}

void Stage::CrushWall()
{
	if (pos_y < 0 || pos_y > 570 || pos_x < 0 || pos_x > 570) {
		g_current_game_phase = PHASE_ENDING;
		pos_x = 360;
		pos_y = 360;
		direction_ = 1;
		while (cnt > 1) {
			Stage::DeleteTail();
			cnt--;
		}
		Mix_FreeMusic(bgm);
		bgm = Mix_LoadMUS("../Resources/ending.mp3");
		Mix_PlayMusic(bgm, -1);
	}
}
void Stage::EatItem()
{
	if ((item_destination_rectangle_.x == pos_x) && (item_destination_rectangle_.y == pos_y)) {
		Item_ = 0; // item을 먹으면 0으로 초기화
		cnt++; // deletetail()을 실행할 개수만큼 늘려준다.
	}
}
Node* Stage::AddHead()
{
	Node* n = new Node;

	head->prev = n;
	n->prev = nullptr;
	n->next = head;
	head = n;

	n->data.X = pos_x; // 헤드의 좌표를 초기 pos_로 잡아 놓은 위치로 지정시킨다.
	n->data.Y = pos_y;

	head_destination_rectangle_.x = pos_x;
	head_destination_rectangle_.y = pos_y;

	Stage::EatItem();
	// 초기 item은 1로 초기화 되어있음 -> 아이템을 먹으면 0으로 초기화 되기 때문에 
	//헤드가 추가되고 테일이 지워지는 형식으로 계속 유지됨 (동작방식)
	if (Item_ == 1)
		Stage::DeleteTail();

	return n;
}

void Stage::DeleteTail()
{
	Node* n = tail;

	tail = tail->prev;
	tail->next = NULL;
	delete n;
}
void Stage::HitSnake() //몸통이랑 박았을 때
{
	Node* n = new Node;

	for (n = tail; n->prev != NULL; n = n->prev) {
		if (pos_x == n->data.X && pos_y == n->data.Y)
		{
			g_current_game_phase = PHASE_ENDING;
			pos_x = 360;
			pos_y = 360;
			direction_ = 1;
			while (cnt > 1) {
				Stage::DeleteTail();
				cnt--;
			}
			Mix_FreeMusic(bgm);
			bgm = Mix_LoadMUS("../Resources/ending.mp3");
			Mix_PlayMusic(bgm, -1);
		}
	}
}

void Stage::ItemPos()
{
	Node* n = new Node;
	srand((unsigned int)time(NULL)); 
	int x, y;
	while (cnt == 1) {
		x = (rand() % 18) * 30 + 30;  
		y = (rand() % 18) * 30 + 30;  
		n = head;
		if ((n->data.X == x) && (n->data.Y == y)) {
			continue;
		}
		else
			break;

	}
	if (cnt >= 2) {
		x = (rand() % 18) * 30 + 30;
		y = (rand() % 18) * 30 + 30;
		for (n = head; n->next != NULL; n = n->next)
		{
			if ((n->data.X == x) && (n->data.Y == y)) {
				x = (rand() % 18) * 30 + 30;
				y = (rand() % 18) * 30 + 30;
				n = head;
				continue;
			}
		}
	}
	item_destination_rectangle_.x = x;
	item_destination_rectangle_.y = y;
}

void Stage::Update()
{
	if (direction_ == 1)
	{
		pos_y -= pixel_size_;
	}
	else if (direction_ == 2)
	{
		pos_y += pixel_size_;
	}
	else if (direction_ == 3)
	{
		pos_x -= pixel_size_;
	}
	else if (direction_ == 4)
	{
		pos_x += pixel_size_;
	}
	Stage::AddHead();
	if (Item_ == 0)
	{
		Stage::ItemPos();
		Item_ = 1;
	}
	Stage::CrushWall();
	Stage::HitSnake();
	SDL_Delay(120);
}


void Stage::Render()
{
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);

	Node* n = new Node;
	n = head;

	head_destination_rectangle_.x = n->data.X;
	head_destination_rectangle_.y = n->data.Y;
	SDL_RenderCopy(g_renderer, head_texture_, &head_source_rectangle_, &head_destination_rectangle_);

	while (n->next != NULL)
	{
		n = n->next;
		tail_destination_rectangle_.x = n->data.X;
		tail_destination_rectangle_.y = n->data.Y;
		SDL_RenderCopy(g_renderer, tail_texture_, &tail_source_rectangle_, &tail_destination_rectangle_);
	}


	SDL_RenderCopy(g_renderer, item_texture_, &item_source_rectangle_, &item_destination_rectangle_);
	SDL_RenderPresent(g_renderer);
}



void Stage::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
			{
				if (direction_ == 2 && head != tail)
					return;
				direction_ = 1;

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (direction_ == 1 && head != tail)
					return;
				direction_ = 2;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (direction_ == 4 && head != tail)
					return;
				direction_ = 3;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (direction_ == 3 && head != tail)
					return;
				direction_ = 4;
			}
			break;

		default:

			break;
		}
	}
}
