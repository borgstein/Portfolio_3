#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "Sequencer.hpp"
#include "Steps.hpp"
#include "ofxTextSuite.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    //Methods
    void updateSequencers();
    void kdStepsChanged(int & kdSteps);
    void snStepsChanged(int & snSteps);
    void hhStepsChanged(int & hhSteps);
    void crStepsChanged(int & crSteps);
    void cbStepsChanged(int & cbSteps);
    
    //Variables
    
    stringstream sampleString[5];
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
    unsigned bufferSize, sampleRate, startTime, endTime, seqProgression, gap, bars;
    
    unsigned stepTime [5], stepAmount[5], stepCheck[5], current[5], stepProgression[5], stepStartTime[5];
    
    int bpm;
    
    int KDsteps, SNsteps, HHsteps, CRsteps, CBsteps;
    
    float stepSize[5], sequencerX, sequencerY[5], sequencerWidth;
    
    Sequencer seqs[5];
    
    double currentSample;
    double outputs [2];
    
    maxiMix mix;
    
    
    //GUI BITS
    
    ofxIntSlider kdSteps, snSteps, hhSteps, crSteps, cbSteps, barsSlider;
    ofxPanel gui;
    ofxTextBlock  myFont [20];

    
    
};
