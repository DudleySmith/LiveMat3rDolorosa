#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

// DEFINE ------------------------
#define renderPanelFileName "render.xml"

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
    
    ofLog   log;
    string  logStringToView = "";
    
    // GUI Events --------------------------------------------------------------
    void dofEnablePressed();
    void rgbShiftEnablePressed();

    
    ofMesh mesh;
    ofxAssimpModelLoader loader;
    ofEasyCam cam;
    ofEasyCam outCam;
    
    // RENDER PASSES ---------------------------------
    ofxPostProcessing post;
    
    DofAltPass::Ptr     dofAltPass;
    RGBShiftPass::Ptr   rgbShiftPass;
    ZoomBlurPass::Ptr   zoomBlurPass;
    //HsbShiftPass::Ptr   hsbShiftPass;
    //LUTPass::Ptr MyLUTPass;
    
    // GUI
    ofParameter<bool>   dofAltPassEnable;
    ofParameter<float>  dofAltFocalDepth;
    ofParameter<float>  dofAltfocalLength;
    ofParameter<float>  dofAltStop;
    ofParameter<bool>   dofAltShowFocus;
    
    ofParameter<bool>   rgbShiftEnable;
    ofParameter<float>  rgbShiftAmount;
    ofParameter<float>  rgbShiftAngle;
    
    //float exposure = 0.48, float decay = 0.9, float density = 0.25, float weight = 0.25, float clamp = 1);
    ofParameter<bool>   zoomBlurEnable;
    ofParameter<float>  zoomBlurExposure = 0.48;
    ofParameter<float>  zoomBlurDecay = 0.9;
    ofParameter<float>  zoomBlurDensity = 0.25;
    ofParameter<float>  zoomBlurWeight = 0.25;
    ofParameter<float>  zoomBlurClamp = 1;
    
    ofParameter<ofColor> faceColor;
    ofParameter<ofColor> wireColor;

    ofxPanel renderPanel;
    
    // Camera
    ofxFloatSlider  camPosX;
    ofxFloatSlider  camPosY;
    ofxFloatSlider  camPosZ;
    
    ofxFloatSlider  camRotX;
    ofxFloatSlider  camRotY;
    ofxFloatSlider  camRotZ;
    
    ofxPanel cameraPanel;
    
};
