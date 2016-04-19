//
//  matrDolorosaCircles.cpp
//  LiveMat3rDolorosa_FluidExample
//
//  Created by Dudley Smith on 19/04/2016.
//
//

#include "matrDolorosaCircles.h"

// ----------------------------------------------------------
void matrDolorosaCircles::setup(){
    circles.push_back(matrDolorosaCircle(ofPoint(0.5, 0.25), 150));
    circles.push_back(matrDolorosaCircle(ofPoint(0.5, 0.75), 300));
    circles.push_back(matrDolorosaCircle(ofPoint(0.5, 0.5), 250));
    
    points.push_back(ofPoint());
    speeds.push_back(ofPoint::zero());
    //points.push_back(ofPoint());
    
}

// ----------------------------------------------------------
void matrDolorosaCircles::update(float ratio){
    
    // ----------------------------------------
    // get the indexes relative to ratio
    int idxA, idxB;
    ofPoint thisPoint;
    
    idxA = ratio * circles.size();
    
    if(idxA < circles.size() - 1){
        idxB = idxA+1;
    }else{
        idxB = 0;
    }
    //ofLog() << "idxA = " << idxA << " : " << "idxB = " << idxB;
    
    // Real ratio
    int realSize = circles.size();
    float realRatio = ratio * realSize;
    realRatio = fmod(realRatio, 1.0);
    
    thisPoint = (1-realRatio)*circles[idxA].ratioPos(realRatio) + realRatio*circles[idxB].ratioPos(realRatio);
    speeds[0] = points[0] - thisPoint;
    points[0] = thisPoint;
    
    ofLog() << "idxA = " << idxA << " : " << "idxB = " << idxB << "ratio=" << ratio << " : " << "realRatio=" << realRatio;
    //points[1] = circles[idxB].ratioPos(ratio);
    
}

// ----------------------------------------------------------
void matrDolorosaCircles::draw(){
    // ---------------------------------
    for (int idxPoint = 0; idxPoint < points.size() ; ++idxPoint) {
        ofDrawCircle(points[idxPoint] * ofPoint(ofGetWidth(),ofGetHeight()), 5);
    }
    // ---------------------------------
    for (int idxCircle = 0; idxCircle < circles.size() ; ++idxCircle) {
        circles[idxCircle].draw();
    }
}
