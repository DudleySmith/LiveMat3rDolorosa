#include "ofApp.h"

bool ySort(ofPoint a, ofPoint b){return a.distance(ofPoint::zero()) > b.distance(ofPoint::zero());}

//--------------------------------------------------------------
void ofApp::setup(){
    
    // ------------------------------------
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetColor(255);
    //ofNoFill();
    
    // ------------------------------------
    shapes.setup();
    
    // ------------------------------------
    pointCloud.load("MOTIF.svg");
    pointCloud.setup();
    
    // ------------------------------------
    cam.setup();
    //cam.setPosition(0, 0, 1000);
    //cam.setTarget(ofVec3f::zero());
    
    // ------------------------------------
    postFx.setup();
    
    // ------------------------------------
    meshes.setup();
    
    // ------------------------------------
    field.setup();
    
    // ------------------------------------
    fluid.setup();
    
    // ------------------------------------
    syphonServer.setName("matrDolorosaGenerative");
    
    // ------------------------------------
    main.setName("main");
    main.add(drawUI.set("drawUI", true));
    main.add(redrawShapes.set("redrawShapes", false));
    main.add(drawMarks.set("drawMarks", false));
    
    panel.setup(main);
    panel.loadFromFile("main.xml");

    panel.setPosition(getPanelX(), 10);
    meshes.panel.setPosition(getPanelX(), 90); idxPanel++;
    shapes.panel.setPosition(getPanelX(), 10); idxPanel++;
    pointCloud.panelAnims.setPosition(getPanelX(), 10);
    pointCloud.panelDraws.setPosition(getPanelX(), 290); idxPanel++;
    cam.panel.setPosition(getPanelX(), 10);
    postFx.panel.setPosition(getPanelX(), 250); idxPanel++;
    field.panel.setPosition(getPanelX(), 10); idxPanel++;
    fluid.panel.setPosition(getPanelX(), 10); idxPanel++;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // ------------------------------------
    shapes.update();
    
    // ------------------------------------
    pointCloud.hasToDrawMarks = drawMarks;
    pointCloud.update();

    // ------------------------------------
    postFx.update();
    
    // ------------------------------------
    meshes.update();
    
    // ------------------------------------
    field.update();
    
    // ------------------------------------
    if(field.drawField){
        for(int i = 0; i < field.getNbNodes(); i++) {
            matrDolorosaNode oneNode = field.getNodes()[i];
            ofPoint pos = oneNode.getPosition() / ofGetWindowSize();
            
            pos.x = ofMap(pos.x, -1, 1, 0, 1);
            pos.y = ofMap(pos.y, -1, 1, 0, 1);

            fluid.addToFluid(pos, oneNode.getVecSpeed()/ ofGetWindowSize(), true, true);
        }
    }
    fluid.update();
    // ------------------------------------
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::black);
    
    postFx.post.begin(cam);
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
    
    // ------------------------------------
    meshes.draw();
    
    // ------------------------------------
    //pies.draw();
    
    // --------------------------------------------------------------------------
    ofPushMatrix();
    ofTranslate(-0.5*ofGetWidth(), -0.5*ofGetHeight());
    fluid.draw();
    ofPopMatrix();
    
    // ------------------------------------
    field.draw();
    
    cam.end();
    postFx.post.end();
    
    // Publish syphon before GUI ;)
    syphonServer.publishScreen();
    
    // ------------------------------------
    if(drawUI){
    
        ofDrawBitmapString(ofToString(ofGetFrameRate()),20,ofGetHeight() - 20);
        
        panel.draw();
        pointCloud.panelAnims.draw();
        pointCloud.panelDraws.draw();
        shapes.panel.draw();
        postFx.panel.draw();
        cam.panel.draw();
        meshes.panel.draw();
        field.panel.draw();
        fluid.panel.draw();
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Hide UI -----------------------------------------------
    if(key == 'h'){
        if(drawUI == true){
            drawUI = false;
        }else{
            drawUI = true;
        }
    }
    
    // Take a picture ------------------------------------------
    if(key == 's'){
        ofImage grab;
        grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        grab.save(ofGetTimestampString()+".jpg");
    }
    
//    // Take a picture ------------------------------------------
//    if(key == 'k'){
//        cam.recordCam();
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    // Take a picture ------------------------------------------
    if(key == 'k'){
        cam.recordCam();
    }
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
