#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "../media/Image.hpp"

class ScrollingBG {
	std::shared_ptr<Image> img;
	SDL_Rect rect = { 0, 0, 0, 0 };
public:
	ScrollingBG(std::shared_ptr<Image> img);
	void update();
	void on_key_down(SDL_Event& event);
};