//
//  matrDolorosaPies.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 01/03/2016.
//
//

#include "matrDolorosaPies.h"

// -----------------------------------------
void matrDolorosaPies::update(){
    
}

// -----------------------------------------
void matrDolorosaPies::draw(){
    
    float angleA = ofGetElapsedTimef() * 360.0f;
    float angleB = ofGetElapsedTimef() * 30.0f + angleA;
    
    ofPushStyle();
    ofFill();
    
    myPie.draw(0, 0, 200, angleA, angleB, true, false);
    
    
    ofPopStyle();
}