#include "EndingStage.h"
#include "TextureManager.h"
#include "IntroStage.h"
#include "GameStage.h"
#include "GameFunc.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <atlstr.h>

extern Stage *stage;
extern SDL_Renderer *g_renderer;
extern TTF_Font* game_font;
extern int g_flag_running;
extern int g_window_width;
extern int g_window_height;
extern int max_score;

SDL_Rect end_text_rect;
//0 : 보통, 1 : 주황글씨.
static int click_mode;

EndingStage::EndingStage() {
	
}

EndingStage::EndingStage(int end, int score) {
	ending = 2;
	click_mode = 0;
	end_buff = end;
	myScore = score;
	if (score > max_score) {
		max_score = score;
	}

	TextureManager* tm = TextureManager::GetSingleton();
	tm->LoadTexture("bg_clear", "../res/clear_bg_image.png");
	tm->LoadTexture("bg_end", "../res/end_bg_image.png");
	tm->LoadTexture("bg_score", "../res/score_background.png");
	tm->LoadTexture("end_text", "../res/end_text_image.png", 255, 255, 255);

	tm->AddSpriteRect("end_text_back0", 0, 0, 400, 80);
	tm->AddSpriteRect("end_text_back1", 0, 80, 400, 80);

	end_text_rect.w = 400;
	end_text_rect.h = 100;
	end_text_rect.x = g_window_width / 2 + end_text_rect.w / 2;
	end_text_rect.y = 500;

	bgm = Mix_LoadMUS("../music/gameover.mp3");
	Mix_PlayMusic(bgm, -1);
	buttonSound = Mix_LoadWAV("../music/button.WAV");
}

EndingStage::~EndingStage() {
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
	if (bgm)
		Mix_FreeMusic(bgm);
	if (buttonSound)
		Mix_FreeChunk(buttonSound);
}

void EndingStage::Render() {
	TextureManager* tm = TextureManager::GetSingleton();
	SDL_RenderClear(g_renderer);
	DrawBackGround();

	if (ending == 0 || ending == 1) {
		if (click_mode == 0) {
			tm->DrawSprite("end_text", "end_text_back0", end_text_rect);
		}
		else if (click_mode == 1) {
			tm->DrawSprite("end_text", "end_text_back1", end_text_rect);
		}
	}
	//스코어 그리기
	else if(ending == 2) {
		SDL_Color black = { 0, 0, 0, 0 };
		SDL_Surface *score_surface = TTF_RenderText_Blended(game_font, std::to_string((long long)max_score).c_str(), black);

		SDL_Rect score_rect;
		score_rect.x = 0;
		score_rect.w = score_surface->w;
		score_rect.y = 0;
		score_rect.h = score_surface->h;

		SDL_Texture* score_texture = SDL_CreateTextureFromSurface(g_renderer, score_surface);
		SDL_FreeSurface(score_surface);

		SDL_Rect score_dest;
		int score_digit = 0;
		for (int i = max_score; i != 0; i = i / 10)
			score_digit++;
		score_dest.x = 1060 - 50 * (score_digit + 1);
		score_dest.w = (score_digit + 1) * 50;
		score_dest.y = 320;
		score_dest.h = 60;

		SDL_RenderCopy(g_renderer, score_texture, &score_rect, &score_dest);

		SDL_Surface *my_score_surface = TTF_RenderText_Blended(game_font, std::to_string((long long)myScore).c_str(), black);

		SDL_Rect my_score_rect;
		my_score_rect.x = 0;
		my_score_rect.w = my_score_surface->w;
		my_score_rect.y = 0;
		my_score_rect.h = my_score_surface->h;

		SDL_Texture* my_score_texture = SDL_CreateTextureFromSurface(g_renderer, my_score_surface);
		SDL_FreeSurface(my_score_surface);

		SDL_Rect my_score_dest;
		score_digit = 0;
		for (int i = myScore; i != 0; i = i / 10)
			score_digit++;
		my_score_dest.x = 600;
		my_score_dest.w = (score_digit + 1) * 50;
		my_score_dest.y = 610;
		my_score_dest.h = 60;

		SDL_RenderCopy(g_renderer, score_texture, &my_score_rect, &my_score_dest);
	}

	SDL_RenderPresent(g_renderer);
}

void EndingStage::HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (ending != 2) {
					int mouse_x = event.button.x;
					int mouse_y = event.button.y;

					if (mouse_x > end_text_rect.x &&
						mouse_y > end_text_rect.y &&
						mouse_x < end_text_rect.x + end_text_rect.w &&
						mouse_y < end_text_rect.y + end_text_rect.h) {

						click_mode = 1;
					}
				}

			}
			break;

		case SDL_MOUSEBUTTONUP:

			if (event.button.button == SDL_BUTTON_LEFT) {

				if (ending != 2) {
					int mouse_x = event.button.x;
					int mouse_y = event.button.y;

					click_mode = 0;

					if (mouse_x > end_text_rect.x &&
						mouse_y > end_text_rect.y &&
						mouse_x < end_text_rect.x + end_text_rect.w &&
						mouse_y < end_text_rect.y + end_text_rect.h) {

						delete this;
						Mix_PlayChannel(-1, buttonSound, 0);
						stage = new IntroStage();
					}
				}
				else if (ending == 2) {
					ending = end_buff;
				}
			}
			break;


		default:
			break;
		}
	}
}

void EndingStage::Update() {

}

void EndingStage::DrawBackGround() {
	TextureManager* tm = TextureManager::GetSingleton();
	SDL_Rect des;
	des.x = 0;
	des.y = 0;
	des.w = g_window_width;
	des.h = g_window_height;
	SDL_Texture* texture;
	if (ending == 0) {
		texture = tm->GetTexture("bg_clear");
	}

	else if (ending == 1) {
		texture = tm->GetTexture("bg_end");
	}

	else if (ending == 2) {
		texture = tm->GetTexture("bg_score");
	}

	SDL_RenderCopy(g_renderer, texture, 0, &des);
}