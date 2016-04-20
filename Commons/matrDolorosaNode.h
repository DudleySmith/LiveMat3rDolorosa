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
    float circleSize;
    float entropy;
    
public:
    matrDolorosaNode(){
        
    };
    
    
    ofVec3f getVecSpeed(){return speed;};
    
    matrDolorosaNode(float size) {
        circleSize = size;
    }
    
    // ----------------------------------------------------------------------------------------------
    void update() {
        ofVec3f realSpeed = speed * entropy;
        setPosition(getPosition().x + realSpeed.x, getPosition().y + realSpeed.y, getPosition().z + realSpeed.z);
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
    void setEntropy(float _entropy){
        entropy = _entropy;
    }
    
    
};