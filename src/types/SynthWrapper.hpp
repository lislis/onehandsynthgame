//
//  SynthWrapper.hpp
//  OHSGv2
//
//  Created by lis lis on 20.09.23.
//

#pragma once
#include "WaveType.hpp"
#include "config.h"
#include "audiotool.hpp"

class SynthWrapper {
public:
    void setup();
    
    float frequency;
    float phaseInc;
    double phase;

    float currentOctave;
    float getOctaveLocation(float frequency);

    float* lowestFreqList;
    float waveTable[NUM_TABLES][TABLE_SIZE];
    float tableFundamentalFreq;

    WaveType currentType;

    void changeTable(WaveType waveType);
    float getCurrentSample();
};
