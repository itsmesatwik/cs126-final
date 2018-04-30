#include "Coin.h"
const double size_ratio_ = 0.1;

Coin::Coin() {
    is_taken_ = false;
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    screen_dim_.set(width, height);
    size_ = size_ratio_*height;
    coin_.load("coin.png");
    coin_pos_.set(1000 + ((double)(rand()%1000)), 0 + ((double)(rand()%700))); // Taken from http://en.cppreference.com/w/cpp/numeric/random/rand
    //coin_pos_.set(500, 500);
}

Coin::~Coin() {}

ofImage Coin::getCoinImg() {
    return coin_;
}

ofVec2f Coin::getCoinPos() {
    return coin_pos_;
}

void Coin::update() {
    coin_pos_.set(coin_pos_.x - 20, coin_pos_.y);
}

void Coin::resize(int h) {
    double height = screen_dim_.y;
    size_ = size_ * (double)(height/h);
}

double Coin::getCoinSize() {
    return size_;
}

bool Coin::isTaken() {
    return is_taken_;
}

void Coin::setTaken(bool a) {
    is_taken_ = a;
}

void Coin::coinTaken() {
    coin_pos_.set(0,0);
}
