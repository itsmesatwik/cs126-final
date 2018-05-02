#include "ofMain.h"
#include "Pillar.h"
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
	static const double size_ratio_;
	bool skinOn = false;
	ofVec2f bird_size_;
	ofVec2f bird_pos_;

public:
	Bird();
	~Bird();
	ofVec2f getBirdSize() const;
    ofImage getIcon() const;
    ofVec2f getBirdPos() const;
	bool isDead(Pillar pillar) const;
	void update();
	void resize(int w, int h);
	BirdDirection getDirection() const;
	void setDirection(BirdDirection newDirection);
	void setSkin(std::string skinPath);
	void setSkinOn(bool a);
	bool getSkinOn();
};
