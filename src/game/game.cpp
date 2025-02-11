#include "Game.hpp"
#include <stdexcept>
#include <string>
#include <chrono>
#include <iostream>
#include <memory>
#include "../geometry/Vec2.hpp"
#include "../media/Image.hpp"
#include "../common.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("Failed to initialize SDL. SDL error: " + std::string(SDL_GetError()));
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	window = SDL_CreateWindow("RPG", (DM.w - WINDOW_WIDTH) / 2, (DM.h - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window. SDL error: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		throw std::runtime_error("Failed to create renderer. SDL error: " + std::string(SDL_GetError()));
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	player = new Character(renderer, "assets/sprites/characters/kirito.png");
	tileMap = new TileMap(renderer);
};

Game::~Game() {
	delete player;
	delete tileMap;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyTexture(texture);
	texture = nullptr;

	SDL_Quit();
};

void Game::update(float deltaTime) {
	player->update(deltaTime);
	tileMap->collision_handler(player);
}

void Game::render() {
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
	SDL_RenderClear(renderer);

	tileMap->render();
	player->render();

	SDL_SetRenderTarget(renderer, nullptr);

	const int CAMERA_WIDTH = WINDOW_WIDTH / 4;
	const int CAMERA_HEIGHT = WINDOW_HEIGHT / 4;

	SDL_Rect rect = { player->pos.x - CAMERA_WIDTH / 2 + 16, player->pos.y - CAMERA_HEIGHT / 2 + 16, CAMERA_WIDTH, CAMERA_HEIGHT };

	rect.x = __max(0, rect.x);
	rect.x = __min(WINDOW_WIDTH - CAMERA_WIDTH, rect.x);

	rect.y = __max(0, rect.y);
	rect.y = __min(WINDOW_HEIGHT - CAMERA_HEIGHT, rect.y);

	SDL_RenderCopy(renderer, texture, &rect, nullptr);
	SDL_RenderPresent(renderer);
}

void Game::event_handler(SDL_Event& event) {
	switch (event.type) {
	case SDL_QUIT:
		stop_game_loop();

		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			stop_game_loop();
		}

		player->on_key_down(event);

		break;
	case SDL_KEYUP:
		player->on_key_up(event);

		break;
	}
}

void Game::init_game_loop() {
	const int frameDelay = 1000 / MAX_FPS;
	float deltaTime = 0.0f;
	
	running = true;

	while (running) {
		SDL_Event event;
		auto frameStartTime = std::chrono::high_resolution_clock::now();

		while (SDL_PollEvent(&event)) {

			event_handler(event);
		}

		update(deltaTime);
		render();

		if (frameDelay > deltaTime) {
			SDL_Delay(frameDelay - deltaTime);
		}

		auto frameStopTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(frameStopTime - frameStartTime).count();
	}
}

void Game::stop_game_loop() {
	running = false;
}

