#include "ofApp.h"

bool ySort(ofPoint a, ofPoint b){return a.distance(ofPoint::zero()) > b.distance(ofPoint::zero());}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofBackground(0);
    
    ofSetColor(255);
    ofNoFill();
    
    // ------------------------------------
    shapes.setup();
    // ------------------------------------
    pointCloud.load("MOTIF.svg");
    pointCloud.setup();
}


//--------------------------------------------------------------
void ofApp::update(){
    
    // ------------------------------------
    shapes.update();
    // ------------------------------------
    pointCloud.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    cam.begin();
    
    // ------------------------------------
    shapes.draw();
    // ------------------------------------
    pointCloud.draw();
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
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
