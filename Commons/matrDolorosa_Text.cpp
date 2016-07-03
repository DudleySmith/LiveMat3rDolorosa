//
//  matrDolorosa_Text.cpp
//  LiveMat3rDolorosa_TextExample
//
//  Created by Dudley Smith on 21/06/2016.
//
//

#include "matrDolorosa_Text.h"

// --------------------------------------------
void matrDolorosa_Text::setup(){
    font.load("verdana.ttf", 60, true, true, true);
    font.setLineHeight(34.0f);
    font.setLetterSpacing(1.035);
    
    anim.reset(0);
    anim.setCurve(EASE_IN);
    anim.setRepeatType(LOOP_BACK_AND_FORTH_N_TIMES);
    anim.setRepeatTimes(1);
    anim.setDuration(1);

}
// --------------------------------------------
void matrDolorosa_Text::update(){
    //app timebase, to send to all animatable objects
    float dt = 1.0f / ofGetFrameRate();
    anim.update(dt);
}

// --------------------------------------------
void matrDolorosa_Text::draw(){
    
    ofPushStyle();
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    
    if(word!=""){
        ofTranslate(0.5 * ofGetWidth(), 0.5 * ofGetHeight());
        
        if(animScale==true){
            float scaleValue;
            if(animScaleInOut==1){
                scaleValue = ofMap(anim.getCurrentValue(), 0, 1, 1, 0);
            }else{
                scaleValue = ofMap(anim.getCurrentValue(), 0, 1, 0, 1);
            }
            ofScale(scaleValue, scaleValue);
        }
        
        if(animFade==true){
            if(animFadeInOut==1){
                ofSetColor(ofColor::white, 255.0f * ofMap(anim.getCurrentValue(), 0, 1, 0, 1));
            }else{
                ofSetColor(ofColor::white, 255.0f * ofMap(anim.getCurrentValue(), 0, 1, 1, 0));
            }
        }
        
        
        //font.drawString(word, -0.5 * font.stringWidth(word), 0);
        // we can also access the individual points
        ofFill();
        ofPushMatrix();
        
        string newWord;
        
        int nbChars = 3;
        int startIdx = anim.getCurrentValue() * word.size();
        int endIdx = startIdx + nbChars;
        float letterStep = font.getSize();
        
        if(endIdx>word.size())
            endIdx = word.size();
        
        if(startIdx>word.size())
            startIdx = word.size();
        
        
        for(int idxChar = 0; idxChar < word.size(); idxChar++){
            if(idxChar<startIdx || idxChar > endIdx){
                newWord += " ";
            }else if (idxChar < endIdx){
                newWord += word[idxChar];
            }
        }
        
        ofLog() << "After replacement : " << newWord;
        ofTranslate(-0.5f * (float)newWord.size() * (float)letterStep, 0);
        
        for(int idxChar = 0; idxChar < newWord.size(); idxChar++){
            
            char extractedChar = newWord[idxChar];
            
            ofTTFCharacter oneChar = font.getCharacterAsPoints(extractedChar);
            
            ofBeginShape();
            ofPushStyle();
            
            ofSetColor(ofColor::white, 255.0f * ofMap(idxChar, startIdx, endIdx, 0, 1, true));
            
            for(int k = 0; k <(int)oneChar.getOutline().size(); k++){
                if( k!= 0)ofNextContour(true) ;
                for(int i = 0; i < (int)oneChar.getOutline()[k].size(); i++){
                    ofVertex(oneChar.getOutline()[k].getVertices()[i].x, oneChar.getOutline()[k].getVertices()[i].y);
                }
            }
            
            ofPopStyle();
            ofEndShape( true );
            
            //float letterStep = font.stringWidth(ofToString(newWord[idxChar])) + 2*font.getLetterSpacing();
            
            ofLog() << "step = " << ofToString(letterStep);
            ofTranslate(letterStep, 0, 0);
            
        }
        
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
}

// --------------------------------------------
void matrDolorosa_Text::setWord(string _word){
    
    ofLog() << "New text : " << _word;
    
    if(_word != word){
        anim.reset(0);
        anim.animateTo(1);
    }
    
    word = _word;
}
// --------------------------------------------
void matrDolorosa_Text::setAnimScaleIn(bool _animScale){
    animScale = _animScale;
    animScaleInOut = 1;
}
// --------------------------------------------
void matrDolorosa_Text::setAnimScaleOut(bool _animScale){
    animScale = _animScale;
    animScaleInOut = -1;
}
// --------------------------------------------
void matrDolorosa_Text::setAnimFadeIn(bool _animFade){
    animFade = _animFade;
    animFadeInOut = 1;
}
// --------------------------------------------
void matrDolorosa_Text::setAnimFadeOut(bool _animFade){
    animFade = _animFade;
    animFadeInOut = -1;
}