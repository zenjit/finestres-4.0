//
//  controlFinestres.cpp
//  finestres
//
//  Created by Corrado Scanavino on 20/2/16 para Convent Sant Agusti
//
//

#include "ControlKinect.hpp"


void ControlKinect::setup(string deviceName)
{
    // enable depth->video image calibration
    device.setRegistration(true);
    
    device.init();
    //device.init(true); // shows infrared instead of RGB video image
    //device.init(false, false); // disable video image (faster fps)
    
    device.open();		// opens first available kinect
    //device.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //device.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(device.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << device.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << device.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << device.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << device.getZeroPlaneDistance() << "mm";
    } else {
        cout << "No device connected!" << endl;
    }

    
    colorImg.allocate(device.width, device.height);
    grayImage.allocate(device.width, device.height);
    grayThreshNear.allocate(device.width, device.height);
    grayThreshFar.allocate(device.width, device.height);
    
    // Gui
    string settingsFile = "settings/" + deviceName + ".xml";
    parameters.setName(deviceName);
    parameters.add(bThreshWithOpenCV.set("Thresholding", true));
    parameters.add(bDrawPointCloud.set("Draw Point Cloud", false));
    parameters.add(bEnableDepthNearValueWhite.set("Enable D Near White", true));
    parameters.add(nearThreshold.set("Near Threshold", 230, 0, 300));
    parameters.add(farThreshold.set("Far Threshold", 70, 0, 100));
    parameters.add(angle.set("Tilt", 0, -30, 30));
    gui.setup(parameters, settingsFile);
    gui.loadFromFile(settingsFile);

    // Listeners
    angle.addListener(this, &ControlKinect::updateTilt);

    device.setCameraTiltAngle(angle);
    
}

void ControlKinect::updateTilt(int & theta)
{
    device.setCameraTiltAngle(theta);
}

void ControlKinect::update()
{
    device.update();
    
    // there is a new frame and we are connected
    if(device.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(device.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (device.width*device.height)/2, 20, false);
    }

}

void ControlKinect::draw(bool drawGui)
{
    if (!drawGui) return;
    
    if(bDrawPointCloud) {
        easyCam.begin();
        drawPointCloud();
        easyCam.end();
    } else {
        // draw from the live kinect
        device.drawDepth(10, 10, 400, 300);
        device.draw(420, 10, 400, 300);
        
        if (grayImage.bAllocated) grayImage.draw(10, 320, 400, 300);
        contourFinder.draw(10, 320, 400, 300);
    }
    
    
    // draw instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    if(device.hasAccelControl()) {
        reportStream << "accel is: " << ofToString(device.getMksAccel().x, 2) << " / "
        << ofToString(device.getMksAccel().y, 2) << " / "
        << ofToString(device.getMksAccel().z, 2) << endl;
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
    << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    << ", fps: " << ofGetFrameRate() << endl
    << "press c to close the connection and o to open it again, connection is: " << device.isConnected() << endl;
    
    if(device.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
        << "press 1-5 & 0 to change the led mode" << endl;
    }
    
    ofDrawBitmapString(reportStream.str(), 20, 652);

    
    // Gui
    gui.draw();

}

void ControlKinect::drawPointCloud()
{
    int w = 640;
    int h = 480;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int step = 2;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(device.getDistanceAt(x, y) > 0) {
                mesh.addColor(device.getColorAt(x,y));
                mesh.addVertex(device.getWorldCoordinateAt(x, y));
            }
        }
    }
    glPointSize(3);
    ofPushMatrix();
    // the projected points are 'upside down' and 'backwards'
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableDepthTest();
    mesh.drawVertices();
    ofDisableDepthTest();
    ofPopMatrix();
}
