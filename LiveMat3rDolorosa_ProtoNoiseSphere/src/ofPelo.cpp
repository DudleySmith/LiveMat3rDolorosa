//
//  ofPelo.cpp
//  LiveMat3rDolorosa_ProtoNoiseSphere
//
//  Created by Dudley Smith on 18/12/2015.
//
//

#include "ofPelo.h"

ofPelo::ofPelo(float ballRadius){
    
    m_fBallRadius = ballRadius;
    
    
    m_fZ = ofRandom(-ballRadius, ballRadius);
    m_fPhi = ofRandom(TWO_PI);
    m_fLargo = ofRandom(1.15, 1.2);
    m_fTheta = asin(m_fZ/ballRadius);

    
}
void ofPelo::setup(){
    
}

void ofPelo::update(){
    
}

void ofPelo::draw(){
    
    float off = (ofNoise(ofGetElapsedTimeMillis() * 0.0005, sin(m_fPhi))-0.5) * 0.3;
    float offb = (ofNoise(ofGetElapsedTimeMillis() * 0.0007, sin(m_fZ) * 0.01)-0.5) * 0.3;
    
    float thetaff = m_fTheta+off;
    float phff = m_fPhi+offb;
    float x = m_fBallRadius * cos(m_fTheta) * cos(m_fPhi);
    float y = m_fBallRadius * cos(m_fTheta) * sin(m_fPhi);
    float z = m_fBallRadius * sin(m_fTheta);
//    float msx= screenX(x, y, z);
//    float msy= screenY(x, y, z);
    
    float xo = m_fBallRadius * cos(thetaff) * cos(phff);
    float yo = m_fBallRadius * cos(thetaff) * sin(phff);
    float zo = m_fBallRadius * sin(thetaff);
    
    float xb = xo * m_fLargo;
    float yb = yo * m_fLargo;
    float zb = zo * m_fLargo;
    
    ofBeginShape();
    //stroke(0);
    ofVertex(x, y, z);
    //stroke(200, 150);
    ofVertex(xb, yb, zb);
    ofEndShape();
    
}