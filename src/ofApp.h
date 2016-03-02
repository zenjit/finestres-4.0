#pragma once

#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxAbletonLive.h"

#include "ControlKinect.hpp"
#include "ControlFinestres.hpp"

class ofApp : public ofBaseApp {
public:
    
    
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
    
    // Kinect
	ControlKinect   kinect;
    
    // Ableton
    ofxAbletonLive  abletonLive;
    
    // Finestres
    ControlFinestres controlFinestres;
    
    // Gui
    bool bDrawGui = true;
    
	
};
