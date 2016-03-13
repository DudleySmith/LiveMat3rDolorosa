#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxPointCloud.h"
#include "ofxSyphon.h"

#include "matrDolorosaShapes.h"
#include "matrDolorosaCam.h"
#include "matrDolorosaPostFX.h"
#include "matrDolorosaMeshes.h"
#include "matrDolorosaPies.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxPointCloud pointCloud;
    
    matrDolorosaCam cam;
    //ofEasyCam cam;
    
    matrDolorosaShapes  shapes;
    matrDolorosaPostFX  postFx;
    matrDolorosaMeshes  meshes;
    matrDolorosaPies    pies;

    ofxPanel          panel;
    ofParameterGroup  main;
    ofParameter<bool> redrawShapes;
    ofParameter<bool> drawMarks;
    ofParameter<bool> drawUI;
    
    // Syphon output
    ofxSyphonServer syphonServer;
    void setupSyphon();
    
};
