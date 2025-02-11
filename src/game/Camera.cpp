#include "Camera.hpp"
#include "../common.h"

Camera::Camera(SDL_Renderer* renderer, SDL_Texture* texture, Vec2* pos, int w, int h):
	renderer(renderer), texture(texture), pos(pos), w(w), h(h)
{}

void Camera::render() {
	SDL_Rect rect = { pos->x - w / 2 + 16, pos->y - h / 2 + 16, w, h };

	rect.x = __max(0, rect.x);
	rect.x = __min(WINDOW_WIDTH - w, rect.x);

	rect.y = __max(0, rect.y);
	rect.y = __min(WINDOW_HEIGHT - h, rect.y);

	SDL_RenderCopy(renderer, texture, &rect, nullptr);
}
