#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    ofSoundStreamSetup(2 , 0, this, sampleRate, bufferSize, 4);
    



    
    startTime = ofGetElapsedTimeMillis();

    //2 Seconds - 1 Bar at 120 BPM - 120 as Default
    //Can have 80, 96, 100, 120, 125, 150, 160 (Factors of 60,000)
    bpm = 120;
    endTime = (60000/bpm * 8);  //2 Bar length
    
    
    
    for(int i = 0; i < 5; i++){
        
        stepStartTime[i] = ofGetElapsedTimeMillis();

        stepAmount[i] = 4;
        stepCheck[i] = stepAmount[i];
        
        sampleString[i] << i << ".wav";
        
        //Quarter notes at 120BPM as default  - 60000/bpm * 4
        stepTime[i] = (endTime/stepAmount[i]) * 2;
        
        stepSize[i] = sequencerWidth/stepAmount[i];
        
        current[i] = 0;

    }

    sequencerX = 210;
    sequencerWidth = ofGetWidth() - sequencerX - 70;
    
    bars = 1;
    gap = 2;
    
    for(int i = 0; i < 5; i++){
        
        sequencerY[i] = 180 + (i * 40);
        seqs[i].setupSequencer(sequencerX, sequencerY[i] + gap, sequencerWidth, sampleString[i].str(), stepAmount[i], gap);
        
    }
    
    //GUI STUFF
    kdSteps.addListener(this, &ofApp::kdStepsChanged);
    snSteps.addListener(this, &ofApp::snStepsChanged);
    hhSteps.addListener(this, &ofApp::hhStepsChanged);
    crSteps.addListener(this, &ofApp::crStepsChanged);
    cbSteps.addListener(this, &ofApp::cbStepsChanged);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(kdSteps.setup("Kick Drum Subdivisions", stepAmount[0], 1, 16));
    gui.add(snSteps.setup("Snare Subdivisions", stepAmount[1], 1, 16));
    gui.add(hhSteps.setup("Hi Hat Subdivisions", stepAmount[2], 1, 16));
    gui.add(crSteps.setup("Crash Subdivisions", stepAmount[3], 1, 16));
    gui.add(cbSteps.setup("Cowbell Subdivisions", stepAmount[4], 1, 16));
    
    for(int i = 0; i < 20; i++){
        
        myFont[i].init("Roland.ttf", 18);
        
    }
 
    myFont[0].setText("Poly Rhythm Drum Machine");
    myFont[1].setText("2 Bar Sequencer");
    myFont[2].setText("Move the Sliders to Change the Subdivisions of Each Sampler");
    myFont[3].setText("Kick Drum ");
    myFont[4].setText("Snare Drum ");
    myFont[5].setText("Hi Hat ");
    myFont[6].setText("Crash Cymbal ");
    myFont[7].setText("Cowbell ");
    myFont[8].setText("Hi Hat ");

    
}
                       

//--------------------------------------------------------------
void ofApp::update(){

    
    seqProgression = ofGetElapsedTimeMillis() - startTime;
    
    for(int i = 0; i < 5; i++){
        
        stepProgression[i] = ofGetElapsedTimeMillis() - stepStartTime[i];
    }
    
    
//---------Restart and update Sequencers if needed-------------------
  
    //Progress Sequencers if not restarting
    for(int i = 0; i < 5; i++){
        
        if(stepProgression[i] >= stepTime[i]){
            
            
            current[i]= ++current[i] % stepAmount[i];
            seqs[i].rewind();
            
            
            stepStartTime[i] = ofGetElapsedTimeMillis();
        }
        
    }
    
    if (seqProgression >= endTime){
        
        endTime = endTime * bars;
        
        updateSequencers();
        
        //Set current step position for all sequencers back to 0
        for(int i = 0; i< 5; i++) {
            stepTime[i] = endTime/stepAmount[i];
            current[i] = 0;
            stepStartTime[i] = ofGetElapsedTimeMillis();
        }
        
        startTime = ofGetElapsedTimeMillis();
    }
    
    
 
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i = 0; i< 2; i ++){
    myFont[i].drawCenter(ofGetWidth()/2, 10 + (40 * i));
}
    
    myFont[2].drawCenter(ofGetWidth()/2, 110);
    
    
    gui.draw();
    
    for(int i = 0; i < 5; i++){
        seqs[i].render(current[i]);
        
        myFont[i+3].draw(40, 160 + (i * 40));
    }
    

}
//----------------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    
    for(int i = 0; i < bufferSize; i++){
        
        currentSample = 0;
        
        
        for(int j = 0; j < 5; j++){
            
            for(int k = 0; k < stepAmount[j]; k++){
                
                if(seqs[j].steps[k].on){
                    currentSample += seqs[j].sample.playOnce() / stepAmount[j];
                }
                
            }
            
        }
        
        
        mix.stereo(currentSample, outputs, 0.5);
        
        
        //-------THESE SEEM TO BE THE PROBLEM AREA----------
        output[i * nChannels] = outputs[0];
        output[i * nChannels + 1] = outputs[1];
        
    }
    
    
}


//--------------------------------------------------------------

void ofApp::updateSequencers(){
    
 
    vector <bool> isOn [5];
    
    
    for(int i = 0; i < 5; i ++){
        
        isOn[i].reserve(stepAmount[i]);

        
        for(int j = 0; j < stepAmount[i]; j++){
            if (seqs[i].steps[j].on == true){
                isOn[i].push_back(true);
            }
            else
                isOn[i].push_back(false);
    
            
        }
        
        
         stepSize[i] = sequencerWidth/stepAmount[i];
         seqs[i].setupSequencer(sequencerX, sequencerY[i], sequencerWidth, sampleString[i].str(), stepAmount[i], gap);
        
        //Check to see if step amount has been changed during sequence
        //If not then pass array of bools turning on the already selected steps from the current sequencer object
        if(stepCheck[i] == stepAmount[i]){
            

            for(int j = 0; j< isOn[i].size(); j++){
                
                seqs[i].steps[j].on = isOn[i][j];
                
            }
            
            
        }
        
        stepCheck[i] = stepAmount[i];
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    for(int i = 0; i < 5; i++){
        
        //Check which sequencer is being toggled
        if(y >= seqs[i].y && y<= seqs[i].y + 20 ){
            
            for (int j = 0; j<seqs[i].steps.size(); j++){
                
                //Check which step in the sequencer is being toggled
                if(x >= seqs[i].steps[j].x && x <= seqs[i].steps[j].x + stepSize[i]){
                 
                    seqs[i].steps[j].pressed();
                }
            }
        }
    }
    
}

void ofApp::kdStepsChanged(int & kdSteps){
    stepAmount[0] = kdSteps * 2;
    
}

void ofApp::snStepsChanged(int & snSteps){
    stepAmount[1] = snSteps * 2;

    
}
void ofApp::hhStepsChanged(int & hhSteps){
    stepAmount[2] = hhSteps * 2;

}
void ofApp::crStepsChanged(int & crSteps){
    stepAmount[3] = crSteps * 2;

}
void ofApp::cbStepsChanged(int & cbSteps){
    stepAmount[4] = cbSteps * 2;

}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
