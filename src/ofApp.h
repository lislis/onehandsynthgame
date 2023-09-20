#pragma once

#include "ofMain.h"
#include "config.h"
#include "audioTool.hpp"
#include "types/WaveType.hpp"
#include "types/SynthWrapper.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
        void exit();
        void audioOut(ofSoundBuffer& outBuffer);
        
        ofSoundPlayer backgroundTrack;
        ofSoundStream soundStream;
        bool isPlaying;
        SynthWrapper synth;
};
