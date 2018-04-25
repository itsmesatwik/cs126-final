#include "Pillar.h"
const double Pillar::size_ratio_ = 0.55;

/*
  Default Constructor
 */
Pillar::Pillar() {
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    screen_dim_.set(width, height);
    double pillar_height_ =  height * size_ratio_; // Taken from http://en.cppreference.com/w/cpp/numeric/random/rand
    pillar_size_.set(width * 0.1, pillar_height_);
    pillar_.set(pillar_pos_, pillar_size_.x, pillar_height_);
}

Pillar::~Pillar() {}

ofVec2f Pillar::getPillarSize() const {
    return pillar_size_;
}

ofVec2f Pillar::getPillarPos() const {
    return pillar_pos_;
}

void Pillar::update() {
    pillar_pos_.set(pillar_pos_.x - (screen_dim_.x * size_ratio_), pillar_pos_.y);
}

void Pillar::resize(int w, int h) {
    double width = screen_dim_.x;
    double height = screen_dim_.y;
    double new_pillar_h = (pillar_size_.y/height) * h;
    double new_pillar_w = (pillar_size_.x/width) * w;
    pillar_size_.set(new_pillar_w, new_pillar_h);
    pillar_pos_.set((pillar_pos_.x/width)*w,(pillar_pos_.y/height)*h);
    screen_dim_.set(w, h);
}

ofRectangle Pillar::getRect() const {
    return pillar_;
}

