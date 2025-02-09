#include "Game.hpp"
#include <stdexcept>
#include <string>
#include <chrono>
#include <iostream>
#include <memory>
#include "../media/Image.hpp"
#include "../common.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("Failed to initialize SDL. SDL error: " + std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow("SDL Tutorial", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window. SDL error: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		throw std::runtime_error("Failed to create renderer. SDL error: " + std::string(SDL_GetError()));
	}
};

Game::~Game() {
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
};

void Game::update(float deltaTime) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
	SDL_RenderClear(renderer);
}

void Game::render() {
	SDL_RenderPresent(renderer);
}

void Game::input_handler(SDL_Event& event) {
	switch (event.type) {
	case SDL_QUIT:
		stop_game_loop();

		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			stop_game_loop();
		}

		break;
	case SDL_KEYUP:

		break;
	}
}

void Game::init_game_loop() {
	float deltaTime = 0.0f;
	
	running = true;

	while (running) {
		SDL_Event event;
		auto frameStartTime = std::chrono::high_resolution_clock::now();

		while (SDL_PollEvent(&event)) {

			input_handler(event);
		}

		update(deltaTime);
		render();

		auto frameStopTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(frameStopTime - frameStartTime).count();
	}
}

void Game::stop_game_loop() {
	running = false;
}

