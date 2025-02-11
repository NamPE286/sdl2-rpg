#pragma once

#include <SDL2/SDL.h>
#include "../entities/Character.hpp"
#include "TileMap.hpp"
#include "Camera.hpp"

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	Character* player = nullptr;
	Camera* camera = nullptr;
	TileMap* tileMap = nullptr;

	bool running = true;

	void update(float deltaTime);
	void render();
	void event_handler(SDL_Event& event);
public:
	Game();
	~Game();
	void init_game_loop();
	void stop_game_loop();
};