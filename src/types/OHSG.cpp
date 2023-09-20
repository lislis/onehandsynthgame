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
    state = GameState::loop;
    wave = WaveType::sine;
    ship = new Ship(wave);
    em = new EnemyManager();
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
        //case GameState::tutorial:
        //    draw_tutorial();
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
    float space_top = 38;
    ofDrawBitmapString("Score: " + to_string(score), 30, space_top);
    ofDrawBitmapString("Wave: ", 110, space_top);
    
    for (int i = sine; i <= sawtooth; i++) {
        if (wave == i) {
            ofPushStyle();
            ofSetColor(choose_color_by_wave(wave));
            ofDrawCircle(170 + (i * 30), 32, 14);
            ofPopStyle();
        }
        ofDrawBitmapString(i, 167 + (i * 30), space_top);
    }
    
}

void OHSG::draw_intro() {
    ofSetColor(FONT_COLOR);
    ofDrawBitmapString("One Hand Synth Game", 300, ofGetHeight() / 2 - 30);
    ofDrawBitmapString("Press <space> to continue", 300, ofGetHeight() / 2);
}

void OHSG::draw_tutorial() {}

void OHSG::draw_over() {
    ofSetColor(FONT_COLOR);
    ofDrawBitmapString("It's over now", 300, ofGetHeight() / 2 - 30);
    ofDrawBitmapString("Press <space> to continue", 300, ofGetHeight() / 2);
}

void OHSG::handle_key_released(int key) {
    //cout << key << endl;
    
    if (state == GameState::intro) {
        if (key == 32) set_state(GameState::loop);
    }
    if (state == GameState::over) {
        if (key == 32) set_state(GameState::intro);
    }
    if (state == GameState::loop) {
        if (key == 32) {
            ship->shoot();
        } else {
            wave = choose_wave_by_key(key);
        }
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
