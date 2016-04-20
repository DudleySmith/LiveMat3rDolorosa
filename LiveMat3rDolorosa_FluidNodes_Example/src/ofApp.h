#pragma once

#include "ofMain.h"
#include "matrDolorosaFluid.h"
#include "matrDolorosaNodeField.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    matrDolorosaFluid   fluid;
    matrDolorosaNodeField field;
    
    ofEasyCam cam;
    
public:
    ofxPanel panel;
    
private:
    ofxOscParameterSync sync;
    ofParameterGroup pgPoints;
    
    ofParameter<float> pSpeedX;
    ofParameter<float> pSpeedY;
    
    ofPoint onePoint;
    ofPoint oneSens;
    ofPoint oneVel;
    

    
};
