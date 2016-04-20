#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofSetVerticalSync(false);
    
    // --
    field.setup();
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
    
    // --
    field.update();
    
    // One point (left -> right)
    oneVel.x = pSpeedX;
    oneVel.y = pSpeedY;
    onePoint += (oneSens*oneVel);
    
    if(onePoint.x > ofGetWidth() || onePoint.x < 0)
        oneSens.x *= -1;
    if(onePoint.y > ofGetHeight() || onePoint.y < 0)
        oneSens.y *= -1;
    
    // ----------------
    float ratio = fmod(ofGetElapsedTimeMillis(), 10000) / 10000;
    
    for(int i = 0; i < field.getNbNodes(); i++) {
        matrDolorosaNode oneNode = field.getNodes()[i];
        ofPoint pos = oneNode.getPosition() / ofGetWindowSize();
        
        pos.x = ofMap(pos.x, -1, 1, 0, 1);
        pos.y = ofMap(pos.y, -1, 1, 0, 1);
        
        ofLog() << "pos = " << pos;
        
        ofDrawCircle(pos, 20);
        
        fluid.addToFluid(pos, oneNode.getVecSpeed()/ ofGetWindowSize(), true, true);
    }

    //fluid.addToFluid(onePoint / ofGetWindowSize(), oneVel / ofGetWindowSize(), true, true);
    
    fluid.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    // --------------------------------------------------------------------------
    ofDrawCircle(onePoint.x, onePoint.y, 5.0);
    
    // --------------------------------------------------------------------------
    ofPushMatrix();
    ofTranslate(-0.5*ofGetWidth(), -0.5*ofGetHeight());
    fluid.draw();
    ofPopMatrix();
    
    // --------------------------------------------------------------------------
    field.draw();
    
    cam.end();
    
    // --------------------------------------------------------------------------
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    // GUI --
    panel.draw();
    field.panel.draw();
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