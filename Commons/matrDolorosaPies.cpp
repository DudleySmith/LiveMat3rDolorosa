//
//  matrDolorosaPies.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 01/03/2016.
//
//

#include "matrDolorosaPies.h"

// -----------------------------------------
void matrDolorosaPies::setup(){
    
    pgPies.setName("pies");
    
    pgPies.add(nbPies.set("nbPies", 6, 0, nbPiesMax));
    pgPies.add(fillNoFill.set("fillNoFill", false));
    
    pgPies.add(nbRadius.set("nbRadius", 1, 0, nbRadiusMax));
    pgPies.add(radiusFactor.set("radiusFactor", 0, -2, 2));
    pgPies.add(startRadius.set("startRadius", 0.25, 0, 2));
    pgPies.add(endRadius.set("endRadius", 0.05, 0, 2));
    
    pgPies.add(singleAngleStart.set("singleAngleStart", 10, 0, 90));
    pgPies.add(singleAngleEnd.set("singleAngleEnd", 10, 0, 90));
    
    panel.setup(pgPies);
    panel.loadFromFile("pgPies.xml");
    
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8070,"localhost", 8071);
    
}

// -----------------------------------------
void matrDolorosaPies::update(){
    sync.update();
}

// -----------------------------------------
void matrDolorosaPies::draw(){

    ofPushStyle();
    
    if(fillNoFill){
        ofFill();
    }else{
        ofNoFill();
    }
    
    float rootAngle = fmod(0.25 * ofGetElapsedTimef() * 360.0f, 360.0f);
    
    ofPushMatrix();
    ofRotate(rootAngle);
    
    for(float idxRadius = 0; idxRadius < nbRadius; idxRadius++){
    
        float myStartRadius = ofMap(idxRadius, 0, nbRadius, startRadius, endRadius);
        float myEndRadius = myStartRadius * (1 + radiusFactor);
        
        // Main loop that draw anything
        for(float idxPie = 0; idxPie < nbPies; idxPie++){
            
            // Ratio is idx/nb occurences
            float ratioPie = ofMap(idxPie, 0, nbPies, 0.0, 1.0);

            float rootRootAngle = ofMap(ratioPie, 0, 1, 0, 360);
            
            float angleA = rootRootAngle - ofMap(ratioPie, 0, 1, singleAngleStart, singleAngleEnd);
            float angleB = rootRootAngle + ofMap(ratioPie, 0, 1, singleAngleStart, singleAngleEnd);

            drawOnePie(0, 0, myEndRadius * min(ofGetHeight(), ofGetWidth()), myStartRadius * min(ofGetHeight(), ofGetWidth()), angleA, angleB, true, false);
            
        }
        
    }
    ofPopMatrix();
    
    ofPopStyle();
    
}

// -----------------------------------------
void matrDolorosaPies::drawOnePie(float x,float y, float lowRadius, float highRadius, float lowAngle, float highAngle, bool closed, bool radians){

    bool angleWrap = (lowAngle > highAngle); // are we doing the 0/360 wrap?
    int res = 16;
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    if(!radians){
        lowAngle = ofDegToRad(lowAngle);
        highAngle = ofDegToRad(highAngle);
    }
    
    ofBeginShape();

    // Near circle
    //ofLog() << "Near Circle";
    for (int i = 0; i < res; i++){
        float angle = ofMap(i, 0, res, lowAngle, highAngle);
        ofVertex(x + cos(angle) * lowRadius, y - sin(angle) * lowRadius);
    }
    
    // Far circle
    //ofLog() << "Far Circle";
    for (int i = res; i >= 0; i--){
        float angle = ofMap(i, 0, res, lowAngle, highAngle);
        ofVertex(x + cos(angle) * highRadius, y - sin(angle) * highRadius);
    }
    
    // One more point to close all, is the first of near circle
    ofVertex(x + cos(lowAngle) * lowRadius, y - sin(lowAngle) * lowRadius);
    
    ofEndShape();
    
    ofPopMatrix();
    
}
