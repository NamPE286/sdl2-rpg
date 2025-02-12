#pragma once

#include <string>
#include <SDL2/SDL.h>

class Image {
	SDL_Renderer* const renderer = nullptr;

public:
	SDL_Texture* texture = nullptr;
	int w = 0, h = 0;
	float scale = 1.0f;

	Image(
		SDL_Renderer* const renderer,
		const std::string filePath, 
		int _w = NULL, 
		int _h = NULL, 
		float scale = 1.0f
	);
	~Image();
	void render(int x, int y, SDL_Rect* srcrect = nullptr);
};