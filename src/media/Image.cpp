#include "Image.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

Image::Image(
	SDL_Renderer* const renderer, 
	const std::string filePath, 
	int _w, 
	int _h, 
	float scale
): renderer(renderer), scale(scale) {
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	if (texture == nullptr) {
		throw std::runtime_error("Failed to load image " + filePath + ". Error: " + std::string(IMG_GetError()));
	}

	if (_w == NULL && _h == NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	}
	else {
		w = _w, h = _h;
	}

	w = static_cast<int>((float)w * scale);
	h = static_cast<int>((float)h * scale);
}

Image::~Image() {
	SDL_DestroyTexture(texture);
}

void Image::render(int x, int y, SDL_Rect* srcrect) {
	if (srcrect == nullptr) {
		SDL_Rect rect = { x, y, w, h };
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
	else {
		SDL_Rect rect = { x, y, int((float)srcrect->w * scale), int((float)srcrect->h * scale) };
		SDL_RenderCopy(renderer, texture, srcrect, &rect);
	}
}
