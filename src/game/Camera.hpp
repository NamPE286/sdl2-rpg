#pragma once

#include <SDL2/SDL.h>
#include "../geometry/Vec2.hpp"

class Camera {
	SDL_Renderer* const renderer = nullptr;
	SDL_Texture* const texture = nullptr;
	Vec2* pos = nullptr;
	int w = 0, h = 0;

public:
	Camera(
		SDL_Renderer* const renderer,
		SDL_Texture* const texture,
		Vec2* pos,
		int w,
		int h
);
	void render();
};