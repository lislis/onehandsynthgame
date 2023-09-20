#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isPlaying = false;
    synth.setup();
    
    backgroundTrack.load("ohsg-bg.wav");
    backgroundTrack.setLoop(true);
    backgroundTrack.play();
    
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = SAMPLE_RATE;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = BUFFER_SIZE;
    soundStream.setup(settings);}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key) {
        case 32:
            isPlaying = !isPlaying;
            break;
        case 121:
            synth.changeTable(WaveType::sine);
            break;
        case 117:
            synth.changeTable(WaveType::square);
            break;
        case 105:
            synth.changeTable(WaveType::triangle);
            break;
        case 108:
            synth.changeTable(WaveType::sawtooth);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
    if (isPlaying) {
        for (int i = 0; i < buffer.getNumFrames(); i++) {
            float currentSample = synth.getCurrentSample();
            
            buffer[i*buffer.getNumChannels() + 0] = currentSample;
            buffer[i*buffer.getNumChannels() * 1] = currentSample;
        }
    }
}


//--------------------------------------------------------------
void ofApp::exit() {
    ofSoundStreamClose();
}
