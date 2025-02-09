#include "Character.hpp"

const float MOVE_SPEED = 0.2f;
const int spriteFrame[4] = { 0, 1, 2, 1 };

void Character::update_sprite(int dir) {
	int unit = 32;
	SDL_Rect rect = { unit * spriteFrame[spriteFrameIndex], unit * dir, unit, unit };
	sprite->update(pos.x, pos.y, &rect);
}

Character::Character(SDL_Renderer* renderer, std::string filePath, Vec2 pos, float scale):
	renderer(renderer), pos(pos), scale(scale)
{
	sprite = new Image(renderer, filePath, 0, 0, scale);
}

Character::~Character() {
	delete sprite;
}

void Character::update(float deltaTime) {
	update_sprite(direction);

	pos += velocity * deltaTime;

	if (velocity != Vec2(0, 0)) {
		spriteFrameTime += deltaTime;
	}

	if (spriteFrameTime > 200) {
		spriteFrameTime = 0;
		spriteFrameIndex = (spriteFrameIndex + 1) % 4;
	}
}

void Character::on_key_down(SDL_Event& event) {
	auto key = event.key.keysym.sym;

	if (
		key == SDLK_UP ||
		key == SDLK_DOWN ||
		key == SDLK_LEFT ||
		key == SDLK_RIGHT
	) {
		if (key != lastKey) {
			spriteFrameIndex = 0;
		}

		lastKey = key;
	}

	switch (key) {
	case SDLK_UP:
		velocity.x = 0;
		velocity.y = -MOVE_SPEED;
		direction = SpriteDirection::UP;

		break;
	case SDLK_DOWN:
		velocity.x = 0;
		velocity.y = MOVE_SPEED;
		direction = SpriteDirection::DOWN;

		break;
	case SDLK_LEFT:
		velocity.x = -MOVE_SPEED;
		velocity.y = 0;
		direction = SpriteDirection::LEFT;

		break;
	case SDLK_RIGHT:
		velocity.x = MOVE_SPEED;
		velocity.y = 0;
		direction = SpriteDirection::RIGHT;

		break;
	}
}

void Character::on_key_up(SDL_Event& event) {
	if (event.key.keysym.sym == lastKey) {
		velocity.x = velocity.y = 0;
		spriteFrameTime = 0;
	}
}
