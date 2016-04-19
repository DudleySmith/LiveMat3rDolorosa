#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofSetVerticalSync(false);
    // --
    fluid.setup();
    // --
    pgPoints.setName("points");
    pgPoints.add(pSpeedX.set("pSpeedX", 0.0, -5.0, 5.0));
    pgPoints.add(pSpeedY.set("pSpeedY", 0.0, -5.0, 5.0));
    panel.setup(pgPoints);
    // --
    onePoint.x = 0.5*ofGetWidth();
    onePoint.y = 0.5*ofGetHeight();
    oneSens.x = 1.0;
    oneSens.y = 1.0;
    
    panel.setPosition(10, 25);
    fluid.panel.setPosition(10, 100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // One point (left -> right)
    oneVel.x = pSpeedX;
    oneVel.y = pSpeedY;
    onePoint += (oneSens*oneVel);
    
    if(onePoint.x > ofGetWidth() || onePoint.x < 0)
        oneSens.x *= -1;
    if(onePoint.y > ofGetHeight() || onePoint.y < 0)
        oneSens.y *= -1;
    
    fluid.addToFluid(onePoint / ofGetWindowSize(), oneVel / ofGetWindowSize(), true, true);
    
    fluid.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // --------------------------------------------------------------------------
    ofDrawCircle(onePoint.x, onePoint.y, 5.0);
    // --------------------------------------------------------------------------
    fluid.draw();
    
    // --------------------------------------------------------------------------
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    
    // GUI --
    panel.draw();
    fluid.panel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    //fluid.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //fluid.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}