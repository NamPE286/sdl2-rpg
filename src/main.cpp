#include <iostream>
#include "game/game.hpp"

int SDL_main(int argc, char* argv[]) {
	Game game;

	game.init_game_loop();

	return 0;
}
