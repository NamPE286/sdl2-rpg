#pragma once

#include <string>
#include <SDL2/SDL.h>

class Image {
	SDL_Renderer* renderer = nullptr;

public:
	SDL_Texture* texture = nullptr;
	int w = 0, h = 0;
	float scale = 1.0f;

	Image(SDL_Renderer* renderer, std::string filePath, int w = NULL, int h = NULL, float scale = 1.0f);
	~Image();
	void update(int x, int y, SDL_Rect* srcrect = nullptr);
};