//
//  WaveType.hpp
//  OneHandSynthGame
//
//  Created by lis lis on 04.08.23.
//

#pragma once
#include "ofMain.h"
#include "config.h"

enum WaveType {
    sine,
    square,
    triangle,
    sawtooth
};

class Wave {
    WaveType type;
    ofPolyline form;
    void draw(float x, float y);
    //void update();
};

ofColor choose_color_by_wave(const WaveType& wave);
WaveType choose_wave_by_key(int key);
WaveType assign_wave(const WaveType& wave);
WaveType assign_wave(int variant_index);
void draw_wave(const WaveType& wave, ofVec2f pos);
void draw_wave(const int variant_index, ofVec2f pos);

void draw_sine();
void draw_square();
void draw_triangle();
void draw_sawtooth();

// --- wave drawing helpers
float sqw(float a);
float stw(float a);
float tw(float a);
