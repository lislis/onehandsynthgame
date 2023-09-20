//
//  SynthWrapper.cpp
//  OHSGv2
//
//  Created by lis lis on 20.09.23.
//

#include "SynthWrapper.hpp"


void SynthWrapper::setup() {
    currentType = WaveType::sine;
    
    frequency = 440;
    phase = 0;

    tableFundamentalFreq = SAMPLE_RATE /float(TABLE_SIZE);
    phaseInc = frequency / tableFundamentalFreq;

    changeTable(currentType);
}

float SynthWrapper::getCurrentSample() {
    phaseInc = frequency / tableFundamentalFreq;
    
    currentOctave = getOctaveLocation(frequency);
    float lowOct = linearInterp(waveTable[int(currentOctave)][int(phase)], waveTable[int(currentOctave)][int(phase+1)], phase);
    float highOct = linearInterp(waveTable[int(fmin(currentOctave + 1, 9))][int(phase)], waveTable[int(fmin(currentOctave+1, 9))][int(phase+1)], phase);
    
    float currentSample = linearInterp(lowOct, highOct, currentOctave);
    currentSample *= 0.1;
    phase += phaseInc;
    if (phase >= TABLE_SIZE) {phase -= TABLE_SIZE;}
    return currentSample;
}

//--------------------------------------------------------------
float SynthWrapper::getOctaveLocation(float _freq) {
    if (_freq > lowestFreqList[9]) {
        currentOctave = 9;
        return 9.0;
    }
    int index = 0;
    if (_freq <= lowestFreqList[0]) {
        currentOctave = 0;
        return 0.0;
    }
    while (_freq > lowestFreqList[index]) {
        if (_freq < lowestFreqList[index+1]) {
            return index + ((_freq/lowestFreqList[index])-1.0);
        } else {
            index++;
        }
    }
}


// --- actual wavetable synth logic ---
//--------------------------------------------------------------
void SynthWrapper::changeTable(WaveType waveType) {
    float nyquist = 20000;
    lowestFreqList = new float[NUM_TABLES];
    
    float currentLow = 20;
    for (int i = 0; i < NUM_TABLES; i++) {
        lowestFreqList[i] = currentLow;
        currentLow *= 2;
    }
    
    switch(waveType) {
        case sine:
            for (int i = 0; i < NUM_TABLES; i++) {
                for (int j = 0; j < TABLE_SIZE; j++) {
                    float numHarmonics = 1;
                    waveTable[i][j] = 0;
                    while(lowestFreqList[i] * numHarmonics < nyquist) {
                        float theta = j*TWO_PI/TABLE_SIZE;
                        waveTable[i][j] += (sin(theta) * 1/float(numHarmonics));
                        numHarmonics += 1;
                    }
                }
            }
            break;
        case square:
            for (int i = 0; i < NUM_TABLES; i++) {
                for (int j = 0; j < TABLE_SIZE; j++) {
                    float numHarmonics = 1;
                    waveTable[i][j] = 0;
                    while(lowestFreqList[i] * numHarmonics < nyquist) {
                        float theta = (j*TWO_PI*numHarmonics)/float(TABLE_SIZE);
                        waveTable[i][j] += sin(theta) * (1/float(numHarmonics));
                        numHarmonics += 2;
                    }
                }
            }
            break;
        case triangle:
            for (int i = 0; i < NUM_TABLES; i++) {
                for (int j = 0; j < TABLE_SIZE; j++) {
                    float numHarmonics = 1;
                    waveTable[i][j] = 0;
                    while(lowestFreqList[i] * numHarmonics < nyquist) {
                        float theta = (j*TWO_PI*numHarmonics)/float(TABLE_SIZE);
                        waveTable[i][j] += cos(theta) * (1/float(numHarmonics*numHarmonics));
                        numHarmonics += 2;
                    }
                }
            }
            break;
        case sawtooth:
            for (int i = 0; i < NUM_TABLES; i++) {
                for (int j = 0; j < TABLE_SIZE; j++) {
                    float numHarmonics = 1;
                    waveTable[i][j] = 0;
                    while(lowestFreqList[i] * numHarmonics < nyquist) {
                        float theta = (j*TWO_PI*numHarmonics)/float(TABLE_SIZE);
                        waveTable[i][j] += sin(theta) * (-1/float(numHarmonics));
                        numHarmonics += 1;
                    }
                }
            }
            break;
        default:
            cout << "not a valid type" << endl;
            break;
    }
    
    // normalize wavetables
    for (int i = 0; i < NUM_TABLES; i++) {
        float largestValue = 0;
        for (int j = 0; j < TABLE_SIZE; j++) {
            if (fabs(waveTable[i][j]) > largestValue) {
                largestValue = fabs(waveTable[i][j]);
            }
        }
        float scalarValue = 1/float(largestValue);
        for (int j = 0; j < TABLE_SIZE; j++) {
            waveTable[i][j] *= scalarValue;
        }
    }
}

void SynthWrapper::handleKeyReleased(int key) {
    switch(key) {
        case SINE_KEY:
            changeTable(WaveType::sine);
            break;
        case SQUARE_KEY:
            changeTable(WaveType::square);
            break;
        case TRIANGLE_KEY:
            changeTable(WaveType::triangle);
            break;
        case SAWTOOTH_KEY:
            changeTable(WaveType::sawtooth);
            break;
    }
}
