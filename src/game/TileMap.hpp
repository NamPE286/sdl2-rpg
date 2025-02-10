#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"
#include "../entities/Character.hpp"
#include "../common.h"

constexpr int MAP_W = WINDOW_WIDTH / 32;
constexpr int MAP_H = WINDOW_HEIGHT / 32;

enum Tile {
	GRASS,
	DIRT,
	STONE
};

class TileMap {
	struct Texture {
		Image* dirt = nullptr;
		Image* grass = nullptr;
		Image* stone = nullptr;
	} texture;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect src = { 0, 0, 0, 0 }, dest = { 0, 0, 0, 0 };
	int textureMap[MAP_H][MAP_W] = {};
	int collisionMap[MAP_H][MAP_W] = {};
public:
	TileMap(SDL_Renderer* renderer);
	~TileMap();
	void load(int lvl[MAP_H][MAP_W], bool coll[MAP_H][MAP_W]);
	void collision_handler(Character* c) const;
	void render();
};