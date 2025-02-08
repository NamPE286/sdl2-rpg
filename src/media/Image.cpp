#include "Image.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

Image::Image(SDL_Renderer* renderer, std::string filePath, int x, int y, int w, int h): renderer(renderer) {
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	if (texture == nullptr) {
		throw std::runtime_error("Failed to load " + filePath);
	}

	rect.x = x, rect.y = y;

	if (w == NULL && h == NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}
	else {
		rect.w = w, rect.h = h;
	}
}

Image::~Image() {
	SDL_DestroyTexture(texture);
}

void Image::update() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
