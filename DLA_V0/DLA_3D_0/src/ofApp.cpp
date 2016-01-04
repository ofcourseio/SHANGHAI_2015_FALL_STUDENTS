#include "ofApp.h"
//DLA_3D_0

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
    
    floatingPtlPos.set(500*sin(degreeRad)+ofGetWidth()/2, 500*cos(degreeRad)+ofGetHeight()/2,ofRandom(-1000, 1000));
//    VecSpeed.set(ofRandom(0, 20), ofRandom(0, 20));
//    VecSpeed = floatingPtlPos - org;
    cout << "********************************" << endl;
    cout << "floatingPtPos:" << floatingPtlPos << endl;
    vecDir =  org - floatingPtlPos;
    cout << "vecDir:" << vecDir << endl;
    vecDir.normalize();
    VecSpeed = ofRandom(10,20) * vecDir;
    
    particlesagged.push_back(coreStart);

    keyAnimate = true;

    cout << "VecSpeed:" << VecSpeed << endl;
    
    cout << "********************************" << endl;
    
    cam.setDistance(600);
    cam.lookAt(coreStart);
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
    
        if (floatingPtlPos.z > 1000  ) {
            VecSpeed.z *= -1;
            floatingPtlPos.z = 1000;
        }else if (floatingPtlPos.z < -1000){
            VecSpeed.z *= -1;
            floatingPtlPos.z = -1000;
        }
    
        for (int i = 0; i <= particlesagged.size(); i++) {
            if (floatingPtlPos.distance(particlesagged[i]) <  radiusCore + radiusPtl) {
                
                
                float disAct = floatingPtlPos.distance(particlesagged[i]);
                float disShould = radiusPtl + radiusCore;
                //move back
                ofVec3f moveBack = floatingPtlPos-particlesagged[i];
                moveBack.normalize();
                moveBack = moveBack * (disShould - disAct);
                floatingPtlPos = floatingPtlPos + moveBack;
                particlesagged.push_back(floatingPtlPos);
                
                //reset paras
//                floatingPtlPos.set(ofRandom(0,ofGetWidth()),ofRandom(0, ofGetHeight()), 0);
                
                
                float degreeRad = ofRandom(2*PI);
                
                floatingPtlPos.set(500*sin(degreeRad)+ofGetWidth()/2, 500*cos(degreeRad)+ofGetHeight()/2,ofRandom(-1000, 1000));
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
                VecSpeed = 11*VecSpeed;
                
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
    cam.begin();
    ofColor ptlColor;
    ptlColor.set(134, 175, 60,190);
    ofSetColor(ptlColor);
    ofNoFill();
    ofCircle(coreStart.x, coreStart.y, 500);
    ofFill();
//    ofCircle(coreStart, radiusCore);

    ofCircle(floatingPtlPos.x, floatingPtlPos.y, floatingPtlPos.z, radiusPtl);
    if (particlesagged.size() >= 2) {
        for (int i = 0; i < particlesagged.size(); i++) {
            ofCircle(particlesagged[i].x, particlesagged[i].y, particlesagged[i].z, radiusPtl);
//            sphere.setPosition(particlesagged[i]);
//            sphere.setRadius(radiusPtl);
//            sphere.draw();
            
        }
    }
    cam.end();
//    if (keyAnimate == true) {
//        <#statements#>
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
