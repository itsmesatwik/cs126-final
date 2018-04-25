#pragma once

#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>

#include "ofMain.h"
#include "ofApp.h"

#include "Bird.h"
#include "Pillar.h"

// Game State Enums
enum GameState {
    RUNNING = 0,
    PAUSED,
    FINISHED
};

class ofApp : public ofBaseApp {
private:
    std::vector<int> scores_;
    int pillars_cleared_;
    GameState game_state_ = RUNNING;
    Bird birdy_;
    Pillar game_pillar_;
    bool update_ = true;
    
    // Private functions to render game states
    void drawBird();
    void drawPillar();
    void drawGamePaused();
    void drawGameOver();
    void drawScore();
    void reset();
    
public:
    // Function for initial setup
    void setup();
    
    // Game loop functions
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);
		
};
