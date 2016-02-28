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
    addMesh("ANGE_LESS_Exported.obj");
    addMesh("ATENA_Exported.obj");
    addMesh("CHILD_Exported.obj");
    addMesh("VIRGEN_Exported.obj");
    addMesh("CHURCH_Exported.obj");
    addMesh("MOUNTAIN_Exported.obj");
    
    meshesPG.setName("meshes");
    
    meshesPG.add(bDrawFaces.set("drawFaces",false));
    meshesPG.add(bDrawWireframe.set("drawWireframe",false));
    
    meshesPG.add(bDrawMeshOne.set("drawMeshOne",false));
    meshesPG.add(bDrawMeshTwo.set("drawMeshTwo",false));
    meshesPG.add(bDrawMeshThree.set("drawMeshThree",false));
    meshesPG.add(bDrawMeshFour.set("drawMeshFour",false));
    meshesPG.add(bDrawMeshFive.set("drawMeshFive",false));
    meshesPG.add(bDrawMeshSix.set("drawMeshSix",false));
    
    meshesPG.add(faceColor.set("faceColor",ofColor(255),ofColor(0,0),ofColor(255)));
    meshesPG.add(wireColor.set("wireColor",ofColor(255),ofColor(0,0),ofColor(255)));
    meshesPG.add(lineWidth.set("lineWidth",1,0,10));
    
    panel.setup(meshesPG);
    // by now needs to pass the gui parameter groups since the panel internally creates it's own group
    sync.setup((ofParameterGroup&)panel.getParameter(),8060,"localhost", 8061);
    
    
    
}

//--------------------------------------------------------------
void matrDolorosaMeshes::addMesh(string meshFile){
    
    ofMesh mesh;
    ofFile meshExists = ofFile(meshFile);
    
    if (meshExists.exists()) {
        loader.loadModel(meshExists.path());
        mesh = loader.getMesh(0);
        
        allMeshes.push_back(mesh);
        
        ofLogNotice() << "Mesh loaded :  Nb Meshes:" << ofToString(loader.getMeshCount());
        
        
    }else{
        ofLogError() << "CRAP : The mesh is not loaded ! " + meshExists.path();
        
    }
    

    
}

//--------------------------------------------------------------
void matrDolorosaMeshes::update(){
    sync.update();
}

//--------------------------------------------------------------
void matrDolorosaMeshes::draw(){
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPushMatrix();
    ofScale(0.25, 0.25, 0.25);
    ofRotateX(180);
    
    if(bDrawFaces){
         // PUSH Faces -----------------------------------
        ofPushMatrix();
        ofPushStyle();
            ofSetColor(faceColor);
            drawFaces();
        ofPopStyle();
        ofPopMatrix();
    }
    
    if(bDrawWireframe){
        // PUSH Wireframe ------------------------
        ofPushMatrix();
        ofPushStyle();
            ofSetColor(wireColor);
            ofSetLineWidth(lineWidth);
            drawWireframe();
        ofPopStyle();
        ofPopMatrix();
    }
    
    // Whole MATRIX Because Mesh is Upside Down
    ofPopMatrix();
    

    
}

//--------------------------------------------------------------
void matrDolorosaMeshes::drawFaces(){

    if(bDrawMeshOne)    allMeshes[0].drawFaces();
    if(bDrawMeshTwo)    allMeshes[1].drawFaces();
    if(bDrawMeshThree)  allMeshes[2].drawFaces();
    if(bDrawMeshFour)   allMeshes[3].drawFaces();
    if(bDrawMeshFive)   allMeshes[4].drawFaces();
    if(bDrawMeshSix)    allMeshes[5].drawFaces();

}

//--------------------------------------------------------------
void matrDolorosaMeshes::drawWireframe(){
    
    if(bDrawMeshOne){
        allMeshes[0].drawWireframe();
        allMeshes[0].drawVertices();
    }
    if(bDrawMeshTwo){
        allMeshes[1].drawWireframe();
        allMeshes[1].drawVertices();
    }
    if(bDrawMeshThree){
        allMeshes[2].drawWireframe();
        allMeshes[2].drawVertices();
    }
    if(bDrawMeshFour){
        allMeshes[3].drawWireframe();
        allMeshes[3].drawVertices();
    }
    if(bDrawMeshFive){
        allMeshes[4].drawWireframe();
        allMeshes[4].drawVertices();
    }
    if(bDrawMeshSix){
        allMeshes[5].drawWireframe();
        allMeshes[5].drawVertices();
    }

}

