//
//  Movable.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#pragma once

#include "ofMain.h"

class Movable {
public:
    bool active;
    
    ~Movable();
    
    void accellerate();
    ofVec2f get_position();
    void set_position(ofVec2f position);
    void update();
    void accelerate(ofVec2f force);
    bool is_out_of_bounds();
    bool is_active();
    void set_inactive();
//void draw();
    
protected:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f drag;
    float direction;
};
