#include "ofApp.h"
//aim at solving particles moveback gap
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2,winHeight/2, 0);
    corePos.set(winCen.x, winCen.y, 0);
    coreRadius = 25;
    
    aggPtlPos.push_back( corePos);
    radiusAggPtl.push_back( coreRadius);
    
    //set inital floating particle
    fltPtlPos.set(100, 4, 0);
    ofVec3f org;
    org.set(0 ,0 ,0);
    fltPtlSpeed =  winCen - fltPtlPos;
    fltPtlSpeed.normalize();
    fltPtlSpeed = 13.0f * fltPtlSpeed;
    
    fltPtlRadius = 25;
    
    
    keyAnimate = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fltPtlPos = fltPtlPos + fltPtlSpeed;
    
    if ( keyAnimate ) {
        if (fltPtlPos.x > winWidth ) {
            fltPtlSpeed.x *= -1.0f;
            fltPtlPos.x = winWidth;
        }else if (fltPtlPos.x < 0 ){
            fltPtlSpeed.x *= -1.0f;
            fltPtlPos.x = 0;
        }
        
        if (fltPtlPos.y > winHeight) {
            fltPtlSpeed.y *= -1.0f;
            fltPtlPos.y = winHeight;
        }else if (fltPtlPos.y < 0 ){
            fltPtlSpeed.y *= -1.0f;
            fltPtlPos.y = 0;
        }
        
        for (int i = 0; i < aggPtlPos.size(); i++) {
            if (fltPtlPos.distance(aggPtlPos[i]) < radiusAggPtl[i]+fltPtlRadius) {
                
                indexHit = i;
                //move floating particle back to avoid overlapping/control overlapping and gap;
                float disAct = fltPtlPos.distance(aggPtlPos[i]);
                float disShould = radiusAggPtl[i] + fltPtlRadius;
                ofVec3f moveBack = fltPtlPos - aggPtlPos[i];
                moveBack.normalize();
                moveBack = moveBack * (disShould - disAct);
                fltPtlPos = fltPtlPos + moveBack;
                
                aggPtlPos.push_back( fltPtlPos);
                radiusAggPtl.push_back( fltPtlRadius);
                //regenerate pos and radius
                float degreeRad = ofRandom(4*PI);
                fltPtlPos.set(500 * sin(degreeRad)+ winCen.x, 500 * cos(degreeRad) + winCen.y, 0);
                
                fltPtlSpeed = winCen - fltPtlPos;
                fltPtlSpeed.normalize();
                fltPtlSpeed = 13.0f * fltPtlSpeed;
                fltPtlRadius = ofRandom(8, 18);
                
                
                
//                keyAnimate = false;
                
                
                
                
                
            }
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor ptlColor;
    ptlColor.set(74, 82, 160,190);
    ofSetColor(ptlColor);
    ofNoFill();
    ofCircle(winCen , 500);
    ofFill();
    
    ofCircle(fltPtlPos , fltPtlRadius);
    for (int i = 0; i < aggPtlPos.size(); i++) {
        if (i == indexHit) {
            ofColor mark;
            mark.set(200);
            ofSetColor(mark);
            ofCircle(aggPtlPos[i], radiusAggPtl[i]);
        }else{
            ofSetColor(ptlColor);
            ofCircle(aggPtlPos[i], radiusAggPtl[i]);
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
