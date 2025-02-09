#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"

enum Object {
	NONE,
	COBBLESTONE
};

class TileMap {
	SDL_Renderer* renderer = nullptr;
	Image* cobblestone = nullptr;
	SDL_Rect src = { 0, 0, 0, 0 }, dest = { 0, 0, 0, 0 };
	int map[20][20] = {};
public:
	TileMap(SDL_Renderer* renderer);
	void load(int arr[20][20]);
	void render();
};