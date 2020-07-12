#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
class Intro
{
public:
	Intro();
	~Intro();
	void HandleEvents();
	void Update();
	void Render();

private: 
	TTF_Font *title_font;
	TTF_Font *start_font;

	SDL_Texture *game_title_texture;
	SDL_Texture *start_title_texture;
	SDL_Texture * texture_; 

	SDL_Rect source_rectangle_; 
	SDL_Rect destination_rectangle_;
	SDL_Rect dest_game_title;
	SDL_Rect dest_start_title;
};
