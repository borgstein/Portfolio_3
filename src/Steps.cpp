//
//  Steps.cpp
//  Poly_Drum_Machine
//
//  Created by Leo Petrokofsky on 29/12/2017.
//
//

#include "Steps.hpp"

void Steps::render(bool _this, float _size){
    
    size = _size;
    if(_this){ //current step
        ofSetColor(255,0,0);
    }
    else if(on){
        ofSetColor(255,255,0);
    }
    else{
        ofSetColor(255);
    }
    ofDrawRectangle(x, y, size, 20);
}

void Steps::pressed() {
    
    on = !on;
    
}


//Step Class was built from using step struct in Leon Fedden's Step Sequencer ofxMaxim tutorial as a start point
