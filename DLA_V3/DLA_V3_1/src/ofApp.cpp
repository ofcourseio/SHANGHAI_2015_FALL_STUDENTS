//
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    dla.setup();
    cout << "bl: " << dla.bldrawAggPtl << endl;
    
    dla.dlaCoresetup();
    dla.dlaaggPtlsetup();
    dla.dlafltPtlsetup();
    
    autoZoom = true;
    topCam.setDistance(500);
    topCam.setFarClip(15000);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + " fps");
    
    
    dla.dlaUpdate();
    
    
    
    if (autoZoom) {
        camDist = ofMap(dla.aggPtlPos.size(), 500, 1000+1.5*dla.aggPtlPos.size(), 500, 2000);
        topCam.setDistance(camDist);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    drawInfo();
    
    topCam.begin();
    ofTranslate(-dla.winCen.x, -dla.winCen.y, 0);
    
    //debug enterThread
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofCircle(dla.winCen, dla.enterThread);
    ofFill();
    //
    dla.dlaDrawfltPtls();
    
    if (dla.bldrawAggPtl) {
        dla.dlaDrawaggPtls();
    }
    
//    dlaMesh.draw();
    if (dla.bldrawMesh) {
        dla.dlaDrawMesh();
    }
    
    topCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        dla.keyAnimate = !dla.keyAnimate;
    }
    if (key == 'z') {
        autoZoom = !autoZoom;
    }
    if (key == 'a') {
        dla.maxAggPtlNum += dla.maxAggPtlNum;
        dla.keyAnimate = true;
    }
    if (key == 'd') {
        dla.bldrawAggPtl = !dla.bldrawAggPtl;
    }
    if (key == '2') {
        dla.runIn2d = true;
        dla.runIn3d = false;
    }
    if (key == '3') {
        dla.runIn2d = false;
        dla.runIn3d = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::drawInfo(){
    ofDrawBitmapString("aggPtlNum:" + ofToString(dla.aggPtlPos.size()), 10,20);
    ofDrawBitmapString("press 'z' to  toggle auto zoom: " + ofToString( autoZoom ), 10,30);
    ofDrawBitmapString("cutNumEst:" + ofToString(dla.cutNumEst), 10,40);
    ofDrawBitmapString("cutIndex:" + ofToString(dla.cutIndex), 10,50);
    ofDrawBitmapString("timeElapsed:" + ofToString(ofGetElapsedTimef()), 10,60);
}
