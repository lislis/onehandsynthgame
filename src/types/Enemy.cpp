//
//  Enemy.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 01.09.23.
//

#include "Enemy.hpp"
#include "config.h"

Enemy::Enemy(int wave_variant_index, ofVec2f position, float direction) {
    wave = assign_wave(wave_variant_index);
    vel = ofVec2f(2.0 * direction, 0);
    pos = position;
    active = true;
}

Enemy::~Enemy() {
}
    
void Enemy::draw(const WaveType& w) {
    ofPushStyle();
    if (w == wave) {
        ofSetColor(choose_color_by_wave(wave));
    } else {
        ofSetColor(ENEMY_INACTIVE_COLOR);
    }
    
    draw_wave(wave, pos);
    ofPopStyle();
}

WaveType& Enemy::get_wave() {
    return wave;
}
