//
//  matrDolorosaNode.h
//  LiveMat3rDolorosa_NodeFieldExample
//
//  Created by Dudley Smith on 12/03/2016.
//
//


#pragma once

#include "ofMain.h"

class matrDolorosaNode : public ofNode {
    
    
    ofVec3f speed;
    float   circleSize;
    float   entropy;
    
    float   textEntropy;
    ofPoint textPoint;
    
    float   meshEntropy;
    ofPoint meshPoint;
    
public:
    matrDolorosaNode(){
        
    };
    
    
    ofVec3f getVecSpeed(){return speed;};
    
    ofPoint getTextPoint(){return textPoint;};
    void setTextPoint(ofPoint _textPoint){textPoint = _textPoint;};
    
    ofPoint getMeshPoint(){return meshPoint;};
    void setMeshPoint(ofPoint _meshPoint){meshPoint = _meshPoint;};
    
    matrDolorosaNode(float size) {
        circleSize = size;
    }
    
    // ----------------------------------------------------------------------------------------------
    void update(float _natureForceRatio, float _textForceRatio, float _meshForceRatio) {
        // Classical update
        update();
        setPosition(_meshForceRatio*meshPoint + _textForceRatio*textPoint + _natureForceRatio*getPosition());
    }
    
    // ----------------------------------------------------------------------------------------------
    void update(float _natureForceRatio, float _textForceRatio) {
        // Classical update
        //ofLog() << "A : Position : " << getPosition();
        update();
        
        //ofLog() << "B : Position : " << getPosition();
        setPosition(_textForceRatio*textPoint + _natureForceRatio*getPosition());
        
        //ofLog() << "C : Position : " << getPosition();
        
    }
    
    // ----------------------------------------------------------------------------------------------
    void update() {
        
        ofVec3f realSpeed = speed.normalize() * entropy;
        ofVec3f textSpeed = (textPoint - getPosition()).normalize() * textEntropy;
        //ofVec3f meshSpeed = (meshPoint - getPosition()).normalize() * meshEntropy;
        
        ofPoint newPosition = getPosition();
        newPosition +=  realSpeed;
        newPosition +=  textSpeed;
        //newPosition +=  meshSpeed;
        
        if(newPosition.x == NAN){
            ofLog() << "Fuck, we have a NAN : " << ofToString(newPosition);
        }
        
        setPosition(newPosition);
        
    }
    
    // ----------------------------------------------------------------------------------------------
    void checkCubicCollisions(ofVec3f _limits) {
        
        float r = circleSize/2;
        
        ofVec3f position = getPosition();
        
        if(getPosition().x < (-1 * _limits.x)){
            speed.x = -(speed.x);
            position.x = -1 * _limits.x;
        }
        if(getPosition().x > _limits.x) {
            speed.x = -(speed.x);
            position.x = _limits.x;
        }
        
        if(getPosition().y < (-1 * _limits.y)){
            speed.y = -(speed.y);
            position.y = -1 * _limits.y;
        }
        if(getPosition().y > _limits.y) {
            speed.y = -(speed.y);
            position.y = _limits.y;
        }
        
        if(getPosition().z < (-1 * _limits.z)){
            speed.z = -(speed.z);
            position.z = -1 * _limits.z;
        }
        if(getPosition().z > _limits.z) {
            speed.z = -(speed.z);
            position.z = _limits.z;
        }
        
        setPosition(position);
        
    }
    
    // ----------------------------------------------------------------------------------------------
    void checkSphericCollisions(float _inRadius, float _exRadius) {
        
        float r = circleSize/2;
        
        ofVec3f position = getPosition();
        
        if(position.length() > _exRadius){
            // Normal vector to the sphere
            ofVec3f normal = (-1 * position).normalize();
            // Vnew = -2*(V dot N)*N + V
            ofVec3f speed2 = (-2 * speed.dot(normal) * normal) + speed;
            speed = speed2;
            position.scale(0.99 * _exRadius);
            
        } else if(position.length() < _inRadius){
            // Normal vector to the sphere
            ofVec3f normal = (-1 * position).normalize();
            // Vnew = -2*(V dot N)*N + V
            ofVec3f speed2 = (-2 * speed.dot(normal) * normal) + speed;
            speed = speed2;
            position.scale(1.01 * _inRadius);
            
        }
        
        setPosition(position);
        
    }
    
    // ----------------------------------------------------------------------------------------------
    float getSize() {
        return circleSize;
    }
    
    // ----------------------------------------------------------------------------------------------
    float getSpeed() {
        return speed.length();
    }
    
    // ----------------------------------------------------------------------------------------------
    void setSpeed(ofPoint _speed){
        speed = _speed;
    }
    // ----------------------------------------------------------------------------------------------
    void setEntropies(float _entropy, float _textEntropy, float _meshEntropy){
        entropy = _entropy;
        textEntropy = _textEntropy;
        meshEntropy = _meshEntropy;
    }
    
    
};