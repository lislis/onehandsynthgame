//
//  ProjectileManager.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 04.08.23.
//

#pragma once

#include "Projectile.hpp"

class ProjectileManager {
public:
    ProjectileManager(const WaveType& wave, ofVec2f position);
    ~ProjectileManager();
    
    void shoot();
    void update(const WaveType& wave, ofVec2f pos);
    void draw();
    std::vector<Projectile*> get_projectiles();
    
private:
    float cooldown;
    Projectile* next_shot;
    std::vector<Projectile*>projectiles{};
    
    void update_next_shot(const WaveType& wave, ofVec2f pos);
    void update_projectiles();
    void draw_next_shot();
    void draw_projectiles();
};
