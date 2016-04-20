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
    
    field.add(sphereColor.set("faceColor",ofColor(255),ofColor(0,0),ofColor(255)));
    field.add(linkColor.set("wireColor",ofColor(255),ofColor(0,0),ofColor(255)));

    panel.setup(field);
    panel.loadFromFile("field.xml");
    
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8070,"localhost", 8071);
    
    generateNodes(nodeAmountMax);
    
}

// -----------------------------------------
void matrDolorosaNodeField::update() {
    
    sync.update();
    
    evalDist();
    
    for(int i = 0; i < nbNodes; i++) {
        
        matrDolorosaNode &temp = nodeArray[i];
        
        temp.setEntropy(entropyBig * entropyFine);
        temp.update();
        
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
    
    for(int i = 0; i < nbNodes; i++) {
        
        matrDolorosaNode &temp = nodeArray[i];
        
        ofSetColor(sphereColor);
        ofDrawSphere(temp.getPosition().x,temp.getPosition().y, temp.getPosition().z, circleSize);
        
        for(int j = 0; j < nbNodes; j++) {
            
            if(distances[i][j] <= distance && i < j) {
                
                int transp = (int)(255-(255*distances[i][j]/ distance));
                
                transp = ofMap(distances[i][j], 0, distance, 255, 0);
                
                ofSetColor(linkColor, transp);
                ofDrawLine(temp.getPosition(), nodeArray[j].getPosition());
                
            }
        }
        
    }
    
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
