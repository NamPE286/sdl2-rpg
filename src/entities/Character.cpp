#include "Character.hpp"
#include "cmath"
#include "../common.h"

const float MOVE_SPEED = 0.1f;
const int spriteFrame[4] = { 1, 2, 1, 0 };

void Character::render() {
	SDL_Rect rect = { 32 * spriteFrame[sprite.frameIndex], 32 * sprite.direction, 32, 32 };
	sprite.img->render(pos.x, pos.y, &rect);
}

void Character::stop_movement() {
	velocity = Vec2(0, 0);
	sprite.frameTime = 0;
	sprite.frameIndex = 0;
	moving = false;
}

Character::Character(SDL_Renderer* renderer, std::string filePath, Vec2 pos, float scale):
	renderer(renderer), pos(pos)
{
	sprite.img = new Image(renderer, filePath, 0, 0, scale);
	sprite.scale = scale;
}

Character::~Character() {
	delete sprite.img;
}

void Character::update(float deltaTime) {
	pos += velocity * deltaTime;

	if (isKeyDown) {
		stopPos = pos;

		switch (sprite.direction) {
		case SpriteDirection::UP:
			stopPos.y = std::floor(stopPos.y / 32) * 32;
			break;
		case SpriteDirection::DOWN:
			stopPos.y = std::ceil(stopPos.y / 32) * 32;
			break;
		case SpriteDirection::LEFT:
			stopPos.x = std::floor(stopPos.x / 32) * 32;
			break;
		case SpriteDirection::RIGHT:
			stopPos.x = std::ceil(stopPos.x / 32) * 32;
			break;
		}
	}
	else {
		switch (sprite.direction) {
		case SpriteDirection::UP:
			if (pos.y < stopPos.y) {
				pos.y = stopPos.y;
				stop_movement();
			}

			break;
		case SpriteDirection::DOWN:
			if (pos.y > stopPos.y) {
				pos.y = stopPos.y;
				stop_movement();
			}

			break;
		case SpriteDirection::LEFT:
			if (pos.x < stopPos.x) {
				pos.x = stopPos.x;
				stop_movement();
			}

			break;
		case SpriteDirection::RIGHT:
			if (pos.x > stopPos.x) {
				pos.x = stopPos.x;
				stop_movement();
			}

			break;
		}
	}

	stopPos.x = __max(0, stopPos.x);
	stopPos.y = __max(0, stopPos.y);

	stopPos.x = __min((WINDOW_WIDTH / 32) * 32, stopPos.x);
	stopPos.y = __min((WINDOW_WIDTH / 32) * 32, stopPos.y);

	if (velocity != Vec2(0, 0)) {
		sprite.frameTime += deltaTime;
	}

	if (sprite.frameTime > 200) {
		sprite.frameTime = 0;
		sprite.frameIndex = (sprite.frameIndex + 1) % 4;
	}
}

void Character::on_key_down(SDL_Event& event) {
	auto key = event.key.keysym.sym;

	if (moving) {
		return;
	}

	if (
		key == SDLK_UP ||
		key == SDLK_DOWN ||
		key == SDLK_LEFT ||
		key == SDLK_RIGHT
	) {
		if (key != lastKey) {
			sprite.frameIndex = 0;
		}

		lastKey = key;
		moving = true;
		isKeyDown = true;
	}

	switch (key) {
	case SDLK_UP:
		velocity.x = 0;
		velocity.y = -MOVE_SPEED;
		sprite.direction = SpriteDirection::UP;

		break;
	case SDLK_DOWN:
		velocity.x = 0;
		velocity.y = MOVE_SPEED;
		sprite.direction = SpriteDirection::DOWN;

		break;
	case SDLK_LEFT:
		velocity.x = -MOVE_SPEED;
		velocity.y = 0;
		sprite.direction = SpriteDirection::LEFT;

		break;
	case SDLK_RIGHT:
		velocity.x = MOVE_SPEED;
		velocity.y = 0;
		sprite.direction = SpriteDirection::RIGHT;

		break;
	}
}

void Character::on_key_up(SDL_Event& event) {
	auto key = event.key.keysym.sym;

	if (
		key == SDLK_UP ||
		key == SDLK_DOWN ||
		key == SDLK_LEFT ||
		key == SDLK_RIGHT
	) {
		isKeyDown = false;
	}
}
