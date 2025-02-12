#include "TileMap.hpp"
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>
#include <iostream>

int lvl[MAP_H][MAP_W] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

bool coll[MAP_H][MAP_W] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

TileMap::TileMap(SDL_Renderer* const renderer): renderer(renderer) {
	texture.dirt = new Image(renderer, "assets/textures/dirt.png");
	texture.grass = new Image(renderer, "assets/textures/grass.png");
	texture.tree = new Image(renderer, "assets/textures/tree.png");

	load(lvl, coll);
}

TileMap::~TileMap() {
	delete texture.dirt;
	delete texture.grass;
	delete texture.tree;
}

void TileMap::load(int lvl[MAP_H][MAP_W], bool coll[MAP_H][MAP_W]) {
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			textureMap[i][j] = lvl[i][j];
			collisionMap[i][j] = coll[i][j];
		}
	}
}

void TileMap::collision_handler(Character* c) const {
	int x = c->pos.x / 32;
	int y = c->pos.y / 32;

	if (c->pos.x < 0) {
		c->pos.x = 0;
		c->stop_movement();

		return;
	}
	
	if (c->pos.x > 32 * (MAP_W - 1)) {
		c->pos.x = 32 * (MAP_W - 1);
		c->stop_movement();

		return;
	}

	if (c->pos.y < 0) {
		c->pos.y = 0;
		c->stop_movement();

		return;
	}
	
	if (c->pos.y > 32 * (MAP_H - 1)) {
		c->pos.y = 32 * (MAP_H - 1);
		c->stop_movement();

		return;
	}

	if (c->velocity.x > 0 && collisionMap[y][x + 1]) {
		c->pos.x = 32 * x;
		c->stop_movement();
	
	}
	else if (c->velocity.x < 0 && collisionMap[y][x]) {
		c->pos.x = 32 * (x + 1);
		c->stop_movement();
	}
	else if (c->velocity.y > 0 && collisionMap[y + 1][x]) {
		c->pos.y = 32 * y;
		c->stop_movement();
	}
	else if (c->velocity.y < 0 && collisionMap[y][x]) {
		c->pos.y = 32 * (y + 1);
		c->stop_movement();
	}
}

void TileMap::render() {
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			texture.grass->render(32 * j, 32 * i);

			switch (textureMap[i][j]) {
			case Tile::DIRT:
				texture.dirt->render(32 * j, 32 * i);
				break;
			case Tile::STONE:
				texture.tree->render(32 * j, 32 * i);
				break;
			}
		}
	}
}