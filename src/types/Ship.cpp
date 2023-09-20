//
//  Ship.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#include "ofMain.h"
#include "Ship.hpp"
#include "config.h"


Ship::Ship(const WaveType& wave) {
    direction = -1.;
    size = 30.;
    speed = 100.;
    position = ofVec2f(100., ofGetHeight()/2);
    pm = new ProjectileManager(wave, position);
};

Ship::~Ship() {
    delete pm;
};

void Ship::update(const WaveType& wave) {
    position.y += (direction * ofGetLastFrameTime() * speed);
    pm->update(wave, position);
    
    if (position.y <= UPPER_BOUND + size) {
        direction = 1.;
    }
    if (position.y >= LOWER_BOUND - size) {
        direction = -1.;
    }
}

void Ship::draw(const WaveType& wave) {
    ofVec2f p2 = position + ofVec2f(-size, -size);
    ofVec2f p3 = position + ofVec2f(-size, size);
    ofPushStyle();
    
    ofSetColor(choose_color_by_wave(wave));
    ofFill();
    ofDrawTriangle(position.x, position.y, p3.x, p3.y, p2.x, p2.y);
    
    pm->draw();
    ofPopStyle();
}

void Ship::shoot() {
    pm->shoot();
}

std::vector<Projectile*> Ship::get_projectiles() {
    return pm->get_projectiles();
}
