#include "ofApp.h"
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0)));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (game_state_ == RUNNING) {
        birdy_.update();
        game_pillar_.update();
        
        if (birdy_.isDead()) {
            game_state_ = FINISHED;
            scores_.push_back(pillars_cleared_);
        }
    }
}

/*
 Draws the current state of the game with the following logic
 1. If the game is paused draw the pause screen and high scores
 2. If the game is finished draw the game over screen, final score and high scores
 3. Draw the current position of the food and of the snake
 */

void ofApp::draw(){
    if (game_state_ == FINISHED) {
        drawGameOver();
        drawScore();
    }
    if (game_state_ == PAUSED) {
        drawGamePaused();
        drawScore();
    }
    drawPillar();
    drawBird();
}

/*
 Function that handles actions based on user key presses
 1. if key == F12, toggle fullscreen
 2. if key == p and game is not over, toggle pause
 3. if game is in progress handle WASD action
 4. if key == r and game is over reset it
 
 Space logic:
 Let dir be the direction that corresponds to a key
 if current direction is not dir (Prevents key spamming to rapidly update the snake)
 and current_direction is not opposite of dir (Prevents the snake turning and eating itself)
 Update direction of snake and force a game update (see ofApp.h for why)
 */
void ofApp::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    
    int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'P' && game_state_ != FINISHED) {
        // Pause or unpause
        game_state_ = (game_state_ == RUNNING) ? PAUSED : RUNNING;
    }
    else if (game_state_ == RUNNING)
    {
        if (upper_key == 'Z') {
            birdy_.setDirection(UP);
            update();
        }
    }
    else if (upper_key == 'R' && current_state_ == FINISHED) {
        reset();
    }

}

void ofApp::keyReleased(int key){
    int upper_key = toupper(key); // Standardize on upper case
    if (upper_key == 'Z') {
        birdy_.setDirection(DOWN);
        update();
    }
}

void ofApp::reset() {
    birdy_ = Bird();
    game_pillar_ = Pillar();
    pillars_cleared_ = 0;
    game_state_ = RUNNING;
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    birdy_.resize(w, h);
    game_pillar_.resize(w, h);
}

