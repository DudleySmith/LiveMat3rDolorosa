//
//  matrDolorosaCam.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 02/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

class matrDolorosaCam : public ofEasyCam{

public:
    void setup();
    void update();
    
    void xChanged(float & xChange);
    void yChanged(float & yChange);
    void zChanged(float & zChange);
    
    void targetXChanged(float & targetXChange);
    void targetYChanged(float & targetYChange);
    void targetZChanged(float & targetZChange);
    
    void polarPhiChanged(float & polarPhiChange);
    void polarThetaChanged(float & polarThetaChange);
    void polarRadiusChanged(float & polarRadiusChange);
    
    void fovChanged(float & fovChange);
    
    void sendAKeyPressed(bool & sendAKeyPress);
    void recordCam();
    
    ofVec3f polarPos();
    
    ofxPanel panel;
    ofxOscParameterSync sync;
    ofParameterGroup cam;
    
    ofParameter<bool>   sendAKey;
    
    ofParameter<float>  camX;
    ofParameter<float>  camY;
    ofParameter<float>  camZ;
    
    ofParameter<float>  polarPhi;
    ofParameter<float>  polarTheta;
    ofParameter<float>  polarRadius;
    
    ofParameter<float>  targetX;
    ofParameter<float>  targetY;
    ofParameter<float>  targetZ;
    
    ofParameter<float>  fov;
    
    bool camRecording;

};
