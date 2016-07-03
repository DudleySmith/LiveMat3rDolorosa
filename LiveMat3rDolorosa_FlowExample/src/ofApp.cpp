#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // --------------------------------------------
    //    text.setup();
    //    text.setAnimScaleOut(false);
    //    text.setAnimFadeOut(true);
    // --------------------------------------------
    fontBlend.setup();
    fontBlend.panel.setPosition(250, 10);
    // --------------------------------------------
//    fade.load("Wandering stars Fade.mp4");
//    fade.setLoopState(OF_LOOP_NORMAL);
//    fade.play();
    // --------------------------------------------
//    zoom.load("Wandering stars Zoom.mp4");
//    zoom.setLoopState(OF_LOOP_NORMAL);
//    zoom.play();
    // --------------------------------------------
    flowTool.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // --------------------------------------------
    //text.update();
    fontBlend.update();
    
    // --------------------------------------------
    flowTool.flowSourceFboBegin();
    ofClear(0);
    
    drawText();
    // Videos --
    // --
    //fade.update();
    //fade.draw(-0.5 * flowTool.drawnFbo.getWidth(), -0.25 * flowTool.drawnFbo.getHeight());
    // --
    //zoom.update();
    //zoom.draw(-0.5 * flowTool.drawnFbo.getWidth(), -0.25 * flowTool.drawnFbo.getHeight());
    
    flowTool.flowSourceFboEnd();
    // --------------------------------------------
    
    flowTool.update();
}

//--------------------------------------------------------------
void ofApp::drawText(){
    
    ofPushMatrix();
    
    ofTranslate(-0.5 * flowTool.drawnFbo.getWidth(), -0.25 * flowTool.drawnFbo.getHeight());
    fontBlend.draw();
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // --------------------------------------------
    flowTool.draw();
    
    // --------------------------------------------
    if (flowTool.toggleGuiDraw) {
        fontBlend.panel.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    flowTool.keyPressed(key);
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