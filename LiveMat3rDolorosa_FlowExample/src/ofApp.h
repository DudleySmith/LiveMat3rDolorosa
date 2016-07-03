#pragma once

#include "ofMain.h"
#include "flowToolsApp.h"
#include "ofxOsc.h"
#include "matrDolorosa_Text.h"
#include "matrDolorosa_FontPathBlend.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void drawText();
		
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
    
    flowToolsApp flowTool;
    
    ofVideoPlayer fade;
    ofVideoPlayer zoom;
    
    matrDolorosa_Text text;
    matrDolorosa_FontPathBlend fontBlend;
    
    string            newWord;
};
