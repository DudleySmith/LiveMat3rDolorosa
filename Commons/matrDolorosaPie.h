//
//  matrDolorosaPies.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 01/03/2016.
//
//

#pragma once

#include "ofMain.h"

class matrDolorosaPie {
    
public:
    void update();
    void draw(float x,float y, float radius, float lowAngle, float highAngle, bool closed, bool radians);
    
};