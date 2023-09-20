//
//  config.h
//  OneHandSynthGame
//
//  Created by lis lis on 02.08.23.
//

#pragma once
#include "ofMain.h"

#define MAX_GAME_TIME 60.0

// --- CONTROLS ---
#define SHOOT_KEY 32
#define SINE_KEY 121
#define SQUARE_KEY 117
#define TRIANGLE_KEY 105
#define SAWTOOTH_KEY 108

// --- AUDIO ---
#define TABLE_SIZE 1024
#define NUM_TABLES 10

#define BUFFER_SIZE 512
#define SAMPLE_RATE 48000

// --- INTERFACE ---
#define UPPER_BOUND 80.
#define LOWER_BOUND ofGetHeight() - 50.

#define FONT_COLOR ofColor(200, 200, 200)
#define BOUND_COLOR ofColor(60, 60, 60)
#define BACKGROUND_COLOR ofColor(30, 33, 32)
#define SHIP_COLOR ofColor(190, 40, 60)

#define SHIP_X 100.0

// --- WAVES ---
#define SINE_COLOR ofColor(200, 0, 100);
#define SQUARE_COLOR ofColor(0, 100, 200);
#define TRIANGLE_COLOR ofColor(50, 200, 50);
#define SAWTOOTH_COLOR ofColor(200, 200, 0);

#define WAVE_WIDTH 30.
#define WAVE_HEIGHT 20.

// --- ENEMIES ---
#define ENEMY_WAVE_INTERVAL 1.0
#define ENEMY_INACTIVE_COLOR ofColor(100.0, 100.0, 100.0)
#define NUM_ENEMIES_PER_WAVE 7
