#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    field.setup();
    //smooth(8);
}

//--------------------------------------------------------------
void ofApp::update(){
    field.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();

    field.draw();
    
    if(grab==true){
    ofImage myScreen;
    myScreen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    myScreen.save(ofGetTimestampString()+".jpg");
        grab = false;
    }
    
    cam.end();
    
    field.panel.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Take a picture ------------------------------------------
    if(key == 's'){
        grab = true;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
