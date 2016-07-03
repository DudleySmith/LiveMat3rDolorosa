//
//  matrDolorosa_FontPathBlend.cpp
//  LiveMat3rDolorosa_FontExample
//
//  Created by Dudley Smith on 22/06/2016.
//
//

#include "matrDolorosa_FontPathBlend.h"

//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::setup(){
    
    fonts.setName("fonts");
    
    A_Size.addListener(this, &matrDolorosa_FontPathBlend::ASizeChanged);
    B_Size.addListener(this,&matrDolorosa_FontPathBlend::BSizeChanged);
    
    fonts.add(drawAText.set("drawAText", true));
    fonts.add(drawBText.set("drawBText", false));
    fonts.add(drawBlended.set("drawBlended", false));
    
    fonts.add(fill.set("fill", false));
    
    fonts.add(A_Name.set("A_Name", "verdana.ttf"));
    fonts.add(A_Size.set("A_Size", 60, 0.0, 200));
    
    fonts.add(B_Name.set("B_Name", "frabk.ttf"));
    fonts.add(B_Size.set("B_Size", 60, 0.0, 200));
    
    fonts.add(word.set("word", "wandering"));
    fonts.add(blend.set("blend", 0.5, 0.0, 1.0));
    fonts.add(space.set("space", 1.0, 0.0, 1.0));
    fonts.add(scale.set("scale", 1.0, 0.0, 1.0));
    
    fonts.add(scriptRatio.set("ratio", 0.5, 0.0, 1.0));
    fonts.add(scriptWidth.set("width", 1.0, 0.0, 1.0));
    
    fonts.add(nbPoints.set("nbPoints", 15, 0, 1000));
    
    fonts.add(lineWidth.set("lineWidth", 10, 0, 10));
    
    
    
    panel.setup(fonts);
    panel.loadFromFile("fonts.xml");
    
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8090,"localhost", 8091);
    
    // Setting the fonts and the points related
    // Setting the fonts and the points related
    loadFontA();
    loadFontB();
    //setupPoints(word.get());
    
}

//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::ASizeChanged(int & sizeChange){
    loadFontA();
}
//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::BSizeChanged(int & sizeChange){
    loadFontB();
}

//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::loadFontA(){
    m_oFontA.load(A_Name, A_Size, true, true, true);
    m_oFontA.setLineHeight(34.0f);
    m_oFontA.setLetterSpacing(1.035);
}

//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::loadFontB(){
    m_oFontB.load(B_Name, B_Size, true, true, true);
    m_oFontB.setLineHeight(34.0f);
    m_oFontB.setLetterSpacing(1.035);
}


//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::update(){
    
    sync.update();
    //receiveOscText();
    
    string _word = word;
    
    if(_word.size() > 0){
        
        charPointsA = ofPolyline();
        charPointsB = ofPolyline();
        
        stringWidht = blend * m_oFontA.stringWidth(_word) + (1.0 - blend.get())*m_oFontB.stringWidth(_word);
        stringHeight = blend * m_oFontA.stringHeight(_word) + (1.0 - blend.get())*m_oFontB.stringHeight(_word);
        
        stringSize = blend * m_oFontA.getSize() + (1 - blend)*m_oFontB.getSize();
        
        for(int idxChar=0; idxChar < _word.size(); idxChar++){
            
            int idxOutline = 0;
            
            ofTTFCharacter oneChar_A = m_oFontA.getCharacterAsPoints(_word[idxChar]);
            for (idxOutline = 0; idxOutline < oneChar_A.getOutline().size(); idxOutline++) {
                
                //ofLog() << "A : idxOuline : " << ofToString(idxOutline) << " + " << oneChar_A.getOutline()[idxOutline].getVertices().size();
                for (int idxPoint = 0;  idxPoint < oneChar_A.getOutline()[idxOutline].getVertices().size(); idxPoint++) {
                    
                    ofPoint onePoint;
                    
                    onePoint = oneChar_A.getOutline()[idxOutline].getVertices()[idxPoint];
                    onePoint += ofPoint(idxChar * space * stringSize, 0);
                    
                    charPointsA.addVertex(onePoint);
                }
            }
            
            ofTTFCharacter oneChar_B = m_oFontB.getCharacterAsPoints(_word[idxChar]);
            for (idxOutline = 0; idxOutline < oneChar_B.getOutline().size(); idxOutline++) {
                
                for (int idxPoint = 0;  idxPoint < oneChar_B.getOutline()[idxOutline].getVertices().size(); idxPoint++) {
                    
                    ofPoint onePoint;
                    
                    onePoint = oneChar_B.getOutline()[idxOutline].getVertices()[idxPoint];
                    onePoint += ofPoint(idxChar * space * stringSize, 0);
                    
                    charPointsB.addVertex(onePoint);
                }
                
            }
        }
        
        charPointsB = charPointsB.getResampledByCount(nbPoints);
        charPointsA = charPointsA.getResampledByCount(nbPoints);
    }
    
}

//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::receiveOscText(){
    
    // check for waiting messages
    while(textReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        textReceiver.getNextMessage(m);
        
        // check for mouse moved message
        if(ofIsStringInString(m.getAddress(), "/fonts/text")){
            //if(m.getAddress() == "/text"){
            oscText = m.getAddress();
            ofStringReplace(oscText, "/fonts/text", "");
            //ofLog() << "Osc Text" << oscText;
            word = oscText;
            
        }else{
            
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_RGBA_COLOR){
                    msg_string += ofToString(m.getArgAsRgbaColor(i));
                }
                else{
                    msg_string += "unknown";
                }
            }
            
            ofLog() << "Other osc Message : " << msg_string;
            
        }
    }
    
}



//--------------------------------------------------------------
void matrDolorosa_FontPathBlend::draw(){
    
    // --
    ofPushMatrix();
    ofPushStyle();
    
    
    //center *= ofPoint(ofGetWidth(), ofGetHeight());
    //center += 0.5 * ofPoint(ofGetWidth(), ofGetHeight());
    
    ofTranslate(0.5 * (ofGetWidth() - space * stringWidht), 0.5 * (ofGetHeight() + 0.5*stringHeight));
    
    ofScale(scale, scale);
    
    if(fill){
        ofFill();
    }else{
        ofNoFill();
    }
    ofSetLineWidth(lineWidth);
    
    if(drawAText){
        m_oFontA.drawString(word, 0, 0);
    }
    if(drawBText){
        m_oFontB.drawString(word, 0, 0);
    }
    if(drawBlended){
        if(charPointsA.getVertices().size() > 0 && charPointsB.getVertices().size() > 0){
            
            int startPoint, endPoint;
            
            endPoint = startPoint = scriptRatio * (float)(nbPoints);
            startPoint -= scriptWidth * 0.5f * (float)(nbPoints);
            endPoint += scriptWidth * 0.5f * (float)(nbPoints);
            
            //endPoint = startPoint + (ofMap(scriptRatio, 0, 0.5, 0, scriptWidth, true) - ofMap(scriptRatio, 0.5, 1, 0, scriptWidth, true)) * (float)(nbPoints);
            
            startPoint = max(0, startPoint);
            endPoint = min(nbPoints.get(), endPoint);
            
            //ofLog() << "start Point = " << ofToString(startPoint) << " : " << "end point = " << ofToString(endPoint);
            
            ofBeginShape();
            
            for(int idxPoint = startPoint; idxPoint < endPoint; idxPoint++){
                
                ofPoint onePointA = charPointsA.getPointAtPercent((float)idxPoint / (float) nbPoints);
                ofPoint onePointB = charPointsB.getPointAtPercent((float)idxPoint / (float) nbPoints);
                
                ofPoint onePoint = blend * onePointA + (1.0f - blend)*onePointB;
                //ofLog() << "Point = " << ofToString(onePoint);
                
                ofCurveVertex(onePoint);
                
            }
            
            ofEndShape();
            
        }
        
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}
