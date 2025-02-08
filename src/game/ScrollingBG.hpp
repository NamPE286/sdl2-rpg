#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"
#include "../geometry/Vec2.hpp"

class ScrollingBG {
	std::shared_ptr<Image> img;
	Vec2 pos;
	Vec2 velocity;
public:
	ScrollingBG(std::shared_ptr<Image> img);
	void update(float deltaTime);
	void on_key_down(SDL_Event& event);
	void on_key_up(SDL_Event& event);
};