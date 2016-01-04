#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    radiusCore = 45;
    radiusPtl = 20;
    
    coreStart.set(ofGetWidth()/2, ofGetHeight()/2,0);//set the core start at the center of the screen
    floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
    VecSpeed.x = ofRandom(0, 10);
    VecSpeed.y = ofRandom(0, 10);
    VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
    
    particlesagged.push_back(coreStart);

    

    
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
    
    
    floatingPtlPos = floatingPtlPos + 1*VecSpeed;
    if (floatingPtlPos.x > ofGetWidth() || floatingPtlPos.x < 0) {
        VecSpeed.x *= -1;
    }
    
    if (floatingPtlPos.y > ofGetHeight() || floatingPtlPos.y < 0) {
        VecSpeed.y *=-1;
    }
    for (int i = 0; i <= particlesagged.size(); i++) {
        if (floatingPtlPos.distance(particlesagged[i]) <  radiusCore + radiusPtl) {
            
//          particlesagged.set(floatingPtlPos);
            
            particlesagged.push_back(floatingPtlPos);
            floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
            VecSpeed.x = ofRandom(0, 20);
            VecSpeed.y = ofRandom(0, 20);
            VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
            
            
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);

//    ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);
//    cout << "a=" << coreStart.x+ofGetElapsedTimef() << endl;
    ofColor ptlColor;
    ptlColor.set(134, 22, 60,190);
    ofSetColor(ptlColor);
    ofCircle(coreStart.x, coreStart.y, radiusCore);
    ofCircle(floatingPtlPos.x, floatingPtlPos.y, 0, 20);
    if (particlesagged.size() >= 2) {
        for (int i = 0; i <= particlesagged.size(); i++) {
            ofCircle(particlesagged[i].x, particlesagged[i].y, radiusPtl);
        }
    }
 

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
