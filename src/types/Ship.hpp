//
//  Ship.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 03.08.23.
//

#pragma once
#include "ofMain.h"
#include "WaveType.hpp"
#include "ProjectileManager.hpp"

class Ship {
public:
    Ship(const WaveType& wave);
    ~Ship();
    
    void update(const WaveType& wave);
    void draw(const WaveType& wave);
    void shoot();
    std::vector<Projectile*> get_projectiles();
    
private:
    ofVec2f position;
    ProjectileManager* pm;
    float direction;
    float size;
    float speed;
};
