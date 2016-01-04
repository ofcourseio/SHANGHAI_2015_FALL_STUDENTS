#include "ofApp.h"
//debugging gap between different radius particles
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(false);
    radiusCore = 20;
    radiusPtl = 20;
    
    coreStart.set(ofGetWidth()/2, ofGetHeight()/2,0);//set the core start at the center of the screen
    
    org.set(ofGetWidth()/2, ofGetHeight()/2, 0);
//    floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
    float degreeRad = ofRandom(2*PI);
    
    floatingPtlPos.set(500*sin(degreeRad)+ofGetWidth()/2, 500*cos(degreeRad)+ofGetHeight()/2,0);
//    VecSpeed.set(ofRandom(0, 20), ofRandom(0, 20));
    cout << "********************************" << endl;
    cout << "floatingPtPos:" << floatingPtlPos << endl;
    //setup speed
    vecDir =  org - floatingPtlPos;
    cout << "vecDir:" << vecDir << endl;
    vecDir.normalize();
    VecSpeed = ofRandom(10,20) * vecDir;
    
    particlesagged.push_back(coreStart);
    radiusAggPtl.push_back(radiusCore);
//    radiusAggPtl.push_back(radiusPtl);
    
//    radiusAggPtl.push_back(radiusCore);
//    radiusAggPtl.push_back(radiusPtl);
//    for (int i =0; i<10000; ++i) {
//        radiusAggPtl.push_back(ofRandom(7, 22));
//    }
    

    keyAnimate = true;

    cout << "VecSpeed:" << VecSpeed << endl;
    
    cout << "********************************" << endl;
    
    cam.setDistance(400);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
//    ofCircle(coreStart.x + ofGetElapsedTimef(), coreStart.y, 110);
//    floatingPtlPos.x += floatingPtlPos.x + VecSpeed.x;
//    floatingPtlPos.y += floatingPtlPos.y + VecSpeed.y;
//    cout << "floatingPtPos:" << floatingPtlPos << endl;
//    cout << "VecSpeed:" << VecSpeed << endl;
//    cout << "--------------------------------" << endl;
//    sideNum = ofRandom(1,5);
//    cout << "sideNum" << sideNum <<endl;
//    org.set(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    if (keyAnimate) {
        floatingPtlPos = floatingPtlPos + 1*VecSpeed;
    }
    //telling if particles go outside
        if (floatingPtlPos.x > ofGetWidth()  ) {
            VecSpeed.x *= -1;
            floatingPtlPos.x = ofGetWidth();
        }else if (floatingPtlPos.x < 0){
            VecSpeed.x *= -1;
            floatingPtlPos.x = 0;
        }
        
        if (floatingPtlPos.y > ofGetHeight()  ) {
            VecSpeed.y *= -1;
            floatingPtlPos.y = ofGetHeight();
        }else if (floatingPtlPos.y < 0){
            VecSpeed.y *= -1;
            floatingPtlPos.y = 0;
        }
        
        for (int i = 0; i < particlesagged.size(); i++) {
            if (floatingPtlPos.distance(particlesagged[i]) <  radiusAggPtl[0] + radiusAggPtl[i]) {
                
                index = i;
                float disAct = floatingPtlPos.distance(particlesagged[i]);
                float disShould = radiusPtl + radiusCore;
                //move back
                ofVec3f moveBack = floatingPtlPos-particlesagged[i];
                moveBack.normalize();
                moveBack = moveBack * (disShould - disAct);
                floatingPtlPos = floatingPtlPos + moveBack;
                particlesagged.push_back(floatingPtlPos);
//                radiusAggPtl.push_back(ofRandom(14,25));

                radiusAggPtl.push_back(radiusPtl);
                radiusPtl = ofRandom(7, 23);
                //reset paras
//                floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
                
                
                float degreeRad = ofRandom(2*PI);
                
                floatingPtlPos.set(500*sin(degreeRad)+ofGetWidth()/2, 500*cos(degreeRad)+ofGetHeight()/2,0);
//                for (int j = 0; j < particlesagged.size(); i++) {
//                    if (floatingPtlPos.distance(particlesagged[j]) < radiusCore + radiusPtl) {
//                        floatingPtlPos.set(400*sin(degreeRad)+ofGetWidth()/2, 400*cos(degreeRad)+ofGetHeight()/2,0);
//                    }
//                }
    //            VecSpeed.x = ofRandom(0, 20);
    //            VecSpeed.y = ofRandom(0, 20);
    //            VecSpeed.set(VecSpeed.x, VecSpeed.y,0);
                VecSpeed = org - floatingPtlPos ;
                VecSpeed.normalize();
                VecSpeed = 20*VecSpeed;
                
//                keyAnimate = false;
                
                cout << "floatingPtPos:" << floatingPtlPos << endl;
                cout << "VecSpeed:" << VecSpeed << endl;
                cout << "moveBack" << moveBack << endl;
                cout << "--------------------------------" << endl;
                
            }
        }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);

//    ofCircle(coreStart.x+ofGetElapsedTimef(), coreStart.y, 110);
//    cout << "a=" << coreStart.x+ofGetElapsedTimef() << endl;
//    cam.begin();
    ofColor ptlColor;
    ptlColor.set(74, 82, 160,190);
    ofSetColor(ptlColor);
    ofNoFill();
    ofCircle(coreStart.x, coreStart.y, 400);
    ofFill();
//    ofCircle(coreStart, radiusCore);

    ofCircle(floatingPtlPos.x, floatingPtlPos.y, 0, radiusPtl);
    if (particlesagged.size() >= 2) {
        for (int i = 0; i < particlesagged.size(); i++) {
            
            if (i == index) {
                ofColor mark;
                mark.set(200);
                ofSetColor(mark);
                ofCircle(particlesagged[i].x, particlesagged[i].y, radiusAggPtl[i]);
            }else{
                ofColor normal;
                normal.set(74,82,160,190);
                ofSetColor(normal);
                ofCircle(particlesagged[i].x, particlesagged[i].y, radiusAggPtl[i]);
            }
        }
    }
//    cam.end();
//    if (keyAnimate == true) {
//        ;
//    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        keyAnimate = !keyAnimate;
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
