//
//  Steps.hpp
//  Poly_Drum_Machine
//
//  Created by Leo Petrokofsky on 29/12/2017.
//
//

#ifndef Steps_hpp
#define Steps_hpp

#include <stdio.h>
#include "ofMain.h"

class Steps {
    
public:
    //Methods
    void render(bool _this, float _size);
    void pressed();
    
    
    //Variables
    float x, y, size;
    
    bool on;
    
    
};
#endif /* Steps_hpp */
