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
	SDL_Renderer* const renderer;
	Uint32 lastKey = 0;
public:
	bool isKeyDown = false;
	bool moving = false;
	Vec2 pos, stopPos, velocity;

	Character(
		SDL_Renderer* const renderer,
		const std::string filePath, 
		Vec2 pos = Vec2(0, 0), 
		float scale = 1.0f
	);
	~Character();
	void update(const float deltaTime);
	void render();
	void stop_movement();
	void on_key_down(const SDL_Event& event);
	void on_key_up(const SDL_Event& event);
};