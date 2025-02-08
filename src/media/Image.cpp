#include "Image.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

Image::Image(SDL_Renderer* renderer, std::string filePath, int x, int y, int w, int h, float scale): renderer(renderer) {
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	if (texture == nullptr) {
		throw std::runtime_error("Failed to load image " + filePath + ". Error: " + std::string(IMG_GetError()));
	}

	rect.x = x, rect.y = y;

	if (w == NULL && h == NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}
	else {
		rect.w = w, rect.h = h;
	}

	rect.w = static_cast<int>((float)rect.w * scale);
	rect.h = static_cast<int>((float)rect.h * scale);
}

Image::~Image() {
	SDL_DestroyTexture(texture);
}

void Image::update(SDL_Rect* pos) {
	if (pos == nullptr) {
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
	else {
		SDL_RenderCopy(renderer, texture, NULL, pos);
	}
}
