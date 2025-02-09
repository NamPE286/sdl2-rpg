#include "Map.hpp"
#include <SDL2/SDL_image.h>

Map::Map(SDL_Renderer* renderer): renderer(renderer) {
	cobblestone = new Image(renderer, "assets/textures/terrain/cobblestone.png");
}