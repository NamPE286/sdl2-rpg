#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"

enum Object {
	FIELD,
	COBBLESTONE
};

class TileMap {
	struct Texture {
		Image* field = nullptr;
	} texture;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect src = { 0, 0, 0, 0 }, dest = { 0, 0, 0, 0 };
	int map[20][20] = {};
public:
	TileMap(SDL_Renderer* renderer);
	~TileMap();
	void load(int arr[20][15]);
	void render();
};