#include "ofApp.h"


void ofApp::setup()
{
    // Settings
	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    // Kinects
    kinect.setup("kinect1");
    
    // Finestres
    controlFinestres.setup(ofGetScreenWidth(), ofGetScreenHeight(), 2, 2);
	
}

//--------------------------------------------------------------
void ofApp::update() {
	
	ofBackground(100, 100, 100);
	
	kinect.update();
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofSetColor(255, 255, 255);

    controlFinestres.draw();
    
    kinect.draw(bDrawGui);

}



//--------------------------------------------------------------
void ofApp::exit() {

    kinect.device.close();
	
}


//--------------------------------------------------------------
void ofApp::keyPressed (int key)
{
    switch (key)
    {
    case 'g':
        bDrawGui = !bDrawGui;
        break;
    case ' ':
        kinect.bThreshWithOpenCV = !kinect.bThreshWithOpenCV;
        break;
     
    case'p':
        kinect.bDrawPointCloud = !kinect.bDrawPointCloud;
        break;
     
    case '>':
    case '.':
        kinect.farThreshold ++;
        if (kinect.farThreshold > 255) kinect.farThreshold = 255;
        break;
     
    case '<':
    case ',':
        kinect.farThreshold --;
        if (kinect.farThreshold < 0) kinect.farThreshold = 0;
        break;
     
    case '+':
    case '=':
        kinect.nearThreshold ++;
        if (kinect.nearThreshold > 255) kinect.nearThreshold = 255;
        break;
     
    case '-':
        kinect.nearThreshold --;
        if (kinect.nearThreshold < 0) kinect.nearThreshold = 0;
        break;
     
    case 'w':
        kinect.device.enableDepthNearValueWhite(!kinect.device.isDepthNearValueWhite());
        break;
     
    case 'o':
        kinect.device.setCameraTiltAngle(kinect.angle); // go back to prev tilt
        kinect.device.open();
        break;
     
    case 'c':
        kinect.device.setCameraTiltAngle(0); // zero the tilt
        kinect.device.close();
        break;
     
    case '1':
        kinect.device.setLed(ofxKinect::LED_GREEN);
        break;
     
    case '2':
        kinect.device.setLed(ofxKinect::LED_YELLOW);
        break;
     
    case '3':
        kinect.device.setLed(ofxKinect::LED_RED);
        break;
     
    case '4':
        kinect.device.setLed(ofxKinect::LED_BLINK_GREEN);
        break;
     
    case '5':
        kinect.device.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
        break;
     
    case '0':
        kinect.device.setLed(ofxKinect::LED_OFF);
        break;
     
    case OF_KEY_UP:
        kinect.angle++;
        if(kinect.angle>30) kinect.angle=30;
        kinect.device.setCameraTiltAngle(kinect.angle);
        break;
     
    case OF_KEY_DOWN:
        kinect.angle--;
        if(kinect.angle<-30) kinect.angle=-30;
        kinect.device.setCameraTiltAngle(kinect.angle);
        break;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}