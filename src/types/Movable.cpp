//
//  Movable.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#include "ofMain.h"
#include "Movable.hpp"


Movable::~Movable() {
}

void Movable::accelerate(ofVec2f force) {
    acc += force;
}
ofVec2f Movable::get_position() {
    return pos;
}

void Movable::set_position(ofVec2f position) {
    pos = position;
}

void Movable::update() {
    acc += drag; // external force
    vel += acc;
    //vel.x = vel.x < 0 ? 0 : vel.x; // can this be nicer with max or abs?
    pos += vel;
    acc = ofVec2f(0.0, 0.0);
}

bool Movable::is_out_of_bounds() {
    if (pos.x > ofGetWidth() + WAVE_WIDTH || pos.x < SHIP_X - WAVE_WIDTH) {
        return true;
    } else {
        return false;
    }
}

bool Movable::is_active() {
    return active;
}

void Movable::set_inactive() {
    active = false;
}
