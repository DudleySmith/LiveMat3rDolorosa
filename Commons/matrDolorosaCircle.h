//
//  matrDolorosaCircle.h
//  LiveMat3rDolorosa_FluidExample
//
//  Created by Dudley Smith on 19/04/2016.
//
//

#pragma once

#include "ofMain.h"
#include "matrDolorosaCircle.h"

class matrDolorosaCircle {
    
public:
    matrDolorosaCircle(ofPoint centerRelative, float radius);
    ofPoint ratioPos(float ratio);
    
    void draw();
    
private:
    ofPoint m_pCenter;
    float   m_fRadius;
    
};
