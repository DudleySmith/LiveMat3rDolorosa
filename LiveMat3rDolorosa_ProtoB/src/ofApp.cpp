#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    
    guiSetup();
    
    //mesh.load("Arbor.ply");
    //mesh.load("lofi-bunny.ply");
    ofFile meshExists = ofFile("ANGE_MIDDLE.obj");
    if (meshExists.exists()) {
        loader.loadModel(meshExists.path());
        mesh = loader.getMesh(0);
        ofLogNotice() << "Mesh loaded :  Nb Meshes:" << ofToString(loader.getMeshCount());
    }else{
        ofLogError() << "CRAP : The mesh is not loaded ! " + meshExists.path();
        
    }
    
    // INIT PASSES --------------------------------------
    post.init(ofGetWidth(), ofGetHeight());
    MyRGBShiftPass = post.createPass<RGBShiftPass>();
    MyZoomBlurPass = post.createPass<ZoomBlurPass>();
    MyDofAltPass = post.createPass<DofAltPass>();
    
}

//--------------------------------------------------------------
void ofApp::guiSetup(){
    
    gui.setup("matrDolorsa");
    
    //DofAltPass(const ofVec2f& aspect, bool arb, float focalDepth = 1.f, float focalLength = 500.f, float fStop = 3.f, bool showFocus = false);
    gui.add(dofAltPassEnable.set("dofAltPassEnable", true));
    gui.add(dofAltFocalDepth.set("dofAltFocalDepth", 1.0, 0.5, 200.0));
    gui.add(dofAltfocalLength.set("dofAltfocalLength", 1.0, 0.5, 200.0));
    gui.add(dofAltStop.set("dofAltStop", 5.0, 0.5, 200.0));
    gui.add(dofAltShowFocus.set("dofAltShowFocus", true));
    
    //RGBShiftPass(const ofVec2f& aspect, bool arb, float amount = 0.005, float angle = 0.0);
    gui.add(rgbShiftEnable.set("rgbShiftEnable", true));
    gui.add(rgbShiftAmount.set("rgbShiftAmount", 0.0, 0.0, 0.05));
    gui.add(rgbShiftAngle.set("rgbShiftAngle", 0, 0, 360));
    
    //float exposure = 0.48, float decay = 0.9, float density = 0.25, float weight = 0.25, float clamp = 1);
    gui.add(zoomBlurEnable.set("zoomBlurEnable", true));
    gui.add(zoomBlurExposure.set("zoomBlurExposure", 0.48, 0.0, 1.0));
    gui.add(zoomBlurDecay.set("zoomBlurDecay", 0.9, 0.0, 1.0));
    gui.add(zoomBlurDensity.set("zoomBlurDensity", 0.25, 0.0, 1.0));
    gui.add(zoomBlurWeight.set("zoomBlurWeight", 0.25, 0.0, 1.0));
    
    gui.add(faceColor.set("faceColor", ofColor(255,255,255,0), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    gui.add(wireColor.set("wireColor", ofColor(255,255,255,255), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    
    gui.loadFromFile(guiFileName);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    MyDofAltPass->setEnabled(dofAltPassEnable);
    MyDofAltPass->setFocalDepth(dofAltFocalDepth);
    MyDofAltPass->setFocalLength(dofAltfocalLength);
    MyDofAltPass->setShowFocus(dofAltShowFocus);
    
    MyRGBShiftPass->setEnabled(rgbShiftEnable);
    MyRGBShiftPass->setAmount(rgbShiftAmount);
    MyRGBShiftPass->setAngle(ofDegToRad(rgbShiftAngle));
    
    MyZoomBlurPass->setEnabled(zoomBlurEnable);
    MyZoomBlurPass->setDecay(zoomBlurDecay);
    MyZoomBlurPass->setDensity(zoomBlurDensity);
    MyZoomBlurPass->setExposure(zoomBlurExposure);
    MyZoomBlurPass->setWeight(zoomBlurWeight);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // copy enable part of gl state
    //glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    //glEnable (GL_COLOR_MATERIAL);

    //glPointSize(2);
    
    // begin scene to post process
    post.begin(cam);
    cam.begin();
    
    //ofDrawAxis(200);
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPushMatrix();
    ofRotateX(180);
    
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
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPushMatrix();
    ofDrawAxis(200);
    
    // end scene and draw
    cam.end();
    post.end();
    
    ofPopMatrix();
    
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

