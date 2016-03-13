//
//  matrDolorosaNodeFields.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 12/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

#include "matrDolorosaNode.h"

#define nodeAmountMax 2000

class matrDolorosaNodeField {
	
    vector<matrDolorosaNode> nodeArray;
    float distances[nodeAmountMax][nodeAmountMax];
    
public:
    ofxPanel panel;

private:
    ofxOscParameterSync sync;
    ofParameterGroup field;
    
    ofParameter<int>    nbNodes;
    ofParameter<bool>   xyLinks;
    ofParameter<bool>   sphereLimit;
    ofParameter<float>  distance;
    ofParameter<float>  entropyBig;
    ofParameter<float>  entropyFine;
    ofParameter<float>  circleSize;
    
    ofParameter<float>  xLimit;
    ofParameter<float>  yLimit;
    ofParameter<float>  zLimit;
    ofParameter<float>  exRadius;
    ofParameter<float>  inRadius;
    
    ofParameter<ofColor>    sphereColor;
    ofParameter<ofColor>    linkColor;
    
    
    
public:
    void setup();
    void update();
    void draw();
    void generateNodes(int _nodeAmount);
    void evalDist();
    
};

