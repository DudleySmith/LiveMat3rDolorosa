//
//  matrDolorosaCircles.h
//  LiveMat3rDolorosa_FluidExample
//
//  Created by Dudley Smith on 19/04/2016.
//
//

#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxOscParameterSync.h"

#include "matrDolorosaCircle.h"

class matrDolorosaCircles {
    
public:
    void setup();
    void update(float ratio);
    void draw();
    
private:
    vector<matrDolorosaCircle> circles;
    
public:
    vector<ofPoint> points;
    vector<ofPoint> speeds;
    
};
