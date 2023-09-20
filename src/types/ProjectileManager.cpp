//
//  ProjectileManager.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 04.08.23.
//

#include "ProjectileManager.hpp"
#include "WaveType.hpp"

ProjectileManager::ProjectileManager(const WaveType& wave, ofVec2f position) {
    cooldown = 5.;
    next_shot = new Projectile(wave, position, 1);
}

ProjectileManager::~ProjectileManager() {
    delete next_shot;
    for (int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
        projectiles.erase(projectiles.begin() + i);
    }
}

void ProjectileManager::update(const WaveType& wave, ofVec2f pos) {
    update_next_shot(wave, pos);
    update_projectiles();
}

void ProjectileManager::update_next_shot(const WaveType& wave, ofVec2f pos) {
    next_shot->set_wave(wave);
    next_shot->set_position(pos);
}

void ProjectileManager::update_projectiles() {
    for (std::vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); it++) {
        Projectile* proj = *it;
        proj->update();
        if (proj->is_out_of_bounds()) {
            proj->set_inactive();
        }
    }
    // I'm doing a 'cleanup' round in a 2nd step
    // since I ran into problems with erasing elements in the first step
    for (int i = 0; i < projectiles.size(); i++) {
        if (!projectiles[i]->is_active()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

void ProjectileManager::draw() {
    draw_next_shot();
    draw_projectiles();
}

void ProjectileManager::draw_next_shot() {
    draw_wave(next_shot->get_wave(), next_shot->get_position());
}

void ProjectileManager::draw_projectiles() {
    for (std::vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); it++) {
        Projectile* proj = *it;
        proj->draw();
    }
}

void ProjectileManager::shoot() {
    Projectile* new_shot = new Projectile(next_shot->get_wave(), next_shot->get_position(), 1);
    // next_shot->accelerate(ofVec2f (2000.0, 0.0));
    projectiles.push_back( next_shot );
    next_shot = new_shot;
}

std::vector<Projectile*> ProjectileManager::get_projectiles() {
    return projectiles;
}
