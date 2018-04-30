#include "Bird.h"
const double Bird::size_ratio_ = 0.1;

/*
 * Default Constructor
 * Sets the screen dimensions, bird position and bird size to the appropriate ratio
 *
 */
Bird::Bird() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dim_.set(width, height);
	double bird_height_ = size_ratio_*height;
	bird_size_.set(bird_height_,bird_height_);
    //setting current dir to DOWN by default because we want the bird to go down
	current_direction_ = DOWN;
    //load the bird image
	bird_icon_.load("default_bird_logo.png");
    //set the bird's position at the centre of the window
	bird_pos_.set(width/2 - 50, height/2);
}

Bird::~Bird() {}

void Bird::update() {
	switch (current_direction_) {
		case UP:
			bird_pos_.set(bird_pos_.x, bird_pos_.y - 30);
			break;
		case DOWN:
			bird_pos_.set(bird_pos_.x, bird_pos_.y + 20);
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
	if (bird_pos_.y > screen_dim_.y)
		return true;
    ofVec2f pillar_pos = screen_pillar_.getPillarPos();
    ofVec2f pillar_size = screen_pillar_.getPillarSize();
    ofRectangle pillar_rect1_(pillar_pos.x, pillar_pos.y, pillar_size.x, pillar_size.y);
    ofRectangle pillar_rect2_ (pillar_pos.x, 0, pillar_size.x, ofGetHeight() - pillar_size.y - ofGetWindowHeight()*0.35);
    ofRectangle bird_rect_(bird_pos_.x + 7, bird_pos_.y + 7, bird_size_.x - 10, bird_size_.y - 10);
	if (pillar_rect1_.intersects(bird_rect_) || pillar_rect2_.intersects(bird_rect_))
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
