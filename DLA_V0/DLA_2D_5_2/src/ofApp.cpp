#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(false);
    radiusCore = 25;
    radiusPtl = 25;
    
    coreStart.set(ofGetWidth()/2, ofGetHeight()/2,0);//set the core start at the center of the screen
//    floatingPtlPos.x = ;

//    if (<#condition#>) {
//        <#statements#>
//    }
//    sideNum = int(ofRandom(4));
    
    org.set(ofGetWidth()/2, ofGetHeight()/2, 0);
//    floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
    float degreeRad = ofRandom(2*PI);
    
    floatingPtlPos.set(400*sin(degreeRad)+ofGetWidth()/2, 400*cos(degreeRad)+ofGetHeight()/2);
//    VecSpeed.x = ofRandom(0, 20);
//    VecSpeed.y = ofRandom(0, 20);
//    VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
//    VecSpeed = floatingPtlPos - org;
    VecSpeed = floatingPtlPos - org;
    VecSpeed.normalize();
    VecSpeed = ofRandom(10,20)*VecSpeed;
    
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
//    sideNum = ofRandom(1,5);
//    cout << "sideNum" << sideNum <<endl;
    org.set(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    
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
            
            float disAct = floatingPtlPos.distance(particlesagged[i]);
            float disShould = radiusPtl + radiusCore;
            ofVec3f moveBack = floatingPtlPos[i]-particlesagged[i];
            moveBack.normalize();
            moveBack = moveBack * (disShould - disAct);
//            moveBack = moveBack * disShould;
            floatingPtlPos = floatingPtlPos + moveBack;
            
            particlesagged.push_back(floatingPtlPos);
            floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
            float degreeRad = ofRandom(2*PI);
            
            floatingPtlPos.set(400*sin(degreeRad)+ofGetWidth()/2, 400*cos(degreeRad)+ofGetHeight()/2);
//            VecSpeed.x = ofRandom(0, 20);
//            VecSpeed.y = ofRandom(0, 20);
//            VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
            VecSpeed = -1*(floatingPtlPos - org);
            VecSpeed.normalize();
            VecSpeed = ofRandom(10,20)*VecSpeed;
            
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
    ofNoFill();
    ofCircle(coreStart.x, coreStart.y, 400);
    ofFill();
    ofCircle(coreStart.x, coreStart.y, radiusCore);

    ofCircle(floatingPtlPos.x, floatingPtlPos.y, 0, radiusPtl);
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
