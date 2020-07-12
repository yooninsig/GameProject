#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <string>


class TextureManager
{
private:
	TextureManager() {};
	static TextureManager* instance;

public:

	// Singleton
	static void CreateInstance();
	static void DestroyInstance();
	static TextureManager* GetSingleton();

	// Load Texture 
	bool LoadTexture(std::string texture_id, std::string file_name);
	bool LoadTexture(std::string texture_id, std::string file_name, unsigned char color_key_r, unsigned char color_key_g, unsigned char color_key_b);
	void AddSpriteRect(std::string sprite_id, int x, int y, int w, int h);

	// Draw
	void DrawSprite(std::string texture_id);
	void DrawSprite(std::string texture_id, std::string sprite_id, int x, int y);
	void DrawSprite(std::string texture_id, std::string sprite_id, int x, int y, int w, int h);
	void DrawSpriteRef(std::string texture_id);
	void DrawSpriteRef(std::string texture_id, std::string sprite_id, int x, int y);
	void DrawSpriteRef(std::string texture_id, std::string sprite_id, int x, int y, int w, int h);
	void DrawSprite(std::string texture_id, std::string sprite_id, SDL_Rect des_rect);
	void DrawSpriteRef(std::string texture_id, std::string sprite_id, SDL_Rect des_rect);

	SDL_Rect GetSpriteRect(std::string sprite_id) const { return spriteRects.find(sprite_id)->second; }
	SDL_Texture* GetTexture(std::string texture_id) { return textureMap[texture_id]; }

private:
	std::map<std::string, SDL_Texture*> textureMap;
	std::map<std::string, SDL_Rect> spriteRects;
};