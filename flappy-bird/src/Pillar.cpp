#include "Pillar.h"
#include <cstdlib>
/*
  Default Constructor
  Randomly sets the height of the pillar
 */
Pillar::Pillar() {
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    screen_dim_.set(width, height);
    double pillar_height_ =  height * (0.15 + ((double)(rand()%1000000)/2000000)); // Taken from http://en.cppreference.com/w/cpp/numeric/random/rand
    pillar_size_.set(100, pillar_height_);
    pillar_pos_.set(1500, height - pillar_size_.y);
    pillar_.load("pillar.png");
}

Pillar::~Pillar() {}

ofVec2f Pillar::getPillarSize() const {
    return pillar_size_;
}

ofVec2f Pillar::getPillarPos() const {
    return pillar_pos_;
}

void Pillar::update() {
    pillar_pos_.set(pillar_pos_.x - 20, pillar_pos_.y);
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

ofImage Pillar::getRect() const {
    return pillar_;
}

