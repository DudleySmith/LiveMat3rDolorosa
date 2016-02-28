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
    void addMesh(string meshFile);
    
    void update();
    
    void draw();
    void drawFaces();
    void drawWireframe();
        
    ofxPanel panel;
    
private:
    
    ofxAssimpModelLoader loader;
    vector<ofMesh> allMeshes;
    
    ofxOscParameterSync sync;
    ofParameterGroup meshesPG;
    
    ofParameter<bool>   bDrawFaces;
    ofParameter<bool>   bDrawWireframe;
    
    ofParameter<bool>   bDrawMeshOne;
    ofParameter<bool>   bDrawMeshTwo;
    ofParameter<bool>   bDrawMeshThree;
    ofParameter<bool>   bDrawMeshFour;
    ofParameter<bool>   bDrawMeshFive;
    ofParameter<bool>   bDrawMeshSix;
    
    
    ofParameter<ofColor>   faceColor;
    ofParameter<ofColor>   wireColor;
    ofParameter<float>  lineWidth;

    
};