//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#include "controlFinestres.hpp"

ControlFinestres::ControlFinestres()
{
    
    string scenesPath = "scenes";
    ofDirectory scenesDir(scenesPath);
    scenesDir.listDir();
    
    for (int item = 0; item < scenesDir.size(); item++) {
        
        if (!scenesDir[item].isDirectory()) continue;
        
        ofLogNotice("Found Scene") << scenesDir[item].path();
        
        string picturesPath = scenesDir[item].getAbsolutePath();
        ofDirectory picturesDir(picturesPath);
        picturesDir.allowExt("png");
        picturesDir.listDir();
        
        vector<ofImage> pictures;
        
        for (int p = 0; p < picturesDir.size(); p++)
        {
            //ofLogNotice("Loaded Picture") << picturesDir[p].getAbsolutePath();
            ofImage picture;
            picture.load(picturesDir[p].getAbsolutePath());
            pictures.push_back(picture);
        }
        
        if (pictures.size() > 0 ) scenePictures.push_back(pictures);
    }

    if (scenePictures.size() <= 0)
        ofLogError("No scenes found!!!");
    
    for (int s = 0; s < finestres.size(); s++)
        if (scenePictures[0].size() <= 0) ofLogError("No pictures found!!! in scene ") << s;

}

ControlFinestres::~ControlFinestres()
{
    
}

void ControlFinestres::setup(int width, int height, int tilesH, int tilesV)
{
    
    ofPoint tile = ofPoint(ofGetWindowWidth() / tilesH, ofGetWindowHeight() / tilesV);
    ofPoint crop = ofPoint(1024 / tilesH, 768 / tilesV);
    
    Finestra finestra1;
    finestra1.setup(ofPoint(0,0), crop, tile, ofPoint(0, 0), &scenePictures[0][0]);
    Finestra finestra2;
    finestra2.setup(ofPoint(crop.x,0), crop, tile, ofPoint(0, 1), &scenePictures[0][1]);
    Finestra finestra3;
    finestra3.setup(ofPoint(0,crop.y), crop, tile, ofPoint(1, 0), &scenePictures[0][2]);
    Finestra finestra4;
    finestra4.setup(ofPoint(crop.x,crop.y), crop, tile, ofPoint(1, 1), &scenePictures[0][3]);
    
    vector<Finestra> sceneFinestres;
    sceneFinestres.push_back(finestra1);
    sceneFinestres.push_back(finestra2);
    sceneFinestres.push_back(finestra3);
    sceneFinestres.push_back(finestra4);
    
    finestres.push_back(sceneFinestres);
        
}

void ControlFinestres::update()
{
    
}

void ControlFinestres::draw(bool drawGui)
{
    for (int s = 0; s < finestres.size(); s++)
    for (int f = 0; f < finestres[s].size(); f++)
        finestres[s][f].draw();
    
}