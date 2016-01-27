#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    ofEnableAntiAliasing();
    
    //ofEnableSmoothing();
    
    guiSetup();
    
    //mesh.load("Arbor.ply");
    //mesh.load("lofi-bunny.ply");
    ofFile meshExists = ofFile("ANGE_LESS_Exported.obj");
    if (meshExists.exists()) {
        loader.loadModel(meshExists.path());
        mesh = loader.getMesh(0);
        ofLogNotice() << "Mesh loaded :  Nb Meshes:" << ofToString(loader.getMeshCount());
        
    }else{
        ofLogError() << "CRAP : The mesh is not loaded ! " + meshExists.path();
        
    }
    
   // INIT PASSES --------------------------------------
    post.init(ofGetWidth(), ofGetHeight());
    dofAltPass = post.createPass<DofAltPass>();
    zoomBlurPass = post.createPass<ZoomBlurPass>();
    rgbShiftPass = post.createPass<RGBShiftPass>();
    
    // INIT CAM ----------------------------------------
    outCam.setOrientation(ofVec3f(90, 0, 0));
    
}

//--------------------------------------------------------------
void ofApp::guiSetup(){
    
    // RENDER --------------------------------------------
    renderPanel.setup("matrDolorsa");
    
    //DofAltPass(const ofVec2f& aspect, bool arb, float focalDepth = 1.f, float focalLength = 500.f, float fStop = 3.f, bool showFocus = false);
    renderPanel.add(dofAltPassEnable.set("dofAltPassEnable", true));
    renderPanel.add(dofAltFocalDepth.set("dofAltFocalDepth", 1.0, 0.5, 500.0));
    renderPanel.add(dofAltfocalLength.set("dofAltfocalLength", 1.0, 0.5, 500.0));
    renderPanel.add(dofAltStop.set("dofAltStop", 5.0, 0.5, 200.0));
    renderPanel.add(dofAltShowFocus.set("dofAltShowFocus", true));
    
    //RGBShiftPass(const ofVec2f& aspect, bool arb, float amount = 0.005, float angle = 0.0);
    renderPanel.add(rgbShiftEnable.set("rgbShiftEnable", true));
    renderPanel.add(rgbShiftAmount.set("rgbShiftAmount", 0.0, 0.0, 0.05));
    renderPanel.add(rgbShiftAngle.set("rgbShiftAngle", 0, 0, 360));
    
    //float exposure = 0.48, float decay = 0.9, float density = 0.25, float weight = 0.25, float clamp = 1);
    renderPanel.add(zoomBlurEnable.set("zoomBlurEnable", true));
    renderPanel.add(zoomBlurExposure.set("zoomBlurExposure", 0.48, 0.0, 1.0));
    renderPanel.add(zoomBlurDecay.set("zoomBlurDecay", 0.9, 0.0, 1.0));
    renderPanel.add(zoomBlurDensity.set("zoomBlurDensity", 0.25, 0.0, 1.0));
    renderPanel.add(zoomBlurWeight.set("zoomBlurWeight", 0.25, 0.0, 1.0));
    
    renderPanel.add(faceColor.set("faceColor", ofColor(255,255,255,0), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    renderPanel.add(wireColor.set("wireColor", ofColor(255,255,255,255), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    
    renderPanel.loadFromFile(renderPanelFileName);
    
    
    // CAMERA --------------------------------------------
    cameraPanel.setup("camera");
    
    cameraPanel.add(camPosX.setup("Pos X", 0, -1000, 200));
    cameraPanel.add(camPosY.setup("Pos Y", 0, -1000, 200));
    cameraPanel.add(camPosZ.setup("Pos Z", 0, -1000, 200));
    
    cameraPanel.add(camRotX.setup("Rot X", 0, 0, 360));
    cameraPanel.add(camRotY.setup("Rot Y", 0, 0, 360));
    cameraPanel.add(camRotZ.setup("Rot Z", 0, 0, 360));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Lerp position --> it will go in class soon
    ofPoint pos;
    float amplitude = 400;
    float speed = 0.1;
    float relativeTime = ofGetElapsedTimef() * speed;
    float ratio = abs(relativeTime - ceil(relativeTime));
    float sinRatio = sin(TWO_PI * ratio);
    //
    pos = outCam.getPosition();
    pos.y = ofLerp(-amplitude, amplitude, sinRatio);
    
    outCam.setGlobalPosition(pos);
    
    camPosX = outCam.getGlobalPosition().x;
    camPosY = outCam.getGlobalPosition().y;
    camPosZ = outCam.getGlobalPosition().z;
    camRotX = outCam.getOrientationEuler().x;
    camRotY = outCam.getOrientationEuler().y;
    camRotZ = outCam.getOrientationEuler().z;
    
    dofAltPass->setEnabled(dofAltPassEnable);
    dofAltPass->setFocalDepth(dofAltFocalDepth);
    dofAltPass->setFocalLength(dofAltfocalLength);
    dofAltPass->setShowFocus(dofAltShowFocus);
    
    rgbShiftPass->setEnabled(rgbShiftEnable);
    rgbShiftPass->setAmount(rgbShiftAmount);
    rgbShiftPass->setAngle(ofDegToRad(rgbShiftAngle));
    
    zoomBlurPass->setEnabled(zoomBlurEnable);
    zoomBlurPass->setDecay(zoomBlurDecay);
    zoomBlurPass->setDensity(zoomBlurDensity);
    zoomBlurPass->setExposure(zoomBlurExposure);
    zoomBlurPass->setWeight(zoomBlurWeight);
    
    
    
    
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
    post.begin(outCam);
    outCam.begin();
    
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
    ofPopMatrix();
    //ofDrawAxis(200);
    
    // end scene and draw
    outCam.end();
    post.end();
    
    // DRAW GUI
    renderPanel.draw();
    cameraPanel.draw();
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + " : " + logStringToView, 10, ofGetHeight() - 10);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 's'){
        renderPanel.saveToFile(renderPanelFileName);
        logStringToView = "Saved file : " + ofToString(renderPanelFileName);
    }
    else if(key == 'l'){
        renderPanel.loadFromFile(renderPanelFileName);
        logStringToView = "Loaded file : " + ofToString(renderPanelFileName);
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

