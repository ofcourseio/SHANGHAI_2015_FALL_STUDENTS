#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    coreStart.set(ofGetWidth()/2, ofGetHeight()/2,0);//set the core start at the center of the screen
    floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
    VecSpeed.x = ofRandom(0, 10);
    VecSpeed.y = ofRandom(0, 10);
    VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
//    coreStart.x +=ofGetElapsedTimef();
  //  cout << "a=" << ofGetElapsedTimef() << endl;
//
//    ofCircle(coreStart.x + ofGetElapsedTimef(), coreStart.y, 110);
//    floatingPtlPos.x += floatingPtlPos.x + VecSpeed.x;
//    floatingPtlPos.y += floatingPtlPos.y + VecSpeed.y;
    cout << "floatingPtPos:" << floatingPtlPos << endl;
    cout << "VecSpeed:" << VecSpeed << endl;
    floatingPtlPos = floatingPtlPos + VecSpeed;
    if (floatingPtlPos.x > ofGetWidth() || floatingPtlPos.x < 0) {
        VecSpeed.x *= -1;
    }
    
    if (floatingPtlPos.y > ofGetHeight() || floatingPtlPos.y < 0) {
        VecSpeed.y *=-1;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);

//    ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);
//    cout << "a=" << coreStart.x+ofGetElapsedTimef() << endl;
    ofCircle(floatingPtlPos.x, floatingPtlPos.y, 0, 20);

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
