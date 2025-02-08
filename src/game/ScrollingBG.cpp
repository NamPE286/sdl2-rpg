#include "ScrollingBG.hpp"

ScrollingBG::ScrollingBG(std::shared_ptr<Image> img) : img(img) {
	rect = img->rect;
}

void ScrollingBG::update() {
	img->update(&rect);
}