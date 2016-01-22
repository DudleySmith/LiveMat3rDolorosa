#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(20);
    
    // GL_REPEAT for texture wrap only works with NON-ARB textures //
    ofDisableArbTex();
    texture.load("of.png");
    texture.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    vidGrabber.setup(640, 480, true);
    
    bFill       = true;
    bWireframe  = true;
    bDrawNormals= false;
    bDrawAxes   = false;
    bDrawLights = false;
    bInfoText   = true;
    bMousePressed   = false;
    bSplitFaces = false;
    
    float width     = ofGetWidth() * .12;
    float height    = ofGetHeight() * .12;
    
    icoSphere.setRadius( width );

    mode = 0;
    
    ofSetSmoothLighting(true);
//    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
//    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
//    
//    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
//    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
//    
//    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
//    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    pointLight.setDiffuseColor(ofColor::white);
    pointLight.setSpecularColor(ofColor::white);
    
    pointLight2.setDiffuseColor(ofColor::white);
    pointLight2.setSpecularColor(ofColor::white);
    
    pointLight3.setDiffuseColor(ofColor::white);
    pointLight3.setSpecularColor(ofColor::white);

    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 60));
    material.setDiffuseColor(ofColor(10,10,10,50));
    
    ofSetSphereResolution(24);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );
    
    //ofSetWindowTitle("Framerate: "+ofToString(ofGetFrameRate(), 0));
    if(mode == 2 || ofGetElapsedTimef() < 10) {
        vidGrabber.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    if(bMousePressed) {
        spinX = spinY = 0.0f;
    }
    
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
    
    
    if(mode == 1 || mode == 3) texture.getTexture().bind();
    if(mode == 2) vidGrabber.getTexture().bind();
    
    // ICO Sphere //
    icoSphere.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    icoSphere.rotate(spinX, 1.0, 0.0, 0.0);
    icoSphere.rotate(spinY, 0, 1.0, 0.0);
    
    if(mode == 3) {
        triangles = icoSphere.getMesh().getUniqueFaces();

        float angle = (ofGetElapsedTimef() * 0.4);
        ofVec3f faceNormal;
        for(size_t i = 0; i < triangles.size(); i++ ) {
            float frc = ofSignedNoise(angle * (float)i * .01, angle*.05) * 4;
            faceNormal = triangles[i].getFaceNormal();
            for(int j = 0; j < 3; j++ ) {
                triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * frc );
            }
        }
        icoSphere.getMesh().setFromTriangles( triangles );
    }
    
    if(bFill) {
        //material.begin();
        ofFill();
        ofSetColor(ofColor::black, 100);
        icoSphere.draw();
        //material.end();
    }
    
    if(bWireframe) {
        ofNoFill();
        ofSetColor(ofColor::white);
        icoSphere.setScale(1.01f);
        icoSphere.drawWireframe();
        icoSphere.setScale(1.f);
    }
    
    
    if(!bFill && bWireframe){
        material.end();
    }
    
    if(mode == 1 || mode == 3) texture.getTexture().unbind();
    if(mode == 2) vidGrabber.getTexture().unbind();
    
    material.end();
    ofDisableLighting();
    
    if(bDrawLights) {
        ofFill();
        ofSetColor(pointLight.getDiffuseColor());
        pointLight.draw();
        ofSetColor(pointLight2.getDiffuseColor());
        pointLight2.draw();
        ofSetColor(pointLight3.getDiffuseColor());
        pointLight3.draw();
    }
    
    if(bDrawNormals) {
        ofSetColor(225, 0, 255);
        icoSphere.drawNormals(20, bSplitFaces);
    }
    if(bDrawAxes) {
        icoSphere.drawAxes(icoSphere.getRadius()+30);
    }
    
    ofDisableDepthTest();
    
    ofFill();
    /*
    ofSetColor(0);
    ofDrawRectangle(icoSphere.getPosition().x-154, icoSphere.getPosition().y + 120, 168, 24);
    ofSetColor(255);
    ofDrawBitmapString("ofIcoSpherePrimitive", icoSphere.getPosition().x-150, icoSphere.getPosition().y+136 );
    */
    if(bInfoText) {
        stringstream ss;
        ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
        ss << "(f): Toggle Fullscreen"<<endl<<"(s): Draw Solid Shapes"<<endl<<"(w): Draw Wireframes"<<endl;
        ss <<"(1/2/3/4): Set Resolutions" <<endl<<"(n): Draw Normals"<<"\n(LEFT/RIGHT): Set Mode "<<ofToString(mode,0)<<endl;
        ss <<"(z): Split Faces " <<bSplitFaces<<endl;
        ss <<"(a): Draw Axes"<<endl<<"(l): Render lights"<<endl<<"(t): Info Text"<<endl;
        
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }
    
    if(bGrabScreen){
        ofImage grab;
        grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        grab.save(ofGetTimestampString()+".jpg");
        
        bGrabScreen = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            bFill = !bFill;
            break;
        case 'w':
            bWireframe = !bWireframe;
            break;
        case '1':
            bSplitFaces=false;
            // icosahedron //
            icoSphere.setResolution(0); // number of subdivides //
            break;
        case '2':
            bSplitFaces=false;
            icoSphere.setResolution(1);
            break;
        case '3':
            bSplitFaces=false;
            icoSphere.setResolution(2);
            break;
        case '4':
            bSplitFaces=false;
            icoSphere.setResolution(4);
            break;
        case 'n':
            bDrawNormals = !bDrawNormals;
            break;
        case OF_KEY_RIGHT:
            mode++;
            if(mode > 3) mode = 0;
            break;
        case OF_KEY_LEFT:
            mode--;
            if(mode < 0) mode = 3;
            break;
        case 'a':
            bDrawAxes = !bDrawAxes;
            break;
        case 'l':
            bDrawLights = !bDrawLights;
            break;
        case 't':
            bInfoText=!bInfoText;
            break;
        case 'z':
            bSplitFaces = !bSplitFaces;
            
            if(mode == 3) bSplitFaces = false;
            
            if(bSplitFaces) {
                icoSphere.setMode( OF_PRIMITIVE_TRIANGLES );
                triangles = icoSphere.getMesh().getUniqueFaces();
                icoSphere.getMesh().setFromTriangles(triangles, true);
                
            } else {
                // vertex normals are calculated with creation, set resolution //
                icoSphere.setResolution( icoSphere.getResolution() );
            }
            break;
        case 'c':
            bGrabScreen = true;
            

    }
    
    if(mode == 1) {
        icoSphere.mapTexCoordsFromTexture( texture.getTexture() );
    }
    
    if(mode == 2) {
        icoSphere.mapTexCoordsFromTexture( vidGrabber.getTexture() );
    }
    
    //
    if( mode == 3 ) {
//        
//        bSplitFaces = false;
//        
//        // if the faces were split, we can get some weird results, since we
//        // might not know what the new strides were,
//        // so reset the primitives by calling their setMode function
//        // which recreates the mesh with the proper indicies //
//        icoSphere.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//        
//        // rebuild the box,
//        icoSphere.mapTexCoords(0, 0, 5, 5);
//        
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
    bMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePressed = false;
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
