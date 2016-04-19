
#include "matrDolorosaFluid.h"

char sz[] = "[Rd9?-2XaUP0QY[hO%9QTYQ`-W`QZhcccYQY[`b";


float tuioXScaler = 1;
float tuioYScaler = 1;

//--------------------------------------------------------------
void matrDolorosaFluid::setup() {
    for(int i=0; i<strlen(sz); i++) sz[i] += 20;

    
    /*
    gui.addSlider("fluidCellsX", fluidCellsX, 20, 400);
    gui.addButton("resizeFluid", resizeFluid);
    gui.addSlider("colorMult", colorMult, 0, 100);
    gui.addSlider("velocityMult", velocityMult, 0, 100);
    gui.addSlider("fs.viscocity", fluidSolver.viscocity, 0.0, 0.01);
    gui.addSlider("fs.colorDiffusion", fluidSolver.colorDiffusion, 0.0, 0.0003);
    gui.addSlider("fs.fadeSpeed", fluidSolver.fadeSpeed, 0.0, 0.1);
    gui.addSlider("fs.solverIterations", fluidSolver.solverIterations, 1, 50);
    gui.addSlider("fs.deltaT", fluidSolver.deltaT, 0.1, 5);
    gui.addComboBox("fd.drawMode", (int&)fluidDrawer.drawMode, msa::fluid::getDrawModeTitles());
    gui.addToggle("fs.doRGB", fluidSolver.doRGB);
    gui.addToggle("fs.doVorticityConfinement", fluidSolver.doVorticityConfinement);
    gui.addToggle("drawFluid", drawFluid);
    gui.addToggle("drawParticles", drawParticles);
    gui.addToggle("fs.wrapX", fluidSolver.wrap_x);
    gui.addToggle("fs.wrapY", fluidSolver.wrap_y);
    gui.addSlider("tuioXScaler", tuioXScaler, 0, 2);
    gui.addSlider("tuioYScaler", tuioYScaler, 0, 2);
    
    gui.currentPage().setXMLName("ofxMSAFluidSettings.xml");
    gui.loadFromXML();
    gui.setDefaultKeys(true);
    gui.setAutoSave(true);
    gui.show();
    */
    
    
    // setup fluid stuff
    fluidSolver.setup(100, 100);
    fluidDrawer.setup(&fluidSolver);
    
    /*fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
    fluidDrawer.setup(&fluidSolver);
    
    fluidCellsX			= 150;
    
    drawFluid			= true;
    drawParticles		= true;
    */
    pgMsaFluid.setName("fluid");
    
    pgMsaFluid.add(pFluidCellsX.set("pFluidCellsX", 150, 20, 400));
    pgMsaFluid.add(pResizeFluid.set("pResizeFluid", false));
    pgMsaFluid.add(pColorMult.set("pColorMult", 98.5, 0, 100));
    pgMsaFluid.add(pVelocityMult.set("pVelocityMult", 7.5, 0, 100));
    pgMsaFluid.add(pViscocity.set("pViscocity", 0.00015, 0.0, 0.01));
    pgMsaFluid.add(pColorDiffusion.set("pColorDiffusion", 0.0, 0.0, 0.0003));
    pgMsaFluid.add(pFadeSpeed.set("pFadeSpeed", 0.002, 0.0, 0.1));
    pgMsaFluid.add(pSolverIterations.set("pSolverIterations", 15, 1, 50));
    pgMsaFluid.add(pDeltaT.set("pDeltaT", 0.5, 0.1, 5));
    pgMsaFluid.add(pDrawMode.set("pDrawMode", 3, 0, 3));
    pgMsaFluid.add(pDoRGB.set("pDoRGB", true));
    pgMsaFluid.add(pDoVorticityConfinement.set("pDoVorticityConfinement", false));
    pgMsaFluid.add(pDrawFluid.set("pDrawFluid", true));
    pgMsaFluid.add(pDrawParticles.set("pDrawParticles", true));
    pgMsaFluid.add(pWrap_x.set("pWrap_x", false));
    pgMsaFluid.add(pWrap_y.set("pWrap_y", false));
    
    // we add this listener before setting up so the initial circle resolution is correct
    pDrawMode.addListener(this, &matrDolorosaFluid::drawModeChanged);
    pResizeFluid.addListener(this, &matrDolorosaFluid::resizeFluidPressed);
    
    panel.setup(pgMsaFluid);
    panel.loadFromFile("fluid.xml");
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8080,"localhost", 8081);
    
    ofSetWindowShape(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
    pMouse = msa::getWindowCenter();
    resizeFluid			= true;
    
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);

}


void matrDolorosaFluid::fadeToColor(float r, float g, float b, float speed) {
    glColor4f(r, g, b, speed);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}


// add force and dye to fluid, and create particles
void matrDolorosaFluid::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce) {
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0) {
        pos.x = ofClamp(pos.x, 0.0f, 1.0f);
        pos.y = ofClamp(pos.y, 0.0f, 1.0f);
        
        int index = fluidSolver.getIndexForPos(pos);
        
        if(addColor) {
            //			Color drawColor(CM_HSV, (getElapsedFrames() % 360) / 360.0f, 1, 1);
            ofColor drawColor;
            drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
            
            fluidSolver.addColorAtIndex(index, drawColor * colorMult);
            
            if(drawParticles)
                particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
        }
        
        if(addForce)
            fluidSolver.addForceAtIndex(index, vel * velocityMult);
        
    }
}


void matrDolorosaFluid::update(){
    
    //
    sync.update();
    //    GUI -> MSA
    
    fluidCellsX = pFluidCellsX;
    colorMult = pColorMult;
    velocityMult = pVelocityMult;
    fluidSolver.viscocity = pViscocity;
    fluidSolver.colorDiffusion = pColorDiffusion;
    fluidSolver.fadeSpeed = pFadeSpeed;
    fluidSolver.solverIterations = pSolverIterations;
    fluidSolver.deltaT = pDeltaT;
    //fluidDrawer.drawMode = pDrawMode;
    fluidSolver.doRGB = pDoRGB;
    fluidSolver.doVorticityConfinement = pDoVorticityConfinement;
    drawFluid = pDrawFluid;
    drawParticles = pDrawParticles;
    fluidSolver.wrap_x = pWrap_x;
    fluidSolver.wrap_y = pWrap_y;
/*
    if(resizeFluid) 	{
        fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
        fluidDrawer.setup(&fluidSolver);
        resizeFluid = false;
    }
 */
    
    fluidSolver.update();
    
    
    
}

void matrDolorosaFluid::draw(){

    if(drawFluid) {
        ofClear(0);
        glColor3f(1, 1, 1);
        fluidDrawer.draw(0, 0, ofGetWidth(), ofGetHeight());
    } else {
        fadeToColor(0, 0, 0, 0.01);
    }
    
    if(drawParticles){
        particleSystem.updateAndDraw(fluidSolver, ofGetWindowSize(), drawFluid);
    }
    
    // GUI
    gui.draw();
    
}


void matrDolorosaFluid::keyPressed  (int key){

}


//--------------------------------------------------------------
void matrDolorosaFluid::mouseMoved(int x, int y){
    ofVec2f eventPos = ofVec2f(x, y);
    ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
    ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
    addToFluid(mouseNorm, mouseVel, true, true);
    pMouse = eventPos;
}

void matrDolorosaFluid::mouseDragged(int x, int y, int button) {
    ofVec2f eventPos = ofVec2f(x, y);
    ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
    ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
    addToFluid(mouseNorm, mouseVel, false, true);
    pMouse = eventPos;
}


//--------------------------------------------------------------
void matrDolorosaFluid::drawModeChanged(int & _pDrawMode){
    switch (_pDrawMode) {
        case 0:
            fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
            break;
            
        case 1:
            fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);
            break;
            
        case 2:
            fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
            break;
            
        case 3:
            fluidDrawer.setDrawMode(msa::fluid::kDrawVectors);
            break;
            
        default:
            break;
    }
}
//--------------------------------------------------------------
void matrDolorosaFluid::resizeFluidPressed(bool & _pResizeFluid){
    if(pResizeFluid==true){
        fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
        fluidDrawer.setup(&fluidSolver);
        pResizeFluid = false;
    }
}

