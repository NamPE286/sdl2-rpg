#pragma once

#include <string>
#include <SDL2/SDL.h>

class Image {
	SDL_Renderer* renderer = nullptr;

public:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = { 0, 0, 0, 0 };

	Image(SDL_Renderer* renderer, std::string filePath, int x = 0, int y = 0, int w = NULL, int h = NULL, float scale = 1.0f);
	~Image();
	void update(SDL_Rect* pos = nullptr);
};