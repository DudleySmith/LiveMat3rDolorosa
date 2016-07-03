//
//  matrDolorosa_Text.h
//  LiveMat3rDolorosa_TextExample
//
//  Created by Dudley Smith on 21/06/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class matrDolorosa_Text{
    
public:
    void setup();
    void update();
    void draw();

private:
    ofTrueTypeFont font;
    string         word;
    
    bool animScale;
    int animScaleInOut;
    
    bool animFade;
    int animFadeInOut;
    
    float startTime;
    
    ofxAnimatableFloat anim;

public:
    void setWord(string _word);
    
    void setAnimScaleIn(bool _animScaleIn);
    void setAnimScaleOut(bool _animScaleOut);
    
    void setAnimFadeIn(bool _animFade);
    void setAnimFadeOut(bool _animFade);
        
};
