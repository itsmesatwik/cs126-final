#include "Bird.h"
const float Bird::size_ratio_ = 10;

Bird::Bird() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dim_.set(width, height);
	float bird_height_ = size_ratio_*height;
	bird_size_.set(bird_height_,bird_height_);
	current_direction_ = DOWN;
	bird_icon_.load("../data/default_bird_logo.png");
	bird_pos_.set(width/2, height/2);
}

Bird::~Bird() {}

void Bird::update() {
	switch (current_direction_) {
		case UP:
			bird_pos_.set(bird_pos_.x, bird_pos_.y - bird_size_.y);
			break;
		case DOWN:
			bird_pos_.set(bird_pos_.x, bird_pos_.y + bird_size_.y);
			break;
	}
}

bool Bird::isDead(Pillar screen_pillar_) const {
	if (bird_size_.y > ofGetWindowHeight())
		return true;
    ofRectangle bird_rect_(bird_pos_.x, bird_pos_.y, bird_size_.x, bird_size_.y);
	if (screen_pillar_.getRect().intersects(bird_rect_))
        return true;
    return false;
}
