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
    syphonServer.setName("matrDolorosaGenerative");
    
    // ------------------------------------
    main.setName("main");
    main.add(drawUI.set("drawUI", true));
    main.add(redrawShapes.set("redrawShapes", false));
    main.add(drawMarks.set("drawMarks", false));
    
    panel.setup(main);
    panel.loadFromFile("main.xml");
    
    panel.setPosition(10, 10);
    shapes.panel.setPosition(210, 10);
    pointCloud.panelAnims.setPosition(420, 10);
    pointCloud.panelDraws.setPosition(420, 290);
    cam.panel.setPosition(630, 10);
    postFx.panel.setPosition(630, 210);
    meshes.panel.setPosition(10, 90);
    
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
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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

    cam.end();
    postFx.post.end();
    
    // Publish syphon before GUI ;)
    syphonServer.publishScreen();
    
    // ------------------------------------
    if(drawUI){
    
        ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
        
        panel.draw();
        pointCloud.panelAnims.draw();
        pointCloud.panelDraws.draw();
        shapes.panel.draw();
        postFx.panel.draw();
        cam.panel.draw();
        meshes.panel.draw();
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
