
#include "SDL.h"
#include <iostream>
#include "GameFunc.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "GameStage.h"
#include "TextureManager.h"
#include "IntroStage.h"

Stage *stage;
SDL_Renderer *g_renderer;
SDL_Window *g_window;
TTF_Font *game_font;
int g_flag_running;
int ground_height;
int g_window_width;
int g_window_height;
int g_cur_time_ms;
int max_score;

int main(int argc, char* argv[])
{
	g_cur_time_ms = 0;
	g_window_width = 1280;
	g_window_height = 720;
	ground_height = g_window_height / 9 * 8 + 10;
	max_score = 0;
	InitializeWindow("GameTest", 100, 100, g_window_width, g_window_height, false);

	//텍스쳐 매니저 초기화.
	TextureManager::CreateInstance();
	TextureManager* tm = TextureManager::GetSingleton();
	
	//폰트 이니셜라이즈
	TTF_Init();
	game_font = TTF_OpenFont("../Resources/jjang_font.ttf", 50);

	//오디오 이니셜라이즈
	int audio_rate = 44100;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0) {
		fprintf(stderr, "오디오 재생 실패 : %s\n", SDL_GetError());
		Mix_CloseAudio();
	}

	else {
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("오디오 오픈 %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");
	}

	//클래스 테스트
	stage = new IntroStage();

	while(g_flag_running != 0)
	{

		stage->Update();
		stage->HandleEvents();
		stage->Render();

		g_cur_time_ms += 30;
		SDL_Delay(30);	// 30 밀리세컨드 기다린다
	}

	ClearWindow();

	Mix_CloseAudio();
	TTF_CloseFont(game_font);
	TTF_Quit();

	return 0;
}



////////////////////////////////////
// Functions for the Window
bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos, 
			width, height, flags);

		if(g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if(g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer, 
					255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = 1; // everything inited successfully, start the main loop

	return true;

}


void ClearWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}