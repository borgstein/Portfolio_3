//
//  Sequencer.hpp
//  Poly_Drum_Machine
//
//  Created by Leo Petrokofsky on 29/12/2017.
//
//

#ifndef Sequencer_hpp
#define Sequencer_hpp
#include "ofMain.h"
#include "ofxMaxim.h"
#include "Steps.hpp"
#include <stdio.h>

class Sequencer{
    
    public:
        
    //methods
    void setupSequencer(float _x, float _y, float _w, string _sampleName, unsigned _stepAmount, int _gap);
    void drawSequencer();
    void rewind();
    void render(unsigned _current);
    
        //variables
    unsigned stepAmount;
    float x, y, w;
    vector <Steps> steps;
    ofxMaxiSample sample;

    
    
    
};


#endif /* Sequencer_hpp */
