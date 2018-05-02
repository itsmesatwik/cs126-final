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
#include "Coin.h"

// Game State Enums
enum GameState {
    START = 0,
    SHOP,
    INVENTORY,
    RUNNING,
    PAUSED,
    FINISHED
};

class ofApp : public ofBaseApp {
private:
    std::vector<int> scores_;
    std::vector<std::string> inventory_;
    int pillars_cleared_ = 0;
    int coins_collected_ = 0;
    int total_coins_ = 0;
    GameState game_state_ = START;
    Bird birdy_;
    Pillar game_pillar_;
    Coin coin1_;
    Coin coin2_;
    Coin coin3_;
    ofTrueTypeFont game_font_;
    ofImage gameStart_;
    ofImage gameOver_;
    ofImage background_;
    string skin1, skin2, skin3;
    ofSoundPlayer trips_;
    ofSoundPlayer fly_;
    ofSoundPlayer die_;
    ofSoundPlayer die2_;
    ofSoundPlayer backsound_;
    ofSoundPlayer coin_;
    ofSoundPlayer pillar_clear_;
    
    // Private functions to render game states
    void drawBird();
    void drawPillar();
    void drawCoin(Coin coin);
    void drawGameStart();
    void drawGamePaused();
    void drawGameOver();
    void drawScore();
    void drawShop();
    void drawInventory();
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
