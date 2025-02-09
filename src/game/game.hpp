#pragma once

#include <SDL2/SDL.h>

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = true;

	void update(float deltaTime);
	void render();
	void input_handler(SDL_Event& event);
public:
	Game();
	~Game();
	void init_game_loop();
	void stop_game_loop();
};