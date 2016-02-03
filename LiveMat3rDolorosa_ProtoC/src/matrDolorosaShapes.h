//
//  matrDolorosaShapes.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 26/01/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

class matrDolorosaShapes{
    
public:
    void setup();
    void update();
    void draw();
    
    ofFbo background;
    //ofxAnimatableFloat  anim;
    
    bool drawMarks;
    
    ofxPanel panel;
    ofxOscParameterSync sync;
    ofParameterGroup shapes;
    
    ofParameter<float> rootDriver;
    
    ofParameter<float>  alphaTrails;
    ofParameter<float>  lineWidth;
    ofParameter<bool>   fillNoFill;
    ofParameter<int>  circleResolution;
    ofParameter<int>  nbLinesShapes;
    ofParameter<int>  nbRowsShapes;
    
    ofParameter<float>  xOffset;
    ofParameter<float>  yOffset;
    ofParameter<float>  xSizeOffset;
    ofParameter<float>  ySizeOffset;
    
};