#pragma once

#include <string>
#include <SDL2/SDL.h>

class Image {
	SDL_Renderer* renderer = nullptr;

public:
	SDL_Texture* texture = nullptr;
	int w = 0, h = 0;

	Image(SDL_Renderer* renderer, std::string filePath, int x = 0, int y = 0, int w = NULL, int h = NULL, float scale = 1.0f);
	~Image();
	void update(int x, int y, SDL_Rect* srcrect = nullptr);
};