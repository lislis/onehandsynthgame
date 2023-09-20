//
//  EnemyManager.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 01.09.23.
//

#pragma once

#include "Enemy.hpp"

class EnemyManager {
public:
    EnemyManager();
    ~EnemyManager();
    
    void update();
    void draw(const WaveType& wave);
    void spawn_wave();
    std::vector<Enemy*> get_enemies();
    
private:
    std::vector<Enemy*> enemies{};
    long int timer;
};
