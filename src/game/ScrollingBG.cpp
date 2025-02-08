#include "ScrollingBG.hpp"

ScrollingBG::ScrollingBG(std::shared_ptr<Image> img) : img(img) {
	rect = img->rect;
}

void ScrollingBG::update(float deltaTime) {
	img->update(&rect);
}

void ScrollingBG::on_key_down(SDL_Event& event) {

}

void ScrollingBG::on_key_up(SDL_Event& event) {

}