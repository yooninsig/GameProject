#include "ClassIntro.h"
#include "ClassPhase.h"
#include "SDL_image.h"
#include <iostream>
#include<SDL_mixer.h>
#include "SDL_ttf.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
Mix_Music *bgm;
SDL_Rect start_r;
Intro::Intro()
{
	

	SDL_Surface* temp_surface = IMG_Load("../Resources/start.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;

	title_font = TTF_OpenFont("../Resources/game_font.ttf", 70);
	SDL_Color yellow = { 255, 255, 0, 0 };
	SDL_Surface *title_surface = TTF_RenderText_Blended(title_font, "My Banana!! ", yellow);

	start_font = TTF_OpenFont("../Resources/game_font.ttf", 50);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *start_surface = TTF_RenderText_Blended(start_font, "Start Game ", white);

	game_title_texture = SDL_CreateTextureFromSurface(g_renderer, title_surface);
	start_title_texture = SDL_CreateTextureFromSurface(g_renderer, start_surface);

	dest_game_title.x = 0;
	dest_game_title.y = 0;
	dest_game_title.w = title_surface->w;
	dest_game_title.h = title_surface->h;

	dest_start_title.x = 0;
	dest_start_title.y = 0;
	dest_start_title.w = start_surface->w;
	dest_start_title.h = start_surface->h;


	SDL_FreeSurface(title_surface);
	SDL_FreeSurface(start_surface);

	Mix_VolumeMusic(128);

	bgm = Mix_LoadMUS("../Resources/Intro.mp3");
	if (!bgm) 
	{
		printf(" %s\n", Mix_GetError());
	}
	Mix_PlayMusic(bgm, -1);
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(game_title_texture);
	SDL_DestroyTexture(start_title_texture);
	if (bgm)
		Mix_FreeMusic(bgm);
}

void Intro::Update()
{
}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); 

	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	{
		SDL_Rect title_r;
		title_r.x = 70;
		title_r.y = 200;
		title_r.w = dest_game_title.w;
		title_r.h = dest_game_title.h;
		SDL_RenderCopy(g_renderer, game_title_texture, 0, &title_r);
	}

	{
		start_r.x = 140;
		start_r.y = 350;
		start_r.w = dest_start_title.w;
		start_r.h = dest_start_title.h;
		SDL_RenderCopy(g_renderer, start_title_texture, 0, &start_r);
	}

	SDL_RenderPresent(g_renderer); 
}



void Intro::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > start_r.x &&
					mouse_y > start_r.y &&
					mouse_x < start_r.x + start_r.w &&
					mouse_y < start_r.y + start_r.h)
					g_current_game_phase = PHASE_STAGE;
			}
			break;

		default:
			break;
		}
	}
}
