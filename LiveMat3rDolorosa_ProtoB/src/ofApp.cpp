#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    guiSetup();
    
    //mesh.load("Arbor.ply");
    mesh.load("lofi-bunny.ply");
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    ofBackground(25);
    
    // INIT PASSES ----------------------------------------
    post.init(ofGetWidth(), ofGetHeight());
    MyDofPass = post.createPass<DofPass>();
    MyDofAltPass = post.createPass<DofAltPass>();
    MyRGBShiftPass = post.createPass<RGBShiftPass>();
    
}

//--------------------------------------------------------------
void ofApp::guiSetup(){
    
    gui.setup("matrDolorsa");
    
    //float focus = 0.985, float aperture = 0.8, float maxBlur = 0.6
    gui.add(dofEnable.set("dofEnable", true));
    gui.add(dofFocus.set("dofFocus", 0.985, 0.9, 1.0));
    gui.add(dofAperture.set("dofAperture", 1.2, 1.0, 2.0));
    gui.add(dofBlur.set("dofBlur", 0.6, 0.0, 1.0));
    
    //DofAltPass(const ofVec2f& aspect, bool arb, float focalDepth = 1.f, float focalLength = 500.f, float fStop = 3.f, bool showFocus = false);
    gui.add(dofAltPassEnable.set("dofAltPassEnable", true));
    gui.add(dofAltFocalDepth.set("dofAltFocalDepth", 1.0, 0.0, 5.0));
    gui.add(dofAltfocalLength.set("dofAltfocalLength", 500.0, 0.0, 1000.0));
    gui.add(dofAltStop.set("dofAltStop", 3.0, 0.0, 6.0));
    gui.add(dofAltShowFocus.set("dofAltShowFocus", true));
    
    //RGBShiftPass(const ofVec2f& aspect, bool arb, float amount = 0.005, float angle = 0.0);
    gui.add(rgbShiftEnable.set("rgbShiftEnable", true));
    gui.add(rgbShiftAmount.set("rgbShiftAmount", 0.01, 0.0, 0.5));
    gui.add(rgbShiftAngle.set("rgbShiftAngle", 0, 0, 360));
    
    gui.add(faceColor.set("faceColor", ofColor(255,255,255,20), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    gui.add(wireColor.set("wireColor", ofColor(255,255,255,20), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    
    gui.loadFromFile(guiFileName);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    MyDofPass->setEnabled(dofEnable);
    MyDofPass->setFocus(dofFocus);
    MyDofPass->setAperture(dofAperture);
    MyDofPass->setMaxBlur(dofBlur);
    
    MyDofAltPass->setEnabled(dofAltPassEnable);
    MyDofAltPass->setFocalDepth(dofAltFocalDepth);
    MyDofAltPass->setFocalLength(dofAltfocalLength);
    MyDofAltPass->setShowFocus(dofAltShowFocus);
    
    MyRGBShiftPass->setEnabled(rgbShiftEnable);
    MyRGBShiftPass->setAmount(rgbShiftAmount);
    MyRGBShiftPass->setAngle(ofDegToRad(rgbShiftAngle));

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

    glPointSize(2);
    
    // begin scene to post process
    post.begin(cam);
    cam.begin();
    
    // PUSH Faces -----------------------------------
    ofPushMatrix();
    ofPushStyle();
        ofSetColor(faceColor);
        mesh.drawFaces();
    ofPopStyle();
    ofPopMatrix();
    
    // PUSH Wireframe ------------------------
    ofPushMatrix();
    ofPushStyle();
        ofSetColor(wireColor);
        ofSetLineWidth(1);
        mesh.drawWireframe();
        mesh.drawVertices();
    ofPopStyle();
    ofPopMatrix();
    
    // end scene and draw
    cam.end();
    post.end();
    
    // DRAW GUI
    gui.draw();
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + " : " + logStringToView, 10, ofGetHeight() - 10);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 's'){
        gui.saveToFile(guiFileName);
        logStringToView = "Saved file : " + ofToString(guiFileName);
    }
    else if(key == 'l'){
        gui.loadFromFile(guiFileName);
        logStringToView = "Loaded file : " + ofToString(guiFileName);
    }

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

