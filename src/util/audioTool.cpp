//
//  audioTool.cpp
//  wavetable-synth
//
//  Created by lis lis on 18.09.23.
//

#include "audioTool.hpp"

// ---------- linear --------
float linearInterp(float y0, float y1, float currentX) {
    float interpolatedValue;
    float scaleValue = currentX - (int)currentX;
    
    interpolatedValue = (y0*(1 - scaleValue)) + (y1*scaleValue);
    return interpolatedValue;
}

// ----------- cubic -------
float cubicInterp(float y0, float y1, float y2, float y3, float currentX) {
    float interpolatedValue;
    
    float a = (-0.5*y0) + (1.5*y1) - (1.5*y2) + (0.5*y3);
    float b = (y0) - (2.5*y1) + (2*y2) - (0.5*y3);
    float c = (-0.5*y0) + (0.5*y2);
    float d = y1;
    
    float xOff = currentX - (int)currentX;
    interpolatedValue = (a*pow(xOff, 3)) + b*(pow(xOff, 2)) + (c*xOff) + d;
    
    return interpolatedValue;
}
