#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"
#include "../geometry/Vec2.hpp"

enum SpriteDirection {
	DOWN,
	LEFT,
	RIGHT,
	UP
};

class Character {
	SDL_Renderer* renderer = nullptr;
	Image* sprite = nullptr;
	Vec2 pos, velocity;
	int spriteFrame = 0;
	float scale = 1.0f;

	void update_sprite(int dir);
public:
	Character(SDL_Renderer* renderer, std::string filePath, Vec2 pos = Vec2(0, 0), float scale = 1.0f);
	~Character();
	void update(float deltaTime);
	void on_key_down(SDL_Event* event);
	void on_key_up(SDL_Event* event);
};