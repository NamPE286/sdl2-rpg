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
	struct Sprite {
		Image* img = nullptr;
		int direction = SpriteDirection::DOWN;
		int frameIndex = 0;
		float frameTime = 0.0f;
		float scale = 1.0f;
	} sprite;
	SDL_Renderer* renderer = nullptr;
	Vec2 pos, velocity;
	Uint32 lastKey = 0;

	void update_sprite();
public:
	Character(SDL_Renderer* renderer, std::string filePath, Vec2 pos = Vec2(0, 0), float scale = 1.0f);
	~Character();
	void update(float deltaTime);
	void on_key_down(SDL_Event& event);
	void on_key_up(SDL_Event& event);
};