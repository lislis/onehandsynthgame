//
//  WaveType.cpp
//  OneHandSynthGame
//
//  Created by lis lis on 04.08.23.
//

#include "WaveType.hpp"


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
        case SINE_KEY: // y
            return WaveType::sine;
        case SQUARE_KEY: // u
            return WaveType::square;
        case TRIANGLE_KEY: // i
            return WaveType::triangle;
        case SAWTOOTH_KEY: // l
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
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    switch (wave) {
        case WaveType::sine:
            draw_sine();
            break;
        case WaveType::square:
            draw_square();
            break;
        case WaveType::triangle:
            draw_triangle();
            break;
        case WaveType::sawtooth:
            draw_sawtooth();
            break;
    }
    
    ofPopMatrix();
    //ofDrawBitmapString(wave, pos.x + 10, pos.y + 14);
}

void draw_wave(const int variant_index, ofVec2f pos) {
    ofNoFill();
    ofSetLineWidth(1);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    switch (variant_index) {
        case WaveType::sine:
            draw_sine();
            break;
        case WaveType::square:
            draw_square();
            break;
        case WaveType::triangle:
            draw_triangle();
            break;
        case WaveType::sawtooth:
            draw_sawtooth();
            break;
    }
    
    ofPopMatrix();
    //ofDrawBitmapString(wave, pos.x + 10, pos.y + 14);
}

void draw_sine() {
    int numPoints = 200;
    ofPolyline form;
    for (int i = 0; i < numPoints; i++) {
        float x = ofMap(i, 0, numPoints, 0, WAVE_WIDTH);
        //float theta = i*TWO_PI/numPoints;
        float theta = i*TWO_PI*2/numPoints;
        float temp_y = sin(theta);
        float y = ofMap(temp_y, -1, 1, WAVE_HEIGHT, 0);
        form.addVertex(x, y);
    }
    form.draw();
}
void draw_square() {
    int numPoints = 200;
    ofPolyline form;
    for (int i = 0; i < numPoints; i++) {
        float x = ofMap(i, 0, numPoints, 0, WAVE_WIDTH);
        float theta = i*TWO_PI/numPoints;
        float temp_y = sqw(theta);
        float y = ofMap(temp_y, -1, 1, WAVE_HEIGHT, 0);
        form.addVertex(x, y);
    }
    form.draw();
}

void draw_triangle() {
    int numPoints = 200;
    ofPolyline form;
    for (int i = 0; i < numPoints; i++) {
        float x = ofMap(i, 0, numPoints, 0, WAVE_WIDTH);
        float theta = i*PI/numPoints;
        float temp_y = tw(theta);
        float y = ofMap(temp_y, -1, 1, WAVE_HEIGHT, 0);
        form.addVertex(x, y);
    }
    form.draw();
}

void draw_sawtooth() {
    int numPoints = 200;
    ofPolyline form;
    for (int i = 0; i < numPoints; i++) {
        float x = ofMap(i, 0, numPoints, 0, WAVE_WIDTH);
        float theta = i*TWO_PI/numPoints;
        float temp_y = stw(theta);
        float y = ofMap(temp_y, -1, 1, WAVE_HEIGHT, 0);
        form.addVertex(x, y);
    }
    form.draw();
}

float sqw(float a) {
    a /= PI;
    a -= int(a);
    return a < .5? -1 : 1;
}

float stw(float a) {
    a /= 2;
    a -= int(a);
    return ofMap(a,0,1,-1,1);
}

float tw(float a) {
    a = 1-4 * fabs(0.5 - ((0.5*a+ 0.25) - int(0.5*a+ 0.25)));
    return a;
}
