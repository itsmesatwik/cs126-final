#include "ofApp.h"
#include <iostream>

void ofApp::setup(){
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0)));
}


void ofApp::update(){
    if (game_state_ == RUNNING) {
        birdy_.update();
        game_pillar_.update();
        
        // Checking if the bird has passed the pillar
        ofVec2f bird_pos = birdy_.getBirdPos();
        int bird_y = bird_pos.y;
        ofVec2f pillar_pos = game_pillar_.getPillarPos();
        int pillar_y = pillar_pos.y;
        if (bird_y > pillar_y) {
            pillars_cleared_++;
        }
        
        
        if (birdy_.isDead(game_pillar_)) {
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
    //drawBird();
}


void ofApp::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    
    int upper_key = toupper(key);
    
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
    else if (upper_key == 'R' && game_state_ == FINISHED) {
        reset();
    }

}

void ofApp::keyReleased(int key){
    int upper_key = toupper(key);
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


void ofApp::windowResized(int w, int h){
    birdy_.resize(w, h);
    game_pillar_.resize(w, h);
}


void ofApp::drawBird() {
    ofImage bird_ = birdy_.getIcon();
    ofVec2f bird_pos = birdy_.getBirdPos();
    ofVec2f bird_size = birdy_.getBirdSize();
    ofFill();
    ofSetColor(250, 15, 123);
    bird_.draw(0,0);
}

void ofApp::drawPillar() {
    ofRectangle pillar_ = game_pillar_.getRect();
    ofVec2f rect_pos = game_pillar_.getPillarPos();
    ofVec2f rect_size = game_pillar_.getPillarSize();
    ofFill();
    ofSetColor(0,240, 0);
    ofDrawRectangle(rect_pos, rect_size.x, rect_size.y);
}

void ofApp::drawGameOver() {
    string lose_message = "You Lost! Final Score: " + std::to_string(pillars_cleared_);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void ofApp::drawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}
void ofApp::drawScore() {
    std::sort(scores_.rbegin(), scores_.rend());
    string message = "\n";
    for (int i = 1; i <= scores_.size(); i++)
        message += "#" + std::to_string(i) + "  ~~~~~~ " + std::to_string(scores_[i-1]) + "\n";
    
    if (scores_.size() < 10) {
        for (int i = scores_.size() + 1; i <= 10; i++)
            message += "#" + std::to_string(i) + "  ~~~~~~ " + "0\n";
    }
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}
