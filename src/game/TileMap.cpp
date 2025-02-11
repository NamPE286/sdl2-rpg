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

TileMap::TileMap(SDL_Renderer* renderer): renderer(renderer) {
	texture.dirt = new Image(renderer, "assets/textures/FieldsTile_01.png");
	texture.grass = new Image(renderer, "assets/textures/FieldsTile_38.png");
	texture.stone = new Image(renderer, "assets/textures/Stone.png");

	load(lvl, coll);
}

TileMap::~TileMap() {
	delete texture.dirt;
	delete texture.grass;
	delete texture.stone;
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
	std::vector<std::pair<int, int>> dirs = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	std::vector<std::pair<int, int>> offset = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

	if (c->pos.x < 0) {
		c->pos.x = 0;
		c->stop_movement();
	}
	else if (c->pos.x > 32 * (MAP_W - 1)) {
		c->pos.x = 32 * (MAP_W - 1);
		c->stop_movement();
	}

	if (c->pos.y < 0) {
		c->pos.y = 0;
		c->stop_movement();
	}
	else if (c->pos.y > 32 * (MAP_H - 1)) {
		c->pos.y = 32 * (MAP_H - 1);
		c->stop_movement();
	}

	std::cout << c->pos.x << '\n';

	for(size_t i = 0; i < 4; i++) {
		int x = (c->pos.x + 32 * dirs[i].first + offset[i].first) / 32;
		int y = (c->pos.y + 32 * dirs[i].second + offset[i].second) / 32;

		if (collisionMap[y][x]) {
			if (c->velocity.x > 0) {
				c->pos.x = std::floor(c->pos.x / 32) * 32;
			}
			else if (c->velocity.x < 0) {
				c->pos.x = std::ceil(c->pos.x / 32) * 32;
			}

			if (c->velocity.y > 0) {
				c->pos.y = std::floor(c->pos.y / 32) * 32;
			}
			else if (c->velocity.y < 0) {
				c->pos.y = std::ceil(c->pos.y / 32) * 32;
			}

			c->stopPos = c->pos;
			c->stop_movement();

			break;
		}
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
				texture.stone->render(32 * j, 32 * i);
				break;
			}
		}
	}
}