#include "Bird.h"
const double Bird::size_ratio_ = 0.1;

Bird::Bird() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dim_.set(width, height);
	double bird_height_ = size_ratio_*height;
	bird_size_.set(bird_height_,bird_height_);
	current_direction_ = DOWN;
	//bird_icon_.load("./default_bird_logo.png");
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

ofImage Bird::getIcon() const {
    return bird_icon_;
}
ofVec2f Bird:: getBirdPos() const {
    return bird_pos_;
}

ofVec2f Bird::getBirdSize() const {
    return bird_size_;
}

bool Bird::isDead(Pillar screen_pillar_) const {
	if (bird_pos_.x > screen_dim_.x)
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
    double width = screen_dim_.x;
    double height = screen_dim_.y;
    double new_bird_ = (bird_size_.x/height) * h;
    bird_size_.set(new_bird_, new_bird_);
    bird_pos_.set((bird_pos_.x/width)*w, (bird_pos_.y/height)*h);
    screen_dim_.set(w, h);
}
