//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#include "Finestra.hpp"


void Finestra::setup(ofPoint Pos, ofPoint CropSize, ofPoint TileSize, ofPoint ID, ofImage* Picture)
{
    pos = Pos;
    cropSize = CropSize;
    tileSize = TileSize;
    id = ID;
    active = true;
    picture = Picture;
    
    ofLogVerbose("Loaded finestra") << " Pos " << pos << " crop " << cropSize << " tile " << tileSize;
    
}

void Finestra::update()
{
    
}

void Finestra::draw()
{
    ofPushStyle();
    
    if (picture->isAllocated())
    {
        picture->drawSubsection(pos.x, pos.y, cropSize.x, cropSize.y, tileSize.x, tileSize.y);
        ofNoFill();
        ofSetColor(0);
        ofSetLineWidth(FRAME_WIDTH);
        ofDrawRectangle(pos.x, pos.y, tileSize.x, tileSize.y);
    }
    
    ofPopStyle();
}