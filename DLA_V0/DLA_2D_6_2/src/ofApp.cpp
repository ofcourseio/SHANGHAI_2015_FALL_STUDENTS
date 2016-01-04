#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
//    ofSetVerticalSync(false);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    //core setups
    coreRadius = 35;
    corePos.set(winWidth/2, winHeight/2, 0);
    //
    for (int i = 0; i < 3; i++) {
        ofVec3f tmpfltPtlPos;
        tmpfltPtlPos.set(ofRandom(winWidth), ofRandom(winHeight));
        fltPtlPos.push_back(tmpfltPtlPos);
        
    }

    
}

//--------------------------------------------------------------
void ofApp::update(){

    

}

//--------------------------------------------------------------
void ofApp::draw(){



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
