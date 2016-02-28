//
//  matrDolorosaPostFX.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 12/02/2016.
//
//

#include "matrDolorosaPostFX.h"


//--------------------------------------------------------------
void matrDolorosaPostFX::setup(){
    // RENDER --------------------------------------------
    panel.setup("render");
    
    //DofAltPass(const ofVec2f& aspect, bool arb, float focalDepth = 1.f, float focalLength = 500.f, float fStop = 3.f, bool showFocus = false);
    panel.add(dofAltPassEnable.set("dofAltPassEnable", false));
    panel.add(dofAltFocalDepth.set("dofAltFocalDepth", 1.0, 0.5, 500.0));
    panel.add(dofAltfocalLength.set("dofAltfocalLength", 1.0, 0.5, 500.0));
    panel.add(dofAltStop.set("dofAltStop", 5.0, 0.5, 200.0));
    panel.add(dofAltShowFocus.set("dofAltShowFocus", false));
    
    //RGBShiftPass(const ofVec2f& aspect, bool arb, float amount = 0.005, float angle = 0.0);
    panel.add(rgbShiftEnable.set("rgbShiftEnable", false));
    panel.add(rgbShiftAmount.set("rgbShiftAmount", 0.0, 0.0, 0.05));
    panel.add(rgbShiftAngle.set("rgbShiftAngle", 0, 0, 360));
    
    //float exposure = 0.48, float decay = 0.9, float density = 0.25, float weight = 0.25, float clamp = 1);
    panel.add(zoomBlurEnable.set("zoomBlurEnable", false));
    panel.add(zoomBlurExposure.set("zoomBlurExposure", 0.48, 0.0, 1.0));
    panel.add(zoomBlurDecay.set("zoomBlurDecay", 0.9, 0.0, 1.0));
    panel.add(zoomBlurDensity.set("zoomBlurDensity", 0.25, 0.0, 1.0));
    panel.add(zoomBlurWeight.set("zoomBlurWeight", 0.25, 0.0, 1.0));
    
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8050,"localhost", 8051);
    panel.loadFromFile("render.xml");
    
    // INIT PASSES --------------------------------------
    
    int w = ofGetWidth();
    int h  = ofGetHeight();
    
    ofLog() << ofToString(w) << ":" << ofToString(h);
    
    post.init(ofGetWidth(), ofGetHeight());
    dofAltPass = post.createPass<DofAltPass>();
    zoomBlurPass = post.createPass<ZoomBlurPass>();
    rgbShiftPass = post.createPass<RGBShiftPass>();
    
}


//--------------------------------------------------------------
void matrDolorosaPostFX::update(){
    
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
    
    sync.update();
    
}

