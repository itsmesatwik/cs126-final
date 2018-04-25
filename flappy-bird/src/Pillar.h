#include "ofMain.h"
#pragma once

class Pillar {
private:
    ofRectangle pillar_;
    ofVec2f screen_dim_;
    static const double size_ratio_;
    ofVec2f pillar_size_;
    ofVec2f pillar_pos_;
    
public:
    Pillar();
    ~Pillar();
    ofVec2f getPillarSize() const;
    ofVec2f getPillarPos() const;
    void update();
    void resize(int w, int h);
    ofRectangle getRect() const;
};
