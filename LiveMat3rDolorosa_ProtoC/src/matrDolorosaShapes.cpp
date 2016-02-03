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
    
    shapes.setName("shapes");
    
    shapes.add(drawFbo.set("drawFbo",true));
    shapes.add(drawAs3D.set("drawAs3D",false));
    shapes.add(rootDriver.set("rootDriver",0, 0, 1));
    
    shapes.add(alphaTrails.set("alphaTrails",20,0,255));
    shapes.add(lineWidth.set("lineWidth",1,0,10));
    shapes.add(circleResolution.set("circleResolution",0,0,24));
    shapes.add(nbLinesShapes.set("nbLinesShapes",1,0,10));
    shapes.add(nbRowsShapes.set("nbRowsShapes",1,0,10));
    
    shapes.add(fillNoFill.set("fillNoFill",false));
    
    shapes.add(xOffset.set("xOffset",0,0,background.getWidth()));
    shapes.add(yOffset.set("yOffset",0,0,background.getHeight()));
    shapes.add(xSizeOffset.set("xSizeOffset",0,-1,1));
    shapes.add(ySizeOffset.set("ySizeOffset",0,-1,1));

    panel.setup(shapes);
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8020,"localhost", 8021);
    
    
}

// -----------------------------------------
void matrDolorosaShapes::update(){
    
    sync.update();
//    anim.update(1.0f / (float)ofGetFrameRate());
    
    // ---------- ---------- ---------- ---------- ---------- ----------
    background.begin();
    
    if(drawFbo){
        drawInstructions();
    }else{
        ofPushStyle();
        ofFill();
        ofSetColor(ofColor::black);
        ofDrawRectangle(0, 0, background.getWidth(), background.getHeight());
        ofPopStyle();
    }
    
    background.end();
    
}


// -----------------------------------------
void matrDolorosaShapes::drawInstructions(){
    ofPushStyle(); // Style pushed ------------------------------
    ofPushMatrix();
    
    ofSetCircleResolution(circleResolution);
    ofSetLineWidth(lineWidth);
    
    //    float ratio = anim.val();
    float ratio = rootDriver;
    
    ofFill();
    ofSetColor(ofColor::black, alphaTrails);
    ofDrawRectangle(0,0,background.getWidth(),background.getHeight());
    
    // ---------- ---------- ---------- ---------- ---------- ----------
    if(fillNoFill==true){
        ofFill();
    }else{
        ofNoFill();
    }
    
    ofSetColor(255,255,255);
    
    for (float idxRow = 1; idxRow <= nbRowsShapes; idxRow++) {
        for (float idxLine = 1; idxLine <= nbLinesShapes; idxLine++) {
            ofPushMatrix();
            // -- -- --
            ofPoint pos;
            pos.x = 0.5 * background.getWidth() + ((idxRow-1) - 0.5*(float)(nbRowsShapes-1)) * xOffset;
            pos.y = 0.5 * background.getHeight() + ((idxLine-1) - 0.5*(float)(nbLinesShapes-1)) * yOffset;
            ofTranslate(pos);
            ofScale(1 - xSizeOffset * idxRow, 1 - ySizeOffset * idxLine);
            // -- -- --
            ofDrawCircle(0, 0, 0.5 * (float)background.getWidth() * ratio);
            
            ofSpherePrimitive sphere;
            sphere.set(0.5 * (float)background.getWidth() * ratio, circleResolution);
            sphere.drawWireframe();
                       
//            ofDrawSphere(0.5 * (float)background.getWidth() * ratio);
            // -- -- --
            ofPopMatrix();
        }
    }
    
    
    ofPopMatrix();
    ofPopStyle();// Style poped ------------------------------
    
}

// -----------------------------------------
void matrDolorosaShapes::draw(){
    
    ofPushMatrix();
    ofTranslate(-0.5 * ofGetWidth(), -0.5 * ofGetHeight());
    
    if (drawAs3D) {
        drawInstructions();
    }
   
    ofPopMatrix();
}