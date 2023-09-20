//
//  Enemy.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 01.09.23.
//

#pragma once

#include "Movable.hpp"
#include "WaveType.hpp"

class Enemy : public Movable {
public:
    Enemy(int wave_variant_index, ofVec2f position, float direction);
    ~Enemy();
    
    void draw(const WaveType& wave);
    //void set_wave(const WaveType& wave);
    WaveType& get_wave();
    
private:
    WaveType wave;
};
