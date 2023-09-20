//
//  EnemyManager.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 01.09.23.
//

#include "EnemyManager.hpp"
#include "config.h"

EnemyManager::EnemyManager() {
    timer = 3000.0;
}

EnemyManager::~EnemyManager() {
    
}

void EnemyManager::update() {
    timer += ofGetElapsedTimef();
    
    if (timer > ENEMY_WAVE_INTERVAL) {
        spawn_wave();
        timer = 0.0;
        cout << "spawn" << endl;
    }
    
    for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        Enemy* enem = *it;
        enem->update();
        
        if (enem->is_out_of_bounds()) {
            enem->set_inactive();
        }
    }

    for (int i = 0; i < enemies.size(); i++) {
        if (!enemies[i]->is_active()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
}

void EnemyManager::draw(const WaveType& wave) {
    for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        Enemy* enem = *it;
        enem->draw(wave);
    }
}

void EnemyManager::spawn_wave() {
    int new_enemies_wave_count = NUM_ENEMIES_PER_WAVE;
    for (int i = 0; i < new_enemies_wave_count; i++) {
        float rand_y = ofRandom(UPPER_BOUND, LOWER_BOUND - WAVE_HEIGHT);
        ofVec2f new_pos = ofVec2f(ofGetWidth(), rand_y);
        int rand_wave = (int)ofRandom(0, 4); // because enum variants are just numbers
        Enemy* new_enem = new Enemy(rand_wave, new_pos, -1);
        enemies.push_back( new_enem );
    }
}

std::vector<Enemy*> EnemyManager::get_enemies() {
    return enemies;
}
