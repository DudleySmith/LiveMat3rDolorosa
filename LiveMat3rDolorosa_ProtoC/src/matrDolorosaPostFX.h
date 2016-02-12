//
//  matrDolorosaPostFX.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 12/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxPostProcessing.h"

class matrDolorosaPostFX{
    
public:
    void setup();
    void update();
    
    ofxPanel panel;
    ofxOscParameterSync sync;
    ofParameterGroup render;
    
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
    
};
