//
//  matrDolorosaMeshes.cpp
//  LiveMat3rDolorosa_ProtoC
//
//  Created by Dudley Smith on 14/02/2016.
//
//

#include "matrDolorosaMeshes.h"

//--------------------------------------------------------------
void matrDolorosaMeshes::setup(){
    
    //mesh.load("Arbor.ply");
    //mesh.load("lofi-bunny.ply");
    ofFile meshExists = ofFile("ANGE_LESS_Exported.obj");
    if (meshExists.exists()) {
        loader.loadModel(meshExists.path());
        mesh = loader.getMesh(0);
        ofLogNotice() << "Mesh loaded :  Nb Meshes:" << ofToString(loader.getMeshCount());
        
    }else{
        ofLogError() << "CRAP : The mesh is not loaded ! " + meshExists.path();
        
    }

    meshes.setName("meshes");
    
    meshes.add(drawFaces.set("drawFaces",false));
    meshes.add(drawWireframe.set("drawWireframe",true));
    meshes.add(faceColor.set("faceColor",ofColor(255),ofColor(0,0),ofColor(255)));
    meshes.add(faceColor.set("faceColor",ofColor(255),ofColor(0,0),ofColor(255)));
    meshes.add(lineWidth.set("lineWidth",1,0,10));
    
    panel.setup(meshes);
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8060,"localhost", 8061);
    
    
    
}

//--------------------------------------------------------------
void matrDolorosaMeshes::draw(){
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPushMatrix();
    ofScale(0.25, 0.25, 0.25);
    ofRotateX(180);
    
    if(drawFaces){
         // PUSH Faces -----------------------------------
        ofPushMatrix();
        ofPushStyle();
            ofSetColor(faceColor);
            mesh.drawFaces();
        ofPopStyle();
        ofPopMatrix();
    }
    
    if(drawWireframe){
        // PUSH Wireframe ------------------------
        ofPushMatrix();
        ofPushStyle();
            ofSetColor(wireColor);
            ofSetLineWidth(lineWidth);
            mesh.drawWireframe();
            mesh.drawVertices();
        ofPopStyle();
        ofPopMatrix();
    }
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPopMatrix();
    

    
}
