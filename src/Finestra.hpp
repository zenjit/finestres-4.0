//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#ifndef Finestra_hpp
#define Finestra_hpp

#include "ofMain.h"


#define  FRAME_WIDTH 3

class Finestra {
    
public:
        
    void setup(ofPoint Pos, ofPoint CropSize, ofPoint TileSize, ofPoint ID, ofImage* Picture);
    void update();
    void draw();
    
    bool isActive() { return active; }
    
private:
    
    ofImage* picture;
    
    ofPoint pos;
    ofPoint cropSize;
    ofPoint tileSize;
    ofPoint id;
    
    bool active = false;
    
};

#endif /* Finestra_hpp */
