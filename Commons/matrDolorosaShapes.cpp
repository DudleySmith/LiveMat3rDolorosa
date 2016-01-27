//
//  matrDolorosaShapes.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 26/01/2016.
//
//

#include "matrDolorosaShapes.h"

// -----------------------------------------
void matrDolorosaShapes::setup(){
    background.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps

    background.begin();
    ofClear(255,255,255, 0);
    background.end();

}

// -----------------------------------------
void matrDolorosaShapes::update(){
    // ---------- ---------- ---------- ---------- ---------- ----------
    background.begin();
    // ---------- ---------- ---------- ---------- ---------- ----------
    ofPushStyle();
    ofFill();
    
        ofSetColor(ofColor::orange);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
        ofSetColor(255,255,255);
        ofDrawCircle(0.5 * background.getWidth(), 0.5 * background.getHeight(), 150);
    
    ofPopStyle();
    // ---------- ---------- ---------- ---------- ---------- ----------
    background.end();
    
}

// -----------------------------------------
void matrDolorosaShapes::draw(){
    
    ofPushMatrix();
    ofTranslate(-0.5 * ofGetWidth(), -0.5 * ofGetHeight());
    background.draw(0,0);
    ofPopMatrix();
}