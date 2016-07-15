#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    text.setup();
    text.setAnimScaleIn(false);
    text.setAnimFadeIn(true);
}

//--------------------------------------------------------------
void ofApp::update(){
//    text.setWord(ofToString(ofGetElapsedTimef()));
    text.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::darkGray, ofColor::black);
    text.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 13){
        text.setWord(newWord);
        newWord = "";
    }else{
        newWord += key;
    }
    
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