#include "ofApp.h"
//DLA 2D V2.0.0
//multi core multi fltPtl
//next versiion gui;
//add aggregate gap;
//backward loop bug occurs;
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2, winHeight/2,0);
    //CORES SETTINGS
    coreNum = 4;
    minCoreRadius = 5.f;
    maxCoreRadius = 25.f;
    minCorePos = -200.f;
    maxCorePos = 200.f;
    for (int i = 0; i < 4; ++i) {
        ofVec3f tempCorePos;
        tempCorePos.set(ofRandom(minCorePos, maxCorePos) + winCen.x, ofRandom(minCorePos, maxCorePos) + winCen.y ,0 );
        corePos.push_back(tempCorePos);
        float tempCoreRadius = ofRandom(minCoreRadius, maxCoreRadius);
        coreRadius.push_back(tempCoreRadius);
    }
    
    //initialize aggPtls
    for (int i = 0; i < coreNum; ++i) {
        aggPtlPos.push_back(corePos[i]);
        aggPtlRadius.push_back(coreRadius[i]);
//        aggPtlGap.push_back(ofNoise(0.f, 1.2f));
    }
    cout << "test" << ofNoise(0.f,0.f) << endl;
    
    
    //setting inital floating particle list
    maxGenRadius = 2700.0f;
    maxfltPtlNum = 60;
    minfltSpeed = 7.0f;
    maxfltSpeed = 27.0f;
    minfltRadius = 3.0f;
    maxfltRadius = 27.0f;
    for (int i = 0; i < maxfltPtlNum; ++i) {
        //fltPtlPos settings
        degreeSeed = ofRandom(0, 4 * PI);
        cout << "degreeSeed:" << degreeSeed << endl;
        ofVec3f tempPos;
        tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y);
        fltPtlPos.push_back(tempPos);
        
        //fltPtlSpeed settings
        ofVec3f tempSpeed;
        tempSpeed = winCen - tempPos;
//        tempSpeed = ofRandom(minfltSpeed,maxfltSpeed) * (1/tempPos.distance(winCen)) * tempSpeed;
        tempSpeed.normalize();
        tempSpeed = tempSpeed * ofRandom(minfltSpeed, maxfltSpeed);
        fltPtlSpeed.push_back(tempSpeed);
        
        //fltPtlRadius settdings
        float tempRadius = ofRandom(minfltRadius, maxfltRadius);
        fltPtlRadius.push_back(tempRadius);
    }
    
    fltPtlCol.set(74, 82, 160, 220);
    
    maxAggPtlNum = 700;
    keyAnimate = true;
    topCam.setDistance(500);
    autoZoom = true;
    
    
}
//--------------------------------------------------------------




//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + " fps");
    
    if ( keyAnimate ) {
        for (int i = 0 ; i < maxfltPtlNum; ++i) {
            fltPtlPos[i] = fltPtlPos[i] + fltPtlSpeed[i];
            
            for (int j = aggPtlPos.size(); j > 0 ; --j) {
                if (fltPtlPos[i].distanceSquared(aggPtlPos[j]) < aggPtlRadius[j]*aggPtlRadius[j] + fltPtlRadius[i]*fltPtlRadius[i]) {
                    indexHit = i;
                    //move floating particle back to avoid overlapping/ control overlaping gap
                    float disAct = fltPtlPos[i].distance(aggPtlPos[j]);
                    float disShould = aggPtlRadius[j] + fltPtlRadius[i];
                    ofVec3f moveBack = fltPtlPos[i] - aggPtlPos[j];
                    moveBack.normalize();
                    moveBack = moveBack * (disShould - disAct);
                    fltPtlPos[i] = fltPtlPos[i] + moveBack;
                    
                    aggPtlPos.push_back( fltPtlPos[i] );
                    aggPtlRadius.push_back( fltPtlRadius[i] );
                    
                    //regenerate pos and radius
                    fltPtlresetbyIndex(i);
                    
                    if (aggPtlPos.size() > maxAggPtlNum) {
                        keyAnimate = false;
                    }
                }else if (fltPtlPos[i].distanceSquared(winCen) > maxGenRadius*maxGenRadius){
                    fltPtlresetbyIndex(i);
                }
            }
        }
    }
    
    if (autoZoom) {
        camDist = ofMap(aggPtlPos.size(), coreNum, 1000+aggPtlPos.size(), 500, 2000);
        topCam.setDistance(camDist);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofCircle(corePos[0],25);
    ofDrawBitmapString("aggPtlNum:" + ofToString(aggPtlPos.size()), 10,20);
    
    topCam.begin();
    ofTranslate(-winCen.x, -winCen.y, 0);
    ofSetColor(fltPtlCol);
    for (int j = 0; j < maxfltPtlNum; ++j) {
        ofCircle(fltPtlPos[j], fltPtlRadius[j]);
    }
    
    
    //plot aggPtls
    for (int i = 0; i < aggPtlPos.size(); ++i) {
        if (i == indexHit) {
            ofColor mark;
            mark.set(199);
            ofCircle(aggPtlPos[i] , aggPtlRadius[i]);
        }else{
            ofColor aggPtlCol;
            aggPtlCol.setHsb(ofMap(i, 0, aggPtlPos.size(), 0, 255), 180, 190);
            ofSetColor(aggPtlCol, 190);
            ofCircle(aggPtlPos[i], aggPtlRadius[i]);
        }
        
    }
    
    topCam.end();
    
}
//--------------------------------------------------------------
void ofApp::fltPtlresetbyIndex(int i){
    degreeSeed = ofRandom(0, 4 * PI);
    cout << "degreeSeed:" << degreeSeed << endl;
    ofVec3f tempPos;
    tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y);
    fltPtlPos[i].set(tempPos);
    
    //fltPtlSpeed settings
    ofVec3f tempSpeed;
    tempSpeed = winCen - tempPos;
    //        tempSpeed = ofRandom(minfltSpeed,maxfltSpeed) * (1/tempPos.distance(winCen)) * tempSpeed;
    tempSpeed.normalize();
    tempSpeed = tempSpeed * ofRandom(minfltSpeed, maxfltSpeed);
    fltPtlSpeed[i].set(tempSpeed);
    
    //fltPtlRadius settdings
    float tempRadius = ofRandom(minfltRadius, maxfltRadius);
    fltPtlRadius[i] = tempRadius;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        keyAnimate = !keyAnimate;
    }
    if (key == 'z') {
        autoZoom = !autoZoom;
    }
    if (key == 'd') {
        maxAggPtlNum += 200;
        keyAnimate = true;
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
