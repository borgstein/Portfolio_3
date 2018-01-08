//
//  Sequencer.cpp
//  Poly_Drum_Machine
//
//  Created by Leo Petrokofsky on 29/12/2017.
//

#include "Sequencer.hpp"

void Sequencer::setupSequencer(float _x, float _y, float _w, string _sampleName, unsigned _stepAmount, int _gap){

    
    sample.load(ofToDataPath(_sampleName));
    steps.clear();
    
    x = _x;
    y = _y;
    w = _w;
    stepAmount = _stepAmount;
    
    
    for(int i = 0; i < stepAmount; i++){
        Steps temp;
        temp.size = _w/stepAmount;
        temp.x = x + i * (temp.size + _gap);
        temp.y = y;
        temp.on = false;
        steps.push_back(temp);
        
    }
}

void Sequencer::drawSequencer(){
    
    
    
}

void Sequencer::rewind(){
    sample.setPosition(0);
}

void Sequencer::render(unsigned _current){
    
    for(int i = 0; i < stepAmount; i++){
        
        if(i == _current){
            steps[i].render(true, steps[i].size);

        } else {
            steps[i].render(false, steps[i].size);
            
        }
    }
    
}
//Sequencer Class was built from using sequencer struct in Leon Fedden's Step Sequencer ofxMaxim tutorial as a start point
