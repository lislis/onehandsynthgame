//
//  Projectile.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#pragma once

#include "Movable.hpp"
#include "WaveType.hpp"

class Projectile  : public Movable {
public:
    Projectile(const WaveType& wave, ofVec2f position, float direction);
    ~Projectile();
    
    void draw();
    void set_wave(const WaveType& wave);
    WaveType& get_wave();
    
private:
    WaveType wave;
};
