#pragma once

#include <SDL2/SDL.h>
#include <string>

class Dialogue {
	SDL_Renderer* renderer;

public:
	Dialogue(SDL_Renderer* renderer);
	void render(std::string content);
};