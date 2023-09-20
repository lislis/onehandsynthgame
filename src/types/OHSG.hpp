//
//  OHSG.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 02.08.23.
//

#pragma once
#include "ofMain.h"
#include "Ship.hpp"
#include "WaveType.hpp"
#include "EnemyManager.hpp"

enum GameState { intro, tutorial, loop, over };

class OHSG {
    public:
        OHSG();
        ~OHSG();
    
        int get_state();
        void set_state(GameState new_state);
        void increase_score();
        void reset_score();
        int get_score();
        
    
        void update();
        void draw();
        void collision_check();
        void handle_key_released(int key);
        
    private:
        GameState state;
        Ship* ship;
        WaveType wave;
        EnemyManager* em;
    
        int score{0};
        void draw_background();
        void draw_entities();
        void draw_ui();
        void draw_level();
        void draw_intro();
        void draw_tutorial();
        void draw_over();
};
