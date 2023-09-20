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
    soundStream.setup(settings);

    game = new OHSG();
}

//--------------------------------------------------------------
void ofApp::update(){
    game->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    game->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == SHOOT_KEY && game->get_state() == loop) {
        isPlaying = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    game->handle_key_released(key);
    synth.handleKeyReleased(key);
    
    if (key == SHOOT_KEY && game->get_state() == loop) {
        isPlaying = false;
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
