#include "ofApp.h"
//DLA 2D V2.0.0
//multi core multi fltPtl
//next versiion gui;
//add aggregate gap;
//backward loop bug occurs; change to normal

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
    maxfltPtlNum = 5;
    minfltSpeed = 7.0f;
    maxfltSpeed = 13.0f;
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
//    soundsetup();
    soundNum = 20;
    
}
//--------------------------------------------------------------




//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + " fps");
    
    if ( keyAnimate ) {
        for (int i = 0 ; i < maxfltPtlNum; ++i) {
            fltPtlPos[i] = fltPtlPos[i] + fltPtlSpeed[i];
            
            for (int j = aggPtlPos.size(); j > 0 ; --j) {
                float compareRadius = aggPtlRadius[j] + fltPtlRadius[i];
                if (fltPtlPos[i].distance(aggPtlPos[j]) < compareRadius) {
                    
                    indexHit = i;
                    
                    soundIndex = ofMap(compareRadius,minfltRadius + minfltRadius , maxfltRadius + maxfltRadius, 0, soundNum);
//                    pnoSound[soundIndex].play();
//                    soundPlay(ofNoise(soundNum));
                    soundPlay(soundIndex);
                    cout << "r1:" << minfltRadius << "," << "r2:" << maxfltRadius << endl;
                    cout << "index:" << soundIndex << "compRad:"<< compareRadius<< endl;
                    cout << soundNum << endl;
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
                }else if (fltPtlPos[i].distance(winCen) > maxGenRadius){
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
//void ofApp::soundsetup(){
//    soundNum = 14;
//    pnoSound.assign(soundNum, "A6.MP3");
//    for (int i = 0 ; i < soundNum; ++i) {
//        switch (i) {
//            case 0:
//                pnoSound[i].loadSound("A6.MP3");
//                break;
//            case 1:
//                pnoSound[i].loadSound("A7.MP3");
//                break;
//            case 2:
//                pnoSound[i].loadSound("B6.MP3");
//                break;
//            case 3:
//                pnoSound[i].loadSound("B7.MP3");
//                break;
//            case 4:
//                pnoSound[i].loadSound("C6.MP3");
//                break;
//            case 5:
//                pnoSound[i].loadSound("C7.MP3");
//                break;
//            case 6:
//                pnoSound[i].loadSound("D6.MP3");
//                break;
//            case 7:
//                pnoSound[i].loadSound("D7.MP3");
//                break;
//            case 8:
//                pnoSound[i].loadSound("E6.MP3");
//                break;
//            case 9:
//                pnoSound[i].loadSound("E7.MP3");
//                break;
//            case 10:
//                pnoSound[i].loadSound("F6.MP3");
//                break;
//            case 11:
//                pnoSound[i].loadSound("F7.MP3");
//                break;
//            case 12:
//                pnoSound[i].loadSound("G6.MP3");
//                break;
//            case 13:
//                pnoSound[i].loadSound("G7.MP3");
//                break;
//                
//        }
//    }
//    
//}
//--------------------------------------------------------------
void ofApp::soundPlay(int i){
    soundNum = 20;
    

    switch (i) {
        case 0:
            mySound.loadSound("A6.MP3");
            mySound.play();
            break;
        case 1:
            mySound.loadSound("A7.MP3");
            mySound.play();
            break;
        case 2:
            mySound.loadSound("B6.MP3");
            mySound.play();
            break;
        case 3:
            mySound.loadSound("B7.MP3");
            mySound.play();
            break;
        case 4:
            mySound.loadSound("C1.MP3");
            mySound.play();
            break;
        case 5:
            mySound.loadSound("C2.MP3");
            mySound.play();
            break;
        case 6:
            mySound.loadSound("C3.MP3");
            mySound.play();
            break;
        case 7:
            mySound.loadSound("C4.MP3");
            mySound.play();
            break;
        case 8:
            mySound.loadSound("C5.MP3");
            mySound.play();
            break;
        case 9:
            mySound.loadSound("C6.MP3");
            mySound.play();
            break;
        case 10:
            mySound.loadSound("C7.MP3");
            mySound.play();
            break;
        case 11:
            mySound.loadSound("C8.MP3");
            mySound.play();
            break;
        case 12:
            mySound.loadSound("D6.MP3");
            mySound.play();
            break;
        case 13:
            mySound.loadSound("D7.MP3");
            mySound.play();
            break;
        case 14:
            mySound.loadSound("E6.MP3");
            mySound.play();
            break;
        case 15:
            mySound.loadSound("E7.MP3");
            mySound.play();
            break;
        case 16:
            mySound.loadSound("F6.MP3");
            mySound.play();
            break;
        case 17:
            mySound.loadSound("F7.MP3");
            mySound.play();
            break;
        case 18:
            mySound.loadSound("G6.MP3");
            mySound.play();
            break;
        case 19:
            mySound.loadSound("G7.MP3");
            mySound.play();
            break;
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
