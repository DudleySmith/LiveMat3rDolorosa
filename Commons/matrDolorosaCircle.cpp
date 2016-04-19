//
//  matrDolorosaCircle.cpp
//  LiveMat3rDolorosa_FluidExample
//
//  Created by Dudley Smith on 19/04/2016.
//
//

#include "matrDolorosaCircle.h"

// ----------------------------------------------------------
matrDolorosaCircle::matrDolorosaCircle(ofPoint centerRelative, float radiusRelative){
    m_pCenter = centerRelative;
    m_fRadius = radiusRelative;
}

// ----------------------------------------------------------
ofPoint matrDolorosaCircle::ratioPos(float ratio){
    
    ratio = fmod(ratio, 1.0);
    // --
    ofPoint returnPos(cos(TWO_PI * ratio), sin(TWO_PI * ratio));
    returnPos *= m_fRadius;
    returnPos += (m_pCenter * ofPoint(ofGetWidth(),ofGetHeight()));
    
    return returnPos / ofPoint(ofGetWidth(),ofGetHeight());
    
}

// ----------------------------------------------------------
void matrDolorosaCircle::draw(){
    ofPushStyle();
    ofNoFill();
    ofDrawCircle(m_pCenter * ofPoint(ofGetWidth(), ofGetHeight()), m_fRadius);
    ofPopStyle();
}