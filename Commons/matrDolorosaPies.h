//
//  matrDolorosaPies.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 01/03/2016.
//
//

#pragma once

#define nbPiesMax 32
#define nbRadiusMax 16

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

#include "matrDolorosaPie.h"

class matrDolorosaPies {
    
    matrDolorosaPie pies;
    
public:
    ofxPanel panel;
    
private:
    ofxOscParameterSync sync;
    ofParameterGroup pgPies;
    
    ofParameter<int> nbPies;
    ofParameter<bool> fillNoFill;
    
    
    ofParameter<int> nbRadius;
    ofParameter<float> radiusFactor;
    ofParameter<float> startRadius;
    ofParameter<float> endRadius;
    
    ofParameter<float> singleAngleStart;
    ofParameter<float> singleAngleEnd;
    
public:
    void setup();
    void update();
    void draw();
    
    void drawOnePie(float x,float y, float lowRadius, float highRadius, float lowAngle, float highAngle, bool closed, bool radians);
    
    void drawPartofCircle(float x,float y, float radius, float lowAngle, float highAngle, bool radians);
    
};