//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#ifndef ControlFinestres_hpp
#define ControlFinestres_hpp

#include "ofMain.h"

#include "Finestra.hpp"

class ControlFinestres {
    
public:
    
    ControlFinestres();
    ~ControlFinestres();
      
    void setup(int width, int height, int tilesH, int tilesV);
    void update();
    void draw(bool drawGui = false);
    
private:
    
    vector<vector <Finestra>> finestres;
    vector<vector <ofImage>> scenePictures;

};

#endif /* ControlFinestres_hpp */
