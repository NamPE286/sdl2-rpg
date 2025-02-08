#include "Game.hpp"
#include <stdexcept>
#include <string>
#include "../common.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("Failed to initialize SDL. SDL error: " + std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow("SDL Tutorial", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window. SDL error: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr) {
		throw std::runtime_error("Failed to create renderer. SDL error: " + std::string(SDL_GetError()));
	}
};

Game::~Game() {

};

void Game::update() {

}

void Game::draw() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


