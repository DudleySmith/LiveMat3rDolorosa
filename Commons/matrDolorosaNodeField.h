//
//  matrDolorosaNodeFields.h
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 12/03/2016.
//
//

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxAssimpModelLoader.h"

#include "matrDolorosaNode.h"

#define nodeAmountMax 2000

class matrDolorosaNodeField {
	
    vector<matrDolorosaNode> nodeArray;
    float distances[nodeAmountMax][nodeAmountMax];
    
    ofTrueTypeFont oFont;
    
public:
    ofxPanel panel;
    vector<matrDolorosaNode> getNodes();
    int getNbNodes();
    
    ofPolyline          textPoints;
    
    ofxAssimpModelLoader    meshLoader;
    ofMesh                  mesh;
    ofPolyline              meshPoints;
    
    ofParameter<bool>   drawField;

private:
    ofxOscParameterSync sync;
    ofParameterGroup field;
    
    ofParameter<int>    nbNodes;
    ofParameter<bool>   xyLinks;
    ofParameter<bool>   sphereLimit;
    ofParameter<float>  distance;
    ofParameter<float>  entropyBig;
    ofParameter<float>  entropyFine;
    ofParameter<float>  circleSize;
    
    ofParameter<float>  xLimit;
    ofParameter<float>  yLimit;
    ofParameter<float>  zLimit;
    ofParameter<float>  exRadius;
    ofParameter<float>  inRadius;
    
    ofParameter<ofColor>    sphereColor;
    ofParameter<ofColor>    linkColor;
    
    ofParameter<bool>   textReset;
    ofParameter<float>  choiceRatio;
    ofParameter<float>  choiceEntropy;
    
    ofParameter<float>  natureRatio;
    ofParameter<float>  natureEntropy;
    
    ofParameter<float>  textForceRatio;
    ofParameter<float>  textEntropy;
    
    ofParameter<float>  meshForceRatio;
    ofParameter<float>  meshEntropy;
    
    //ofParameter<float>  textEntropyBig;
    //ofParameter<float>  textEntropyFine;
    
    ofParameter<bool>   startText;
    ofParameter<string> textWord;
    ofParameter<int>    textSize;
    ofParameter<string> textFont;
    
    void startPointRecalled(bool &_recall);
    void wordChanged(string &_wordChange);
        
public:
    void setup();
    void setupFont();
    void setupMesh(string _meshFile);
    
    void update();
    void draw();
    void generateNodes(int _nodeAmount);
    void evalDist();
    
};

