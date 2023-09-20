//
//  audioTool.hpp
//  wavetable-synth
//
//  Created by lis lis on 18.09.23.
//

#pragma once

#include "ofMain.h"

float linearInterp(float y0, float y1, float currentX);
float cubicInterp(float y0, float y1, float y2, float y3, float currentX);
