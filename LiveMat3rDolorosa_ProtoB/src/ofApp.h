#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxGui.h"

// DEFINE ------------------------
#define guiFileName "settings.xml"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void guiSetup();
    
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    string logStringToView = "";
    
    // GUI Events --------------------------------------------------------------
    void dofEnablePressed();
    void rgbShiftEnablePressed();

    
    ofMesh mesh;
    ofEasyCam cam;
    
    // RENDER PASSES ---------------------------------
    ofxPostProcessing post;
    
    DofPass::Ptr MyDofPass;
    DofAltPass::Ptr MyDofAltPass;
    RGBShiftPass::Ptr MyRGBShiftPass;
    LUTPass::Ptr MyLUTPass;
    
    // GUI
    ofParameter<bool>   dofEnable;
    ofParameter<float>  dofFocus;
    ofParameter<float>  dofAperture;
    ofParameter<float>  dofBlur;
    
    ofParameter<bool>   dofAltPassEnable;
    ofParameter<float>  dofAltFocalDepth;
    ofParameter<float>  dofAltfocalLength;
    ofParameter<float>  dofAltStop;
    ofParameter<bool>   dofAltShowFocus;
    
    ofParameter<bool>   rgbShiftEnable;
    ofParameter<float>  rgbShiftAmount;
    ofParameter<float>  rgbShiftAngle;
    
    ofParameter<ofColor> faceColor;
    ofParameter<ofColor> wireColor;

    ofxPanel gui;
    
};
