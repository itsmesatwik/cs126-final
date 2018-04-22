#include "ofMain.h"
#pragma once

enum BirdDirection {
	UP = 0,
	DOWN
};

class Bird {
private:
	ofImage bird_icon_;
	BirdDirection current_direction_;
	ofVec2f screen_dim_;
	static const float size_ratio_;
	ofVec2f bird_size_;
	ofVec2f bird_pos_;

public:
	Bird();
	~Bird();
	ofVec2f getBirdSize() const;
	bool isDead();
	void update();
	void resize(int w, int h);
	BirdDirection getDirection() const;
	void setDirection(BirdDirection newDirection);
};
