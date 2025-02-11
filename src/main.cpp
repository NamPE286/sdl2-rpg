#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include "game/game.hpp"

int SDL_main(int argc, char* argv[]) {
	Game game;

	try {
		game.init_game_loop();
	}
	catch (std::runtime_error err) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occured", err.what(), NULL);
	}

	return 0;
}
