#include "ofApp.h"
#include "ofVec3d.h"
//aim at solving particles moveback gap
//multi particles hit one core
//try to solving ofvec3f presion trunning it into double FAILED
// next time try vector field

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2,winHeight/2, 0);
    corePos.set(winCen.x, winCen.y, 0);
    coreRadius = 15;
    
    aggPtlPos.push_back( corePos);
    radiusAggPtl.push_back( coreRadius);
    maxGenRadius = 700.0f;
    maxPtlNum = 1000;
    //set inital floating particle
    
//    fltPtlPos.set(100, 4, 0);
 
//    fltPtlSpeed =  winCen - fltPtlPos;
//    fltPtlSpeed.normalize();
//    fltPtlSpeed = 13.0f * fltPtlSpeed;
//    fltPtlRadius = 15;
    
    // seting inital floating particle list
    fltPtlNum = 3;
    for (int i = 0; i < fltPtlNum; i++) {
        degreeSeed=ofRandom(4*PI);
        cout << "seed:" << degreeSeed <<endl;
        ofVec3d tempPos;
        tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y,0);
        fltPtlPosES.push_back(tempPos);
        
        ofVec3d tempSpeed;
        tempSpeed = winCen - tempPos;
        cout << "angle" << tempSpeed << endl;
        tempSpeed.normalize();
//        tempSpeed = ofMap(degreeSeed, 0, 4 * PI, 8.0f, 13.0f) * tempSpeed;
        tempSpeed = 13.0f * tempSpeed;
        fltPtlSpeedS.push_back(tempSpeed);
        
        float tempRaduis;
        tempRaduis = ofRandom(2, 17);
        fltPtlRadiusES.push_back(tempRaduis);
        
    }

    keyAnimate = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
    if ( keyAnimate ) {
        for (int j = 0; j < fltPtlNum; j++) {
            fltPtlPosES[j] = fltPtlPosES[j] + fltPtlSpeedS[j];
            
            if (fltPtlPosES[j].x > winWidth ) {
                fltPtlSpeedS[j].x *= -1.0f;
                fltPtlPosES[j].x = winWidth;
            }else if (fltPtlPosES[j].x < 0 ){
                fltPtlSpeedS[j].x *= -1.0f;
                fltPtlPosES[j].x = 0;
            }
            
            if (fltPtlPosES[j].y > winHeight) {
                fltPtlSpeedS[j].y *= -1.0f;
                fltPtlPosES[j].y = winHeight;
            }else if (fltPtlPosES[j].y < 0 ){
                fltPtlSpeedS[j].y *= -1.0f;
                fltPtlPosES[j].y = 0;
            }
            
            for (int i = 0; i < aggPtlPos.size(); i++) {
                if (fltPtlPosES[j].distance(aggPtlPos[i]) < radiusAggPtl[i]+fltPtlRadiusES[j]) {

                    indexHit = i;
                    //move floating particle back to avoid overlapping/control overlapping and gap;
                    float disAct = fltPtlPosES[j].distance(aggPtlPos[i]);
                    float disShould = radiusAggPtl[i] + fltPtlRadiusES[j];
                    ofVec3d moveBack = fltPtlPosES[j] - aggPtlPos[i];
                    moveBack.normalize();
                    moveBack = moveBack * (disShould - disAct);
                    fltPtlPosES[j] = fltPtlPosES[j] + moveBack;

                    aggPtlPos.push_back( fltPtlPosES[j]);
                    radiusAggPtl.push_back( fltPtlRadiusES[j]);


                    //regenerate pos and radius
                    degreeSeed=ofRandom(4*PI);
                    ofVec3d tempPos;
                    
                    tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y,0);
                    cout << tempPos << endl;
                    cout <<"-------------" << endl;
//                    fltPtlPosES.push_back(tempPos);
                    
                    fltPtlPosES[j].set(tempPos);
                    ofVec3d tempSpeed;
                    tempSpeed = winCen - tempPos;
                    tempSpeed.normalize();
                    tempSpeed = 13.0f * tempSpeed;
//                    fltPtlSpeedS.push_back(tempSpeed);
                    fltPtlSpeedS[j].set(tempSpeed);
                    float tempRaduis;
                    tempRaduis = ofRandom(12, 17);
//                    fltPtlRadiusES.push_back(tempRaduis);
                    fltPtlRadiusES[j]=tempRaduis;
                    
                    if (aggPtlPos.size() > maxPtlNum) {
                        keyAnimate = false;
                    }
                    
//                    keyAnimate = false;
                }
            }
        }
    }
        

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
    ofColor ptlColor;
    ptlColor.set(74, 82, 160,190);
    ofSetColor(ptlColor);
    ofNoFill();
    ofCircle(winCen.x ,winCen.y, 500);
    ofFill();
    for (int j = 0; j< fltPtlNum; j++) {
        ofCircle(fltPtlPosES[j].x ,fltPtlPosES[j].y , fltPtlRadiusES[j]);

    }
    
    
    for (int i = 0; i < aggPtlPos.size(); i++) {
        if (i == indexHit) {
            ofColor mark;
            mark.set(200);
            ofSetColor(mark);
            ofCircle(aggPtlPos[i].x, aggPtlPos[i].y, radiusAggPtl[i]);
        }else{
            ofColor ptlColor2;
            ptlColor2.setHsb(ofMap(i, 0, aggPtlPos.size(), 0, 255), 180, 190);
            ptlColor2.a = 170;
            ofSetColor(ptlColor2);
            ofCircle(aggPtlPos[i].x, aggPtlPos[i].y, radiusAggPtl[i]);
        }

    }
    
    
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
