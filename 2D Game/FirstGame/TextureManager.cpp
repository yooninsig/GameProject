
#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

extern SDL_Renderer* g_renderer;

TextureManager* TextureManager::instance = 0;

void TextureManager::CreateInstance()
{
	if (instance != 0) return;
	instance = new TextureManager();
}

void TextureManager::DestroyInstance()
{
	if (instance == 0) return;

	std::map<std::string, SDL_Texture*>::iterator iter = instance->textureMap.begin();
	while (iter != instance->textureMap.end())
	{
		SDL_DestroyTexture(iter->second);
		iter++;
	}
	delete instance;
	instance = 0;
}

TextureManager* TextureManager::GetSingleton()
{
	return instance;
}

bool TextureManager::LoadTexture(std::string texture_id, std::string file_name)
{
	SDL_Surface* temp_surface = IMG_Load(file_name.c_str());
	if (temp_surface == 0)
	{
		std::cout << file_name + "LoadTextureFailed" << std::endl;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = temp_surface->w;
	rect.h = temp_surface->h;

	SDL_FreeSurface(temp_surface);

	// everything went ok, add the texture to our list
	if (texture != 0)
	{
		textureMap[texture_id] = texture;
		AddSpriteRect(texture_id, rect.x, rect.y, rect.w, rect.h);
		return true;
	}

	// reaching here means something went wrong
	return false;
}

bool TextureManager::LoadTexture(std::string texture_id, std::string file_name, unsigned char color_key_r, unsigned char color_key_g, unsigned char color_key_b)
{
	SDL_Surface* temp_surface = IMG_Load(file_name.c_str());
	if (temp_surface == 0)
	{
		std::cout << file_name + "LoadTextureFailed" << std::endl;
		return false;
	}
	SDL_SetColorKey(temp_surface, 1, SDL_MapRGB(temp_surface->format, color_key_r, color_key_g, color_key_b));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = temp_surface->w;
	rect.h = temp_surface->h;

	SDL_FreeSurface(temp_surface);

	// everything went ok, add the texture to our list
	if (texture != 0)
	{
		textureMap[texture_id] = texture;
		AddSpriteRect(texture_id, rect.x, rect.y, rect.w, rect.h);
		return true;
	}

	// reaching here means something went wrong
	return false;
}


void TextureManager::AddSpriteRect(std::string sprite_id, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	spriteRects[sprite_id] = rect;
}

void TextureManager::DrawSprite(std::string texture_id)
{
	DrawSprite(texture_id, texture_id, 0, 0);
}

void TextureManager::DrawSprite(std::string texture_id, std::string sprite_id, int x, int y)
{
	SDL_Rect src_rect = spriteRects[sprite_id];
	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = src_rect.w;
	dest_rect.h = src_rect.h;
	SDL_RenderCopy(g_renderer, textureMap[texture_id], &src_rect, &dest_rect);
}

void TextureManager::DrawSprite(std::string texture_id, std::string sprite_id, int x, int y, int w, int h) {
	SDL_Rect src_rect = spriteRects[sprite_id];
	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = w;
	dest_rect.h = h;
	SDL_RenderCopy(g_renderer, textureMap[texture_id], &src_rect, &dest_rect);
}

void TextureManager::DrawSpriteRef(std::string texture_id) {
	DrawSpriteRef(texture_id, texture_id, 0, 0);
}

void TextureManager::DrawSpriteRef(std::string texture_id, std::string sprite_id, int x, int y) {
	SDL_Rect src_rect = spriteRects[sprite_id];
	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = src_rect.w;
	dest_rect.h = src_rect.h;
	SDL_Point p;
	p.x = src_rect.w;
	p.y = src_rect.h;
	SDL_RenderCopyEx(g_renderer, textureMap[texture_id], &src_rect, &dest_rect, 0, &p, SDL_FLIP_HORIZONTAL);
}

void TextureManager::DrawSpriteRef(std::string texture_id, std::string sprite_id, int x, int y, int w, int h) {
	SDL_Rect src_rect = spriteRects[sprite_id];
	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = w;
	dest_rect.h = h;
	SDL_Point p;
	p.x = src_rect.w;
	p.y = src_rect.h;
	SDL_RenderCopyEx(g_renderer, textureMap[texture_id], &src_rect, &dest_rect, 0, &p, SDL_FLIP_HORIZONTAL);
}

void TextureManager::DrawSprite(std::string texture_id, std::string sprite_id, SDL_Rect des_rect) {
	DrawSprite(texture_id, sprite_id, des_rect.x, des_rect.y, des_rect.w, des_rect.h);
}

void TextureManager::DrawSpriteRef(std::string texture_id, std::string sprite_id, SDL_Rect des_rect) {
	DrawSpriteRef(texture_id, sprite_id, des_rect.x, des_rect.y, des_rect.w, des_rect.h);
}
