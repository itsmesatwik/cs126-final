#include "Bird.h"
const double Bird::size_ratio_ = 0.1;

Bird::Bird() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dim_.set(width, height);
	double bird_height_ = size_ratio_*height;
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

ofVec2f Bird::getBirdSize() const {
    return bird_size_;
}

bool Bird::isDead(Pillar screen_pillar_) const {
	if (bird_size_.y > ofGetWindowHeight())
		return true;
    ofRectangle bird_rect_(bird_pos_.x, bird_pos_.y, bird_size_.x, bird_size_.y);
	if (screen_pillar_.getRect().intersects(bird_rect_))
        return true;
    return false;
}

BirdDirection Bird::getDirection() const {
    return current_direction_;
}

void Bird::setDirection(BirdDirection newDirection) {
    current_direction_ = newDirection;
}

void Bird::resize(int w, int h) {
    
}
