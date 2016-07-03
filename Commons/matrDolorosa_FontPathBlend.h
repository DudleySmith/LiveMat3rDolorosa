//
//  matrDolorosa_FontPathBlend.h
//  LiveMat3rDolorosa_FontExample
//
//  Created by Dudley Smith on 22/06/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxOscParameterSync.h"

class matrDolorosa_FontPathBlend {

public:
    void setup();
    void loadFontA();
    void loadFontB();
    
    void update();
    void draw();
    
// FONTS -------------------------------
private:
    ofTrueTypeFont m_oFontA, m_oFontB;
    
// GUI -------------------------------------
public:
    ofxPanel panel;
    
private:
    ofxOscParameterSync sync;
    ofParameterGroup fonts;
    
    void ASizeChanged(int & sizeChange);
    void BSizeChanged(int & sizeChange);
    
    ofParameter<bool>      drawAText;
    ofParameter<bool>      drawBText;
    ofParameter<bool>      drawBlended;
    
    ofParameter<bool>      fill;
    
    ofParameter<string>    A_Name;
    ofParameter<int>       A_Size;
    
    ofParameter<string>    B_Name;
    ofParameter<int>       B_Size;
    
    ofParameter<string>    word;
    
    ofParameter<float>     blend;
    ofParameter<float>     space;
    ofParameter<float>     scale;
    
    ofParameter<float>     scriptRatio;
    ofParameter<float>     scriptWidth;
    
    ofParameter<int>       nbPoints;
  
    ofParameter<int>       lineWidth;
    
    ofPolyline             charPointsA;
    ofPolyline             charPointsB;
    
    ofxOscReceiver         textReceiver;
    string oscText;
    void receiveOscText();

    float stringWidht;
    float stringHeight;
    float stringSize;
    
    
};
