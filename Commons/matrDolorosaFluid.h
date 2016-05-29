#pragma once

#include "MSAFluid.h"
//#include "MSATimer.h"
#include "ParticleSystem.h"

#include "ofMain.h"

// comment this line out if you don't wanna use the GUI
// you will need ofxSimpleGuiToo, ofxMSAInteractiveObject & ofxXmlSettings
// if you don't use the GUI, you won't be able to see the fluid parameters
#include "ofxSimpleGuiToo.h"

#include "ofxGui.h"
#include "ofxOscParameterSync.h"

class matrDolorosaFluid {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    
    void fadeToColor(float r, float g, float b, float speed);
    void addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce);
    
    
    
    float                   colorMult;
    float                   velocityMult;
    int                     fluidCellsX;
    bool                    resizeFluid;
    bool                    drawFluid;
    bool                    drawParticles;
    
    msa::fluid::Solver      fluidSolver;
    msa::fluid::DrawerGl	fluidDrawer;
    
    ParticleSystem          particleSystem;
    
    ofVec2f                 pMouse;

public:
    ofxPanel panel;
    
private:
    ofxOscParameterSync sync;
    ofParameterGroup pgMsaFluid;
    
    ofParameter<bool> pDrawFluid;
    ofParameter<bool> pDrawParticles;
    
    ofParameter<float> pFluidCellsX;
    ofParameter<bool>   pResizeFluid;
    ofParameter<float> pColorMult;
    ofParameter<float> pVelocityMult;
    ofParameter<float> pViscocity;
    ofParameter<float> pColorDiffusion;
    ofParameter<float> pFadeSpeed;
    ofParameter<float> pSolverIterations;
    ofParameter<float> pDeltaT;
    ofParameter<int> pDrawMode;
    ofParameter<bool> pDoRGB;
    ofParameter<bool> pDoVorticityConfinement;
    ofParameter<bool> pWrap_x;
    ofParameter<bool> pWrap_y;
    
    void drawModeChanged(int & pDrawMode);
    void resizeFluidPressed(bool & pResizeFluid);
    
};



