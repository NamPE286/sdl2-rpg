#include "TileMap.hpp"
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>

int lvl[MAP_H][MAP_W] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

bool coll[MAP_H][MAP_W] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

TileMap::TileMap(SDL_Renderer* renderer): renderer(renderer) {
	texture.field = new Image(renderer, "assets/textures/FieldsTile_01.png");
	texture.grass = new Image(renderer, "assets/textures/FieldsTile_38.png");
	texture.stone = new Image(renderer, "assets/textures/Stone.png");

	load(lvl, coll);
}

TileMap::~TileMap() {
	delete texture.field;
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

	c->pos.x = __max(0, c->pos.x);
	c->pos.x = __min(32 * 19, c->pos.x);

	c->pos.y = __max(0, c->pos.y);
	c->pos.y = __min(32 * 14, c->pos.y);

	for(size_t i = 0; i < 4; i++) {
		int x = (c->pos.x + 32 * dirs[i].first + offset[i].first) / 32;
		int y = (c->pos.y + 32 * dirs[i].second + offset[i].second) / 32;

		if (!(0 <= x && x < MAP_W)) {
			continue;
		}

		if (!(0 <= y && y < MAP_H)) {
			continue;
		}

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
		}
	}
}

void TileMap::render() {
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			texture.field->render(32 * j, 32 * i);

			switch (textureMap[i][j]) {
			case Tile::GRASS:
				texture.grass->render(32 * j, 32 * i);
				break;
			case Tile::STONE:
				texture.stone->render(32 * j, 32 * i);
				break;
			}
		}
	}
}