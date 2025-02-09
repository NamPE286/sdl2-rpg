#pragma once

#include <SDL2/SDL.h>
#include "../media/Image.hpp"

class Map {
	SDL_Renderer* renderer = nullptr;
	Image* cobblestone = nullptr;
	SDL_Rect src = { 0, 0, 0, 0 }, dest = { 0, 0, 0, 0 };
public:
	Map(SDL_Renderer* renderer);
};