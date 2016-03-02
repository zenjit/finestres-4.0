//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#ifndef ControlKinect_hpp
#define ControlKinect_hpp

#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"

class ControlKinect {
    
public:
    
    void setup(string deviceName);
    void update();
    void draw(bool drawGui = false);
        
    ofxKinect device;

    ofParameter<bool> bThreshWithOpenCV;
    ofParameter<bool> bDrawPointCloud;
    ofParameter<bool> bEnableDepthNearValueWhite;
    
    ofParameter<int> nearThreshold;
    ofParameter<int> farThreshold;
    
    ofParameter<int> angle;
    
    // Gui params
    ofxPanel gui;    

private:

    ofParameterGroup parameters;
    ofXml settings;
    
    void updateTilt(int & theta);
    
    void drawPointCloud();
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder;
    
    
    // used for viewing the point cloud
    ofEasyCam easyCam;

};

#endif /* ControlKinect_hpp */
