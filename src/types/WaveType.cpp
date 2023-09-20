//
//  WaveType.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 04.08.23.
//

#include "WaveType.hpp"
#include "config.h"


//void Wave::update() {
//    form.clear();
//    
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        float x = ofMap(i, 0, TABLE_SIZE, 0, WAVE_WIDTH);
//        float y = ofMap(waveTable[int(currentOctave)][i], -1, 1, WAVE_HEIGHT, 0);
//        form.addVertex(x, y);
//    }
//}

void Wave::draw(float _x, float _y) {
    ofPushMatrix();
    ofTranslate(_x, _y);
    form.draw();
    //ofDrawBitmapString(ofToString(type), _x, _y);
    ofPopMatrix();
}

ofColor choose_color_by_wave(const WaveType& wave) {
    switch (wave) {
        case WaveType::sine:
            return SINE_COLOR;
        case WaveType::square:
            return SQUARE_COLOR;
        case WaveType::triangle:
            return TRIANGLE_COLOR;
        case WaveType::sawtooth:
            return SAWTOOTH_COLOR;
        default:
            break;
    }
}

WaveType choose_wave_by_key(int key) {
    switch (key) {
        case 121: // y
            return WaveType::sine;
        case 117: // u
            return WaveType::square;
        case 105: // i
            return WaveType::triangle;
        case 108: // l
            return WaveType::sawtooth;
        default:
            return WaveType::sine;
            break;
    }
}

WaveType assign_wave(const WaveType& wave) {
    switch (wave) {
        case WaveType::sine:
            return WaveType::sine;
        case WaveType::square:
            return WaveType::square;
        case WaveType::triangle:
            return WaveType::triangle;
        case WaveType::sawtooth:
            return WaveType::sawtooth;
    }
}

WaveType assign_wave(int variant_index) {
    switch (variant_index) {
        case 0:
            return WaveType::sine;
        case 1:
            return WaveType::square;
        case 2:
            return WaveType::triangle;
        case 3:
            return WaveType::sawtooth;
        default:
            return WaveType::sine;
    }
}

void draw_wave(const WaveType& wave, ofVec2f pos) {
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawRectangle(pos.x, pos.y, WAVE_WIDTH, WAVE_HEIGHT);
    ofDrawBitmapString(wave, pos.x + 10, pos.y + 14);
}
