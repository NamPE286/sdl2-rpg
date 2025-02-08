#include "ScrollingBG.hpp"

#include "../common.h"

ScrollingBG::ScrollingBG(std::shared_ptr<Image> img) : img(img) {}

void ScrollingBG::update(float deltaTime) {
	pos += velocity * deltaTime;

	SDL_Rect rect = { pos.x, pos.y, 0, 0 };
	
	SDL_QueryTexture(img->texture, NULL, NULL, &rect.w, &rect.h);

	if (rect.x > 0) {
		rect.x = 0;
	}
	else if (rect.x < WINDOW_WIDTH - rect.w) {
		rect.x = WINDOW_WIDTH - rect.w;
	}

	if (rect.y > 0) {
		rect.y = 0;
	}
	else if (rect.y < WINDOW_HEIGHT - rect.h) {
		rect.y = WINDOW_HEIGHT - rect.h;
	}

	img->update(&rect);
}

void ScrollingBG::on_key_down(SDL_Event& event) {
	switch (event.key.keysym.sym) {
	case SDLK_RIGHT:
		velocity.x = -1;
		break;
	case SDLK_LEFT:
		velocity.x = 1;
		break;
	case SDLK_UP:
		velocity.y = 1;
		break;
	case SDLK_DOWN:
		velocity.y = -1;
		break;
	}
}

void ScrollingBG::on_key_up(SDL_Event& event) {
	velocity.x = velocity.y = 0;
}