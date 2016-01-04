#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(false);
    radiusCore = 35;

    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    
    coreStart.set(winWidth/2, winHeight/2,0);//set the core start at the center of the screen
    floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
   
    
    VecSpeed.x = ofRandom(5, 25);
    VecSpeed.y = ofRandom(5, 25);
    VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
    
    particlesagged.push_back(coreStart);
    
    radiusPtl.push_back(ofRandom(10, 35));
    
    
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
    
    if (particlesagged.size() <= 50) {
    
        if (floatingPtlPos.x  > ofGetWidth() || floatingPtlPos.x < 0) {
            VecSpeed.x *= -1;
        }
        
        if (floatingPtlPos.y > ofGetHeight() || floatingPtlPos.y < 0) {
            VecSpeed.y *=-1;
        }
        
        for (int i = 0; i <= particlesagged.size(); i++) {
            if (floatingPtlPos.distance(particlesagged[i]) <  radiusCore + radiusPtl[i+0]) {
                
    //          particlesagged.set(floatingPtlPos);
                
    //            float disAct = floatingPtlPos.distance(particlesagged[i]);
    //            float disShould = radiusPtl[i] + radiusCore;
    //            ofVec3f moveBack = floatingPtlPos[i]-particlesagged[i];
    //            moveBack.normalize();
    //            moveBack = moveBack * abs(disShould - disAct);
    //            
    //            floatingPtlPos = floatingPtlPos + moveBack;
                particlesagged.push_back(floatingPtlPos);
                radiusPtl.push_back(ofRandom(15, 35));
                floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
                VecSpeed.x = ofRandom(12, 35);
                VecSpeed.y = ofRandom(12, 35);
                VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
                
                
            }
       
            
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
//    ofCircle(floatingPtlPos.x, floatingPtlPos.y, 0, radiusPtl[i]);
//    if (particlesagged.size() >= 2) {
//        for (int i = 0; i <= particlesagged.size(); i++) {
//            ofCircle(particlesagged[i].x, particlesagged[i].y, radiusPtl[i]);
//        }
//    }

        for (int i = 1 ; i <= particlesagged.size(); i++) {
            ofCircle(floatingPtlPos, radiusPtl[i]);
            
            
            ofCircle(particlesagged[i], radiusPtl[i]);
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
