#include "ofMain.h"
#pragma once

class Coin {
private:
    ofImage coin_;
    ofVec2f coin_pos_;
    ofVec2f screen_dim_;
    double size_;
    bool is_taken_;
    
public:
    Coin();
    ~Coin();
    double getCoinSize();
    ofImage getCoinImg();
    ofVec2f getCoinPos();
    bool isTaken();
    void update();
    void resize(int h);
    void setTaken(bool a);
    void coinTaken();
};
