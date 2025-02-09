#include "Character.hpp"

void Character::update_sprite(int dir) {
	int unit = 32;
	SDL_Rect rect = { unit * spriteFrame, unit * dir, unit, unit };
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
	update_sprite(SpriteDirection::UP);
}
