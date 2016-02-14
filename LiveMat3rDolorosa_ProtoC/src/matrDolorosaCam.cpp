//
//  matrDolorosaCam.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 02/02/2016.
//
//

#include "matrDolorosaCam.h"

// -----------------------------------------
void matrDolorosaCam::setup(){
    
    cam.setName("cam");
    
    cam.add(camX.set("camX",0,-2000,2000));
    cam.add(camY.set("camY",0,-2000,2000));
    cam.add(camZ.set("camZ",1000,-2000,2000));
    
    cam.add(targetX.set("targetX",0,-2000,2000));
    cam.add(targetY.set("targetY",0,-2000,2000));
    cam.add(targetZ.set("targetZ",0,-2000,2000));
    
    
    cam.add(polarTheta.set("polarTheta",0,0,360));
    cam.add(polarPhi.set("polarPhi",0,0,360));
    cam.add(polarRadius.set("polarRadius",1000,0,2000));
    
    panel.setup(cam);
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8040,"localhost", 8041);
    
    camX.addListener(this, &matrDolorosaCam::xChanged);
    camY.addListener(this, &matrDolorosaCam::yChanged);
    camZ.addListener(this, &matrDolorosaCam::zChanged);
    
    polarPhi.addListener(this, &matrDolorosaCam::polarPhiChanged);
    polarTheta.addListener(this, &matrDolorosaCam::polarThetaChanged);
    polarRadius.addListener(this, &matrDolorosaCam::polarRadiusChanged);
    
    targetX.addListener(this, &matrDolorosaCam::targetXChanged);
    targetY.addListener(this, &matrDolorosaCam::targetYChanged);
    targetZ.addListener(this, &matrDolorosaCam::targetZChanged);
    
}

// -----------------------------------------
void matrDolorosaCam::update(){
    sync.update();
}

// -------------------------------------------
ofVec3f matrDolorosaCam::polarPos(){
    
    ofVec3f polarPos;
    ofVec3f orientationVec = ofVec3f(0,0,1);
    orientationVec.rotate(polarTheta, polarPhi, 0);
    orientationVec *= polarRadius;
    
    polarPos.x = polarRadius   * cos(ofDegToRad(polarTheta)) * sin(ofDegToRad(polarPhi));
    polarPos.z = polarRadius   * cos(ofDegToRad(polarTheta)) * cos(ofDegToRad(polarPhi));
    polarPos.y = polarRadius   * sin(ofDegToRad(polarTheta));
    
    return orientationVec;
}

// -------------------------------------------
void matrDolorosaCam::xChanged(float & xChange){
    setGlobalPosition(camX, camY, camZ);
    setTarget(ofVec3f(targetX, targetY, targetZ));

}
void matrDolorosaCam::yChanged(float & yChange){
    setGlobalPosition(camX, camY, camZ);
    setTarget(ofVec3f(targetX, targetY, targetZ));
}
void matrDolorosaCam::zChanged(float & zChange){
    setGlobalPosition(camX, camY, camZ);
    setTarget(ofVec3f(targetX, targetY, targetZ));
}

// -------------------------------------------
void matrDolorosaCam::targetXChanged(float & targetXChange){
    setTarget(ofVec3f(targetX, targetY, targetZ));
}
void matrDolorosaCam::targetYChanged(float & targetYChange){
    setTarget(ofVec3f(targetX, targetY, targetZ));
}
void matrDolorosaCam::targetZChanged(float & targetZChange){
    setTarget(ofVec3f(targetX, targetY, targetZ));
}

// -------------------------------------------
void matrDolorosaCam::polarPhiChanged(float & polarPhiChange){
    setPosition(ofVec3f(polarPos()));
    setTarget(ofVec3f(targetX, targetY, targetZ));

}
void matrDolorosaCam::polarThetaChanged(float & polarThetaChange){
    setPosition(ofVec3f(polarPos()));
    setTarget(ofVec3f(targetX, targetY, targetZ));
}
void matrDolorosaCam::polarRadiusChanged(float & polarRadiusChange){
    setPosition(ofVec3f(polarPos()));
    setTarget(ofVec3f(targetX, targetY, targetZ));
}

