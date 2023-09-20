//
//  Projectile.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#include "Projectile.hpp"

Projectile::Projectile(const WaveType& w, ofVec2f position, float direction) {
    wave = w;
    vel = ofVec2f(5.0 * direction, 0);
    pos = pos;
    active = true;
}

Projectile::~Projectile() {
}

void Projectile::draw() {
    ofPushStyle();
    ofSetColor(choose_color_by_wave(wave));
    draw_wave(wave, pos);
    ofPopStyle();
}

WaveType& Projectile::get_wave() {
    return wave;
}

void Projectile::set_wave(const WaveType& w) {
    wave = w;
}
