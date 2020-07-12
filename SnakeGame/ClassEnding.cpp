#include "ClassEnding.h"
#include "ClassPhase.h"
#include "ClassIntro.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include "SDL_ttf.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern Mix_Music *bgm;

TTF_Font *End_title_font;
SDL_Texture *End_game_title_texture;
SDL_Rect End_dest_game_title;

TTF_Font *End_font;
SDL_Texture *End_title_texture;
SDL_Rect dest_End_title;
SDL_Rect End_r;

Ending::Ending()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/end.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;

	End_title_font = TTF_OpenFont("../Resources/game_font.ttf", 70);
	SDL_Color red = { 255, 0, 0, 0 };
	SDL_Surface *End_title_surface = TTF_RenderText_Blended(End_title_font, "Game Over ", red);

	End_font = TTF_OpenFont("../Resources/game_font.ttf", 50);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *End_surface = TTF_RenderText_Blended(End_font, "Restart Banana ", white);

	End_dest_game_title.x = 0;
	End_dest_game_title.y = 0;
	End_dest_game_title.w = End_title_surface->w;
	End_dest_game_title.h = End_title_surface->h;

	dest_End_title.x = 0;
	dest_End_title.y = 0;
	dest_End_title.w = End_surface->w;
	dest_End_title.h = End_surface->h;

	End_game_title_texture = SDL_CreateTextureFromSurface(g_renderer, End_title_surface);
	End_title_texture = SDL_CreateTextureFromSurface(g_renderer, End_surface);
	SDL_FreeSurface(End_title_surface);

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(End_game_title_texture);
	SDL_DestroyTexture(End_title_texture);
	if (bgm)
		Mix_FreeMusic(bgm);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	{
		SDL_Rect End_title_r;
		End_title_r.x = 90;
		End_title_r.y = 200;
		End_title_r.w = End_dest_game_title.w;
		End_title_r.h = End_dest_game_title.h;
		SDL_RenderCopy(g_renderer, End_game_title_texture, 0, &End_title_r);
	}
	{

		End_r.x = 90;
		End_r.y = 350;
		End_r.w = dest_End_title.w;
		End_r.h = dest_End_title.h;
		SDL_RenderCopy(g_renderer, End_title_texture, 0, &End_r);
	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
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

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				{
					int mouse_x = event.button.x;
					int mouse_y = event.button.y;

					if (mouse_x > End_r.x &&
						mouse_y > End_r.y &&
						mouse_x < End_r.x + End_r.w &&
						mouse_y < End_r.y + End_r.h)
						g_current_game_phase = PHASE_INTRO;
						Mix_FreeMusic(bgm);
						bgm = Mix_LoadMUS("../Resources/background.mp3");
						Mix_PlayMusic(bgm, -1);
				}
			}
			break;

		default:
			break;
		}
	}
}
