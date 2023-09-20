//
//  OHSG.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 02.08.23.
//

#include "ofMain.h"
#include "OHSG.hpp"
#include "config.h"
#include "stdio.h"

using namespace std;

OHSG::OHSG() {
    state = GameState::intro;
    wave = WaveType::sine;
    ship = new Ship(wave);
    em = new EnemyManager();
    start_time = ofGetElapsedTimef();
    delta_time = ofGetElapsedTimef();
}

OHSG::~OHSG() {
    delete ship;
    delete em;
}

int OHSG::get_state() {
    return state;
}

void OHSG::set_state(GameState new_state) {
    state = new_state;
    if (state == GameState::loop) {
        start_time = ofGetElapsedTimef();
        delete em;
        delete ship;
        ship = new Ship(wave);
        em = new EnemyManager();
    }
}

void OHSG::increase_score() {
    score += 1;
}

void OHSG::reset_score() {
    score = 0;
}

int OHSG::get_score() {
    return score;
}

void OHSG::update() {
    if (state == GameState::loop) {
        delta_time = ofGetElapsedTimef();
        if (delta_time - start_time > MAX_GAME_TIME +1) { // so we briefly see 0s
            set_state(GameState::over);
        }
        ship->update(wave);
        em->update();
        collision_check();
    }
}

void OHSG::draw() {
    draw_background();
    switch (state) {
        case GameState::intro:
            draw_intro();
            break;
        case GameState::tutorial:
            draw_tutorial();
            break;
        case GameState::loop:
            draw_entities();
            draw_level();
            draw_ui();
            break;
        case GameState::over:
            draw_over();
            break;
        default:
            break;
    }
}

void OHSG::draw_background() {
    ofBackground(BACKGROUND_COLOR);
}

void OHSG::draw_entities() {
    ship->draw(wave);
    em->draw(wave);
}

void OHSG::draw_level() {
    ofSetColor(BOUND_COLOR);
    ofSetLineWidth(6);
    ofDrawLine(0, UPPER_BOUND, ofGetWidth(), UPPER_BOUND);
    ofDrawLine(0, LOWER_BOUND, ofGetWidth(), LOWER_BOUND);
}

void OHSG::draw_ui() {
    ofSetColor(FONT_COLOR);
    float space_top = 40;
    ofDrawBitmapString("Time remaining: " + ofToString(MAX_GAME_TIME - int(delta_time - start_time)) + "s", 30, space_top);
    ofDrawBitmapString("Score: " + ofToString(score), 220, space_top);
    ofDrawBitmapString("Wave: ", 330, space_top);
    draw_options(380.0, space_top - 10);
}

void OHSG::draw_options(float _x, float _y) {
    for (int i = sine; i <= sawtooth; i++) {
        ofSetColor(FONT_COLOR);
        ofVec2f pos = ofVec2f(_x + (i * 40), _y);
        draw_wave(i, pos);
        
        if (wave == i) {
            ofPushStyle();
            ofSetColor(choose_color_by_wave(wave));
            ofDrawRectangle(pos.x -4, pos.y -4, WAVE_WIDTH + 8, WAVE_HEIGHT + 8);
            ofPopStyle();
        }
    }
}

void OHSG::draw_intro() {
    ofSetColor(FONT_COLOR);
    ofDrawBitmapString("One Hand Synth Game", 300, ofGetHeight() / 2 - 30);
    ofDrawBitmapString("Press <space> to continue", 300, ofGetHeight() / 2);
}

void OHSG::draw_tutorial() {
    ofSetColor(FONT_COLOR);
    ofDrawBitmapString("You need one hand to play this game.", 300, ofGetHeight() / 2 - 120);
    ofDrawBitmapString("Place the fingers of one hand on <y>* <u> <i> <l>", 300, ofGetHeight() / 2 - 90);
    ofDrawBitmapString("and the thumb on <space>.", 300, ofGetHeight() / 2 - 60);
    ofDrawBitmapString("Switch between wave forms with your fingers (try it now!).", 300, ofGetHeight() / 2 - 30);
    draw_options(300., ofGetHeight() / 2 - 10);
    ofDrawBitmapString("Use <space> to shoot enemies with the same wave type.", 300, ofGetHeight() / 2 + 50);
    ofDrawBitmapString("Press <space> to start the game", 300, ofGetHeight() / 2 + 80);
    
    ofDrawBitmapString("* <y> or <z> depending on keyboard layout", 300, ofGetHeight()  - 30);
    
}

void OHSG::draw_over() {
    ofSetColor(FONT_COLOR);
    ofDrawBitmapString("It's over and you made "+ ofToString(score) + " points", 300, ofGetHeight() / 2 - 30);
    ofDrawBitmapString("Press <space> to continue", 300, ofGetHeight() / 2);
}

void OHSG::handle_key_released(int key) {
    //cout << key << endl;
    switch(state) {
        case intro:
            if (key == SHOOT_KEY) set_state(GameState::tutorial);
            break;
        case tutorial:
            if (key == SHOOT_KEY) {
                set_state(GameState::loop);
            } else {
                wave = choose_wave_by_key(key);
            }
            break;
        case loop:
            if (key == SHOOT_KEY) {
                ship->shoot();
            } else {
                wave = choose_wave_by_key(key);
            }
            break;
        case over:
            if (key == SHOOT_KEY) set_state(GameState::intro);
            break;
    }
}

void OHSG::collision_check() {
    std::vector<Enemy*> enemies = em->get_enemies();
    std::vector<Projectile*> projectiles = ship->get_projectiles();
    
    for (std::vector<Enemy*>::iterator it_enem = enemies.begin(); it_enem != enemies.end(); it_enem++) {
        Enemy* enem = *it_enem;
        
        if (!enem->is_active())
            continue;
        
        for (std::vector<Projectile*>::iterator it_proj = projectiles.begin(); it_proj != projectiles.end(); it_proj++) {
            Projectile* proj = *it_proj;
            
            if (!proj->is_active())
                continue;
            
            if (enem->get_wave() != proj->get_wave())
                continue;
            
            ofVec2f epos = enem->get_position();
            ofVec2f ppos = proj->get_position();
            if ((epos.x + WAVE_WIDTH >= ppos.x
                && epos.x <= ppos.x + WAVE_WIDTH)
                && (epos.y + WAVE_HEIGHT >= ppos.y
                && epos.y <= ppos.y + WAVE_HEIGHT)) {
                enem->set_inactive();
                proj->set_inactive();
                score++;
            }
        }
        
    }
}
