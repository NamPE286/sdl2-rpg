#include "Game.hpp"
#include <stdexcept>
#include <string>
#include <chrono>
#include <iostream>
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

	img = new Image(renderer, "assets/anime.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
};

Game::~Game() {
	delete img;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
};

void Game::update(float deltaTime) {
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);

	img->update();
}

void Game::render() {
	SDL_RenderPresent(renderer);
}

void Game::input_handler(SDL_Event& event) {
	if (event.type == SDL_QUIT) {
		stop_game_loop();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
		stop_game_loop();
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

