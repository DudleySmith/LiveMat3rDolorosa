//
//  matrDolorosaNodeFields.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 12/03/2016.
//
//

#include "matrDolorosaNodeField.h"

// -----------------------------------------
void matrDolorosaNodeField::setup() {
    
    field.setName("field");
    
    textReset.addListener(this, &matrDolorosaNodeField::startPointRecalled);
    textWord.addListener(this, &matrDolorosaNodeField::wordChanged);
    
    field.add(drawField.set("drawField",false));
    
    field.add(nbNodes.set("nbNodes", 5, 0, nodeAmountMax));
    field.add(xyLinks.set("xyLinks",false));
    field.add(circleSize.set("circleSize", 2, 0, 10));
    field.add(distance.set("distance", 150, 0, 1000));
    field.add(entropyBig.set("entropyBig", 10, 0, 200));
    field.add(entropyFine.set("entropyFine", 0.1, 0, 5));
    
    field.add(xLimit.set("xLimit",200, 0, 1000));
    field.add(yLimit.set("yLimit",200, 0, 1000));
    field.add(zLimit.set("zLimit",200, 0, 1000));
    
    field.add(sphereLimit.set("sphereLimit",true));
    field.add(exRadius.set("exRadius",200, 0, 1000));
    field.add(inRadius.set("inRadius",0, 0, 1000));
    
    field.add(sphereColor.set("sphereColor",ofColor(255,255),ofColor(0,0),ofColor(255,255)));
    field.add(linkColor.set("linkColor",ofColor(255,255),ofColor(0,0),ofColor(255,255)));
    
    field.add(textReset.set("textReset", false));
    field.add(choiceRatio.set("choiceRatio", 0.0, -1.0, 1.0));
    field.add(choiceEntropy.set("choiceEntropy", 0.0, -1.0, 1.0));
    
    field.add(natureRatio.set("naturePosRatio", 1.0, 0.0, 1.0));
    field.add(natureEntropy.set("natureEntropy", 0.0, 0.0, 1.0));
    
    field.add(textForceRatio.set("textPosRatio", 0.0, 0.0, 1.0));
    field.add(textEntropy.set("textEntropy", 0.0, 0.0, 1.0));
    
    field.add(meshForceRatio.set("meshPosRatio", 0.0, 0.0, 1.0));
    field.add(meshEntropy.set("meshEntropy", 0.0, 0.0, 1.0));
    
    //    field.add(textEntropyBig.set("textEntropyBig", 10, 0, 200));
    //    field.add(textEntropyFine.set("textEntropyFine", 0.1, 0, 5));
    
    field.add(startText.set("startText", true));
    field.add(textWord.set("word", "xxxxxxxx"));
    field.add(textSize.set("textSize", 200, 1, 200));
    field.add(textFont.set("textFont", "verdana.ttf"));
    
    panel.setup(field);
    panel.loadFromFile("field.xml");
    
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8070,"localhost", 8071);
    
    // Based on a text
    ofLog() << "Font : " << textFont.get() << " : " << "Size :" << ofToString(textSize.get());
    oFont.load(textFont.get(), textSize.get(), true, true, true);
    oFont.setLineHeight(34.0f);
    oFont.setLetterSpacing(1.035);
    
    setupFont();
    //setupMesh("ANGE_LESS_Exported.obj");
    
    generateNodes(nodeAmountMax);
    
    
}

// -----------------------------------------
void matrDolorosaNodeField::setupFont(){
    
    textPoints = ofPolyline();
    
    string word = textWord.get();
    
    if(word.size() > 0 && oFont.isLoaded()){
        
        for(int idxChar=0; idxChar < word.size(); idxChar++){
            
            ofTTFCharacter oneChar = oFont.getCharacterAsPoints(word[idxChar]);
            
            float charRatio;
            if(word.size() > 1){
                charRatio = ofMap(idxChar, 0, word.size() - 1, -0.4, 0.4, true);
            }else{
                charRatio = 0;
            }
            /*
            charRatio = (float)(idxChar) / (float)(word.size() - 1);
            charRatio -= 0.5;
            */
            //ofLog() << "Word=" << word << " : " << "Char=" << word[idxChar] << " : " << "Ratio=" << ofToString(charRatio);
            
            if(word[idxChar] != ' '){
                for (int idxOutline = 0; idxOutline < oneChar.getOutline().size(); idxOutline++) {
                    
                    for (int idxPoint = 0;  idxPoint < oneChar.getOutline()[idxOutline].getVertices().size(); idxPoint++) {
                        
                        ofPoint onePoint;
                        
                        onePoint = oneChar.getOutline()[idxOutline].getVertices()[idxPoint];
                        onePoint += ofPoint(charRatio * 2 * exRadius, 0);
                        
                        textPoints.addVertex(onePoint);
                        //ofLog() << "onePoint=" << ofToString(onePoint);
                    }
                }
            }
            
        }
        
        textPoints = textPoints.getResampledByCount(nodeAmountMax);
        
    }
}

// -----------------------------------------
void matrDolorosaNodeField::setupMesh(string _meshFile){
    
    ofFile meshExists = ofFile(_meshFile);
    
    if (meshExists.exists()) {
        meshLoader.loadModel(meshExists.path());
        meshPoints.addVertices(meshLoader.getMesh(0).getVertices());
        /*
         for(int idxMeshVertex=0; idxMeshVertex<meshLoader.getMesh(0).getVertices().size(); idxMeshVertex++){
         //meshPoints.addVertex((0.2 * meshLoader.getMesh(0).getVertices()[idxMeshVertex]));
         }
         */
        ofLogNotice() << "Mesh loaded :  Nb Meshes:" << ofToString(meshLoader.getMeshCount());
        
        
    }else{
        ofLogError() << "CRAP : The mesh is not loaded ! " + meshExists.path();
        
    }
    
}

// -----------------------------------------
void matrDolorosaNodeField::startPointRecalled(bool &_recall){
    if(textReset){
        setupFont();
        textReset = false;
    }
}

// -----------------------------------------
void matrDolorosaNodeField::wordChanged(string &_wordChange){
    setupFont();
    
    //choiceEntropy = -0.25;
    //choiceRatio   = -1;
    
}

//// -----------------------------------------
//void matrDolorosaNodeField::startPointForced(bool &_force){
//    if(startPointForce){
//        forceStartPoints();
//        startPointForce = false;
//    }
//}

// -----------------------------------------
void matrDolorosaNodeField::update() {
    
    sync.update();
    
    // Stop all operations --------
    if(!drawField)  return;
    
    evalDist();
    
    for(int i = 0; i < nbNodes; i++) {
        
        //ofLog() << "Node index : " << ofToString(i);
        
        matrDolorosaNode &temp = nodeArray[i];
        
        // Recalculate entropies with a choice
        textEntropy = ofMap(choiceEntropy, -1, 0, 1, 0, true);
        //meshEntropy = ofMap(choiceEntropy, 1, 0, 1, 0, true);
        natureEntropy = ofMap(choiceEntropy, -1, 0, 0, 1, true) * ofMap(choiceEntropy, 1, 0, 0, 1, true);
        
        // Recalculate force ratios with a choice
        textForceRatio = ofMap(choiceRatio, -1, 0, 1, 0, true);
        //meshForceRatio = ofMap(choiceRatio, 1, 0, 1, 0, true);
        natureRatio = ofMap(choiceRatio, -1, 0, 0, 1, true) * ofMap(choiceRatio, 1, 0, 0, 1, true);
        
        //        temp.setEntropies(entropyBig * entropyFine, textEntropyBig * textEntropyFine);
        temp.setEntropies(natureEntropy*entropyBig * entropyFine, textEntropy*entropyBig * entropyFine, meshEntropy*entropyBig * entropyFine);
        temp.setTextPoint(textPoints.getPointAtPercent((float) i/ (float)nbNodes));
        //temp.setMeshPoint(0.4 * meshPoints.getPointAtPercent((float) i/ (float)nbNodes));
        
        // First we move
        temp.update(natureRatio, textForceRatio); //, meshForceRatio);
        //temp.update();
        
        // then we collide
        if(sphereLimit){
            temp.checkSphericCollisions(inRadius, exRadius);
        }else{
            temp.checkCubicCollisions(ofVec3f(xLimit, yLimit, zLimit));
        }
        
    }
    
}

// -----------------------------------------
void matrDolorosaNodeField::draw() {
    
    
    //evalDist();
    // Stop all operations --------
    if(!drawField)        return;
    
    ofPushStyle();
    ofEnableAlphaBlending();
    
    for(int i = 0; i < nbNodes; i++) {
        
        matrDolorosaNode &temp = nodeArray[i];
        
        ofSetColor(sphereColor);
        ofDrawSphere(temp.getPosition().x,temp.getPosition().y, temp.getPosition().z, circleSize);
        
        //ofSetColor(255,0,0);
        //ofDrawCircle(temp.getStartPoint(), 20);
        
        for(int j = 0; j < nbNodes; j++) {
            
            if(distances[i][j] <= distance && i < j) {
                
                int transp = (int)(255-(255*distances[i][j]/ distance));
                
                //transp = ofMap(distances[i][j], 0, distance, 255, 0);
                //ofSetColor(linkColor, transp);
                
                ofSetColor(linkColor);
                ofDrawLine(temp.getPosition(), nodeArray[j].getPosition());
                
            }
        }
        
    }
    
    ofPopStyle();
    
}

// -----------------------------------------
void matrDolorosaNodeField::generateNodes(int _nodeAmount) {
    
    for(int i = 0; i < _nodeAmount; i++) {
        
        matrDolorosaNode newNode(1);
        
        newNode.setPosition(ofRandom(-1 * xLimit, xLimit), ofRandom(-1 * yLimit, yLimit), ofRandom(-1 * zLimit, zLimit));
        newNode.setSpeed(ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
        
        nodeArray.push_back(newNode);
        
    }
    
}

// -----------------------------------------
void matrDolorosaNodeField::evalDist() {
    
    for(int i = 0; i < nbNodes; i++) {
        for(int j = 0; j < nbNodes; j++) {
            if(i < j){
                
                ofPoint a = nodeArray[i].getPosition();
                ofPoint b = nodeArray[j].getPosition();
                
                if(xyLinks){
                    distances[i][j] = ofDist(a.x, a.y, b.x, b.y);
                }else{
                    distances[i][j] = ofDist(a.x, a.y, a.z, b.x, b.y, b.z);
                }
                
            }
        }
    }
    
}

// -----------------------------------------
vector<matrDolorosaNode> matrDolorosaNodeField::getNodes(){
    return nodeArray;
};
// -----------------------------------------
int matrDolorosaNodeField::getNbNodes(){
    return nbNodes;
};
