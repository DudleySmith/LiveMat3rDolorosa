//
//  ofPelo.h
//  LiveMat3rDolorosa_ProtoNoiseSphere
//
//  Created by Dudley Smith on 18/12/2015.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

class ofPelo{
    
    
public:
    
    ofPelo(float ballRadius);
    
    void setup();
    void update();
    void draw();
    
    float m_fZ;
    float m_fPhi;
    float m_fLargo;
    float m_fTheta;
    float m_fBallRadius;
    
};
