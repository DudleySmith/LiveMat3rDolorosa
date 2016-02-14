//
//  matrDolorosaMeshes.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 14/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxAssimpModelLoader.h"

class matrDolorosaMeshes{

public:
    void setup();
    void draw();

    ofxPanel panel;
    
private:
    
    ofxAssimpModelLoader loader;
    ofMesh mesh;

    ofxOscParameterSync sync;
    ofParameterGroup meshes;
    
    ofParameter<bool>   drawFaces;
    ofParameter<bool>   drawWireframe;
    ofParameter<ofColor>   faceColor;
    ofParameter<ofColor>   wireColor;
    ofParameter<float>  lineWidth;

    
};