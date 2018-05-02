#include "ofApp.h"
#include <iostream>

void ofApp::setup() {
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0)));
    ofSetBackgroundAuto(true);
    background_.load("background.png");
    gameOver_.load("Gameover.png");
    gameStart_.load("start_screen.jpg");
    trips_.load("Triple.mp3");
    backsound_.load("backsound.mp3");
    game_font_.load("Flappy-Bird.ttf",50);
    die_.load("die.mp3");
    die2_.load("die2.mp3");
    fly_.load("fly.wav");
    coin_.load("coin.wav");
    pillar_clear_.load("pillar_clear.flac");
    backsound_.play();
}


void ofApp::update() {
    if (game_state_ == RUNNING) {
        if (birdy_.isDead(game_pillar_)) {
            die2_.play();
            //die_.play();
            game_state_ = FINISHED;
            scores_.push_back(pillars_cleared_ + coins_collected_);
            total_coins_ += coins_collected_;
            return;
        }
        birdy_.update();
        game_pillar_.update();
        coin1_.update();
        coin2_.update();
        coin3_.update();
        
        // Checking if the bird has passed the pillar
        
        ofVec2f pillar_pos = game_pillar_.getPillarPos();
        int pillar_x = pillar_pos.x;
        
        if (pillar_x <= -5) {
            game_pillar_ = Pillar();
        }
        ofVec2f coin1_cor = coin1_.getCoinPos();
        ofVec2f coin2_cor = coin2_.getCoinPos();
        ofVec2f coin3_cor = coin3_.getCoinPos();
        
        if (coin1_cor.x <= 10)
            coin1_ = Coin();
        
        if (coin2_cor.x <= 10)
            coin2_ = Coin();
        
        if (coin3_cor.x <= 10)
            coin3_ = Coin();
        
        ofVec2f bird_pos = birdy_.getBirdPos();
        ofVec2f bird_s = birdy_.getBirdSize();
        double bird_size_ = bird_s.x;

        // Play "Oh baby a triple"
        if (bird_pos.x  >= pillar_x +100 && bird_pos.x <= pillar_x + 120) {
            pillars_cleared_++;
            pillar_clear_.play();
            if (pillars_cleared_ == 3)
                trips_.play();
        }

        ofRectangle bird_box(bird_pos.x + 7, bird_pos.y + 7, bird_size_, bird_size_);
        ofRectangle coin1_pos(coin1_cor, coin1_.getCoinSize() - 10, coin1_.getCoinSize() - 10);
        ofRectangle coin2_pos(coin2_cor, coin1_.getCoinSize() - 10, coin1_.getCoinSize() - 10);
        ofRectangle coin3_pos(coin3_cor, coin1_.getCoinSize() - 10, coin1_.getCoinSize() - 10);
        
        ofVec2f pillar_size = game_pillar_.getPillarSize();
        ofRectangle pillar_rect1_(pillar_pos.x, pillar_pos.y, pillar_size.x, pillar_size.y);
        ofRectangle pillar_rect2_ (pillar_pos.x, 0, pillar_size.x, ofGetHeight() - pillar_size.y - 200);
        
        if(coin1_pos.intersects(pillar_rect1_) || coin1_pos.intersects(pillar_rect2_))
            for (int i = 0; i < 3; i++)
                coin1_.update();
        if(coin2_pos.intersects(pillar_rect1_) || coin2_pos.intersects(pillar_rect2_))
            for (int i = 0; i < 3; i++)
                coin2_.update();
        if(coin3_pos.intersects(pillar_rect1_) || coin3_pos.intersects(pillar_rect2_))
            for (int i = 0; i < 3; i++)
                coin3_.update();
        
        
        if (coin1_pos.intersects(coin2_pos))
            for (int i = 0; i < 3; i++)
                coin1_.update();
        
        if (coin1_pos.intersects(coin3_pos))
            for (int i = 0; i < 3; i++)
                coin3_.update();
        if (coin2_pos.intersects(coin3_pos))
            for (int i = 0; i < 3; i++)
                coin3_.update();
        
        if (coin1_pos.intersects(bird_box)) {
            coin1_.setTaken(true);
            coin1_.coinTaken();
            coins_collected_++;
            coin1_ = Coin();
            coin_.play();
        }
        if (coin2_pos.intersects(bird_box)) {
            coin2_.setTaken(true);
            coin2_.coinTaken();
            coins_collected_++;
            coin2_ = Coin();
            coin_.play();
        }
        if (coin3_pos.intersects(bird_box)) {
            coin3_.setTaken(true);
            coin3_.coinTaken();
            coins_collected_++;
            coin3_ = Coin();
            coin_.play();
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
    if (game_state_ == START) {
        drawGameStart();
        return;
    }
    if (game_state_ == SHOP) {
        drawShop();
        return;
    }
    if (game_state_ == INVENTORY) {
        drawInventory();
        return;
    }
    if (game_state_ == RUNNING) {
        background_.draw(0,0, ofGetWidth()+20, ofGetHeight()+20);
        drawPillar();
        drawBird();
        if (!coin1_.isTaken()) {
            drawCoin(coin1_);
        }
        if (!coin2_.isTaken()) {
            drawCoin(coin2_);
        }
        if (!coin3_.isTaken()) {
            drawCoin(coin3_);
        }
    }
    if (game_state_ == FINISHED) {
        background_.draw(0,0, ofGetWidth()+20, ofGetHeight()+20);
        drawGameOver();
        drawScore();
    }
    if (game_state_ == PAUSED) {
        background_.draw(0,0, ofGetWidth()+20, ofGetHeight()+20);
        drawGamePaused();
        drawScore();
    }
}


void ofApp::keyPressed(int key){
    int upper_key = toupper(key);

    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }

    if (game_state_ == INVENTORY) {
        if(upper_key == 'A' && inventory_.size() > 0) {
            birdy_.setSkin("blu_.png");
            birdy_.setSkinOn(true);
        }
        else if (upper_key == 'B' && inventory_.size() > 1) {
            birdy_.setSkin("chic_.png");
            birdy_.setSkinOn(true);
        }
        else if (upper_key == 'C' && inventory_.size() > 2) {
            birdy_.setSkin("super_bird.png");
            birdy_.setSkinOn(true);
        }
        else {
            game_state_ = START;
            return;
        }
    }

    if (game_state_ == SHOP) {
        if (upper_key == 'H') {
            total_coins_ += 150;
            return;
        }
        if (upper_key == 'A') {
            if (total_coins_ >= 35) {
                inventory_.push_back("blu_.png");
            }
            return;
        }
        else if (upper_key == 'B') {
            if (total_coins_ >= 70) {
                inventory_.push_back("chic_.png");
            }
            return;
        }
        else if (upper_key == 'C') {
            if (total_coins_ >= 150) {
                inventory_.push_back("super_bird.png");
            }
            return;
        }
        else {
            game_state_ = START;
            return;
        }


    }
    if (game_state_ == START) {
        if (upper_key == 'S') {
            game_state_ = SHOP;
            return;
        }
        else if (upper_key == 'I') {
            game_state_ = INVENTORY;
            return;
        }
        else {
            game_state_ = RUNNING;
            return;
        }
    }
    
    if (upper_key == 'P' && game_state_ != FINISHED) {
        // Pause or unpause
        game_state_ = (game_state_ == RUNNING) ? PAUSED : RUNNING;
    }
    else if (game_state_ == RUNNING)
    {
        if (upper_key == 'Z') {
            birdy_.setDirection(UP);
            fly_.play();
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
    coin1_ = Coin();
    coin2_ = Coin();
    coin3_ = Coin();
    pillars_cleared_ = 0;
    coins_collected_ = 0;
    game_state_ = START;
    die_.stop();
    die2_.stop();
    backsound_.play();
}


void ofApp::windowResized(int w, int h){
    birdy_.resize(w, h);
    game_pillar_.resize(w, h);
}


void ofApp::drawGameStart() {
    string message = "Press 'S' for Shop Press 'I' for Inventory";
    gameStart_.draw(0,0,ofGetWindowWidth() + 30, ofGetWindowHeight() + 40);
    game_font_.drawString(message, ofGetWindowWidth()*0.05, ofGetWindowHeight()*0.35);
}

void ofApp::drawBird() {
    ofImage bird_ = birdy_.getIcon();
    ofVec2f bird_pos = birdy_.getBirdPos();
    ofVec2f bird_size = birdy_.getBirdSize();
    game_font_.drawString(std::to_string(pillars_cleared_), ofGetWindowWidth() / 2 - 20, 150);
    if (birdy_.getDirection() == UP && !birdy_.getSkinOn())
        bird_.draw(bird_pos.x - 30, bird_pos.y, bird_size.x + 35, bird_size.y);
    else
        bird_.draw(bird_pos.x,bird_pos.y,bird_size.x,bird_size.y);
}

void ofApp::drawPillar() {
    ofImage pillar_ = game_pillar_.getRect();
    ofImage pillar2_ = game_pillar_.getRect();
    pillar2_.rotate90(2);
    ofVec2f rect_pos = game_pillar_.getPillarPos();
    ofVec2f rect_size = game_pillar_.getPillarSize();
    pillar_.draw(rect_pos.x, rect_pos.y, rect_size.x, rect_size.y);
    pillar2_.draw(rect_pos.x, 0, rect_size.x, ofGetHeight() - rect_size.y - ofGetWindowHeight()*0.35);
}

void ofApp::drawGameOver() {
    backsound_.stop();
    gameOver_.draw(ofGetWindowWidth()/2 - 400, ofGetWindowHeight()/2 - 200, 800, 600);
    string lose_message = "You Lost! Final Score : " + std::to_string(pillars_cleared_ + coins_collected_);
    game_font_.drawString(lose_message, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() / 2);
}

void ofApp::drawCoin(Coin coin) {
    ofImage coin_ = coin.getCoinImg();
    ofVec2f coin_pos = coin.getCoinPos();
    double size_ = coin.getCoinSize();
    coin_.draw(coin_pos, size_, size_);
    
}

void ofApp::drawGamePaused() {
    string pause_message = "P to Unpause!";
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void ofApp::drawScore() {
    std::sort(scores_.rbegin(), scores_.rend());
    string message = "Total Coins : " + std::to_string(total_coins_) + "\nHigh Score  : " + std::to_string(scores_[0]);
    game_font_.drawString(message, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() / 2 - 150);
}

void ofApp::drawShop() {
    background_.draw(0,0, ofGetWindowWidth()+20, ofGetWindowHeight()+20);
    string message = "SHOP";
    game_font_.drawString(message, ofGetWindowWidth() / 2 - 50, 50);
    ofImage skin, skin2, skin3;
    skin.load("blu_.png");
    skin.draw(ofGetWindowWidth() / 2 - ofGetWindowWidth()*0.27 - 75, ofGetWindowHeight() / 2, ofGetWindowHeight()*0.2, ofGetWindowHeight()*0.2);
    skin2.load("chic_.png");
    skin2.draw(ofGetWindowWidth() / 2 - 75, ofGetWindowHeight() / 2, ofGetWindowHeight()*0.2, ofGetWindowHeight()*0.2);
    skin3.load("super_bird.png");
    skin3.draw(ofGetWindowWidth() /2 + ofGetWindowWidth()*0.27 - 75, ofGetWindowHeight() / 2, ofGetWindowHeight()*0.2, ofGetWindowHeight()*0.2);
    ofImage coin_ = coin1_.getCoinImg();
    coin_.draw(ofGetWindowWidth() / 2 - ofGetWindowWidth()*0.32, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28, ofGetWindowHeight()*0.1, ofGetWindowHeight()*0.1);
    coin_.draw(ofGetWindowWidth() / 2  - 30, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28, ofGetWindowHeight()*0.1, ofGetWindowHeight()*0.1);
    coin_.draw(ofGetWindowWidth() / 2 + ofGetWindowWidth()*0.29, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28, ofGetWindowHeight()*0.1, ofGetWindowHeight()*0.1);
    game_font_.drawString("\n35\n\nA",ofGetWindowWidth() / 2 - ofGetWindowWidth()*0.30, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28);
    game_font_.drawString("\n70\n\nB",ofGetWindowWidth() / 2 - 20, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28);
    game_font_.drawString("\n150\n\nC",ofGetWindowWidth() / 2 + ofGetWindowWidth()*0.31, ofGetWindowHeight() / 2 + ofGetWindowHeight()*0.28);
}

void ofApp::drawInventory() {
    background_.draw(0,0, ofGetWindowWidth()+20, ofGetWindowHeight()+20);
    string message = "INVENTORY";
    game_font_.drawString(message, ofGetWindowWidth() / 2 - 50, 50);
    int width = ofGetWindowWidth() * 0.2;
    int height = ofGetWindowHeight()/4;
    int factor = height;
    for (auto elem : inventory_) {
        ofImage inv;
        inv.load(elem);
        inv.draw(width, height, ofGetWindowHeight()*0.1, ofGetWindowHeight()*0.1);
        height += factor;
    }
    height = factor;
    game_font_.drawString("A", width *2, height);
    height += factor;
    game_font_.drawString("B", width *2, height);
    height += factor;
    game_font_.drawString("C", width *2, height);
}
