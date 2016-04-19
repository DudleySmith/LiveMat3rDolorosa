//
//  matrDolorosaPies.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 01/03/2016.
//
//

#include "matrDolorosaPie.h"

// -----------------------------------------
void matrDolorosaPie::update(){
    
}

// -----------------------------------------
void matrDolorosaPie::draw(float x,float y, float radius, float lowAngle, float highAngle, bool closed, bool radians){
    
    
    //    if (!bSetupCircle) setupCircle();
    //
    //    // use smoothness, if requested:
    //    if (bSmoothHinted && drawMode == OF_OUTLINE) startSmoothing();
    
    ofBeginShape();
    
    lowAngle = fmod(lowAngle,360.0f);
    highAngle = fmod(highAngle,360.0f);
    
    bool angleWrap = (lowAngle > highAngle); // are we doing the 0/360 wrap?
    int res = 16;
    
    if(!radians){
        lowAngle = ofDegToRad(lowAngle);
        highAngle = ofDegToRad(highAngle);
    }
    
    float angle = lowAngle;
    float angleRange = ((!angleWrap)?(highAngle - lowAngle):(M_TWO_PI - lowAngle + highAngle));
    float angleAdder = angleRange / (float)res;
    
    //initial points
    ofVertex(x, y);
    
    for (int i = 0; i < res; i++){
        ofVertex(x + cos(angle) * radius, y - sin(angle) * radius);
        angle += angleAdder;
    }
    
    //final point
    ofVertex(x, y);
    
    ofEndShape();
    
}