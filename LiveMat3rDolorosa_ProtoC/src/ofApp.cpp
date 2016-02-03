#include "ofApp.h"

bool ySort(ofPoint a, ofPoint b){return a.distance(ofPoint::zero()) > b.distance(ofPoint::zero());}

//--------------------------------------------------------------
void ofApp::setup(){
    
    // ------------------------------------
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetColor(255);
    ofNoFill();
    
    // ------------------------------------
    shapes.setup();
    
    // ------------------------------------
    pointCloud.load("MOTIF.svg");
    pointCloud.setup();
    
    // ------------------------------------
    cam.setup();
    cam.setPosition(0, 0, 1000);
    cam.setTarget(ofVec3f::zero());
    
    // ------------------------------------
    panel.setup();
    panel.add(redrawShapes.set("redrawShapes", false));
    panel.add(drawMarks.set("drawMarks", false));
    
    panel.setPosition(10, 10);
    shapes.panel.setPosition(200, 10);
    pointCloud.panel.setPosition(400, 10);
    cam.panel.setPosition(600, 10);
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    // ------------------------------------
    shapes.update();
    
    // ------------------------------------
    pointCloud.hasToDrawMarks = drawMarks;
    pointCloud.update();
    
    // ------------------------------------
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    cam.begin();
    
    // ------------------------------------
    if(redrawShapes == true){
        float scaleFactor = 0.25;
        
        ofPushMatrix();
        
        ofTranslate(-0.5 * ofGetWidth(), - 0.5 * ofGetHeight());
        //ofTranslate(scaleFactor * 0.5 * ofGetWidth(), scaleFactor * 0.5 * ofGetHeight());
        
        ofScale(scaleFactor, scaleFactor);
        
        shapes.background.draw(0,0);
        
        if(drawMarks){
            ofDrawRectangle(0, 0, shapes.background.getWidth(), shapes.background.getHeight());
        }
        
        ofPopMatrix();
    }
    
    // ------------------------------------
    if (drawMarks) {
        ofPushStyle();
        ofFill();
        ofSetColor(ofColor::orange, 50);
        ofDrawRectangle(-0.5 * ofGetWidth(), - 0.5 * ofGetHeight(), ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }
    
    shapes.draw();
    // ------------------------------------
    pointCloud.draw(shapes.background);
    
    cam.end();
    
    // ------------------------------------
    panel.draw();
    pointCloud.panel.draw();
    shapes.panel.draw();
    cam.panel.draw();
    
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
