#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"

enum Tile {
	FIELD,
	GRASS,
	STONE
};

class TileMap {
	struct Texture {
		Image* field = nullptr;
		Image* grass = nullptr;
		Image* stone = nullptr;
	} texture;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect src = { 0, 0, 0, 0 }, dest = { 0, 0, 0, 0 };
	int map[15][20] = {};
public:
	TileMap(SDL_Renderer* renderer);
	~TileMap();
	void load(int arr[15][20]);
	void render();
};