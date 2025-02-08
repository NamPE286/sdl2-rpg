#pragma once

#include <SDL2/SDL.h>

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = true;

	void update();
	void draw();
public:
	Game();
	~Game();
};