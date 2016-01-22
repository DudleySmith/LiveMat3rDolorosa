#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    radius = ofGetHeight()/3;
    
    m_aPelos = vector<ofPelo>();
    
    for (int i=0; i<nbPelos; i++) {
        m_aPelos.push_back(ofPelo(radius));
    }
    
    bGrabScreen = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::darkGrey, ofColor::black);
    
    cam.begin();
    ofNoFill();
    ofEnableAlphaBlending();
    ofSetColor(ofColor::white, 50);
    
    //ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
    
    for (std::vector<ofPelo>::iterator it = m_aPelos.begin() ; it != m_aPelos.end(); ++it){
        it->draw();
    }
    cam.end();
    
    if(bGrabScreen){
        ofImage grab;
        grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        grab.save(ofGetTimestampString()+".jpg");
        
        bGrabScreen = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'c'){
        bGrabScreen = true;
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
