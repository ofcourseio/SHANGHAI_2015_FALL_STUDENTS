#include "ofApp.h"
//aim at solving particles moveback gap solved
//multi particles hit one core
//trails on 3D aggregation : worked
//but framerate gets slow

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2,winHeight/2, 0);
//    winCen.set(0,0, 0);
//    ofVec3f
    corePos.set(winCen.x, winCen.y, 0);
    coreRadius = 15;
    
    aggPtlPos.push_back( corePos);
    radiusAggPtl.push_back( coreRadius);
    maxGenRadius = 1900.0f;
    maxPtlNum = 3000;
    //set inital floating particle
    
//    fltPtlPos.set(100, 4, 0);
 
//    fltPtlSpeed =  winCen - fltPtlPos;
//    fltPtlSpeed.normalize();
//    fltPtlSpeed = 13.0f * fltPtlSpeed;
//    fltPtlRadius = 15;
    
    // seting inital floating particle list
    fltPtlNum = 25;
    for (int i = 0; i < fltPtlNum; i++) {
        degreeSeed=ofRandom(4*PI);
        degreeSeedPhi = ofRandom(-2 * PI, 2*PI);
        cout << "seed:" << degreeSeed <<endl;
        ofVec3f tempPos;
        tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y,maxGenRadius * sin(degreeSeedPhi));
        fltPtlPosES.push_back(tempPos);
        
        ofVec3f tempSpeed;
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
    
    ofEnableDepthTest();
    topCam.setDistance(500);
//    topCam.lookAt(winCen);
    
    //3dprimitiveshpere
//    aggPtlSphere.assign(1000, 0);
    
    ofEnableLighting();
    
    aggPtlSphere.setResolution(4);
}

//--------------------------------------------------------------
void ofApp::update(){

    
    if ( keyAnimate ) {
        for (int j = 0; j < fltPtlNum; j++) {
            fltPtlPosES[j] = fltPtlPosES[j] + fltPtlSpeedS[j];
            

            // try while loop next version
            for (int i = 0; i < aggPtlPos.size(); i++) {
                
                if (fltPtlPosES[j].distance(aggPtlPos[i]) < radiusAggPtl[i]+fltPtlRadiusES[j]) {

                    indexHit = i;
                    //move floating particle back to avoid overlapping/control overlapping and gap;
                    float disAct = fltPtlPosES[j].distance(aggPtlPos[i]);
                    float disShould = radiusAggPtl[i] + fltPtlRadiusES[j];
                    ofVec3f moveBack = fltPtlPosES[j] - aggPtlPos[i];
                    moveBack.normalize();
                    moveBack = moveBack * (disShould - disAct);
                    fltPtlPosES[j] = fltPtlPosES[j] + moveBack;

                    aggPtlPos.push_back( fltPtlPosES[j]);
                    radiusAggPtl.push_back( fltPtlRadiusES[j]);


                    //regenerate pos and radius
                    degreeSeed=ofRandom(4*PI);
                    ofVec3f tempPos;
                    degreeSeedPhi = ofRandom(-2 * PI, 2*PI);
                    tempPos.set(maxGenRadius * sin(degreeSeed) + winCen.x, maxGenRadius * cos(degreeSeed) + winCen.y,maxGenRadius * sin(degreeSeedPhi));
                    cout << tempPos << endl;
                    cout <<"-------------" << endl;
//                    fltPtlPosES.push_back(tempPos);
                    
                    fltPtlPosES[j].set(tempPos);
                    ofVec3f tempSpeed;
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
                    
                    
                    if (fltPtlPosES[j].distance(winCen) > 1.5*maxGenRadius) {
                        fltPtlPosES[j].set(tempPos);
                        ofVec3f tempSpeed;
                        tempSpeed = winCen - tempPos;
                        tempSpeed.normalize();
                        tempSpeed = 13.0f * tempSpeed;
                        //                    fltPtlSpeedS.push_back(tempSpeed);
                        fltPtlSpeedS[j].set(tempSpeed);
                        float tempRaduis;
                        tempRaduis = ofRandom(12, 17);
                        //                    fltPtlRadiusES.push_back(tempRaduis);
                        fltPtlRadiusES[j]=tempRaduis;
                    }

                }
            }
        }
        topCam.setDistance(ofMap(aggPtlPos.size(), 300, 1000+aggPtlPos.size(), 600, 1800));
    }
        
    float camDis;
    
//    topCam.setDistance(600+20*ofGetElapsedTimef());
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
    ofDrawBitmapString("spherenumber:" +  ofToString(maxPtlNum), 10, 30);
    ofDrawBitmapString("currentnumber:" +  ofToString(aggPtlPos.size()), 10, 40);
    
    
    ofEnableLighting();
    topCam.begin();
    lighttest1.enable();
    ofTranslate(-winCen.x, -winCen.y,0);
    ofColor ptlColor;
    ptlColor.set(74, 82, 160,190);
    ofSetColor(ptlColor);
    ofNoFill();
    ofCircle(winCen , maxGenRadius);
    ofFill();
    for (int j = 0; j< fltPtlNum; j++) {
        ofCircle(fltPtlPosES[j] , fltPtlRadiusES[j]);
        
//        ofDrawSphere(fltPtlPosES[j], fltPtlRadiusES[j]);
        
        
        
    }
    
    
    //set primitive shpere
//    for (int k = 0; k < aggPtlPos.size(); k++) {
//        aggPtlSphere[k].setPosition(aggPtlPos[k]);
//        aggPtlSphere[k].setRadius(radiusAggPtl[k]);
//        
//        aggPtlSphere[k].draw();
//        
//    }
    
   
    
    for (int i = 0; i < aggPtlPos.size(); i++) {
        if (i == indexHit) {
            ofColor mark;
            mark.set(200);
            ofSetColor(mark);
//            ofCircle(aggPtlPos[i], radiusAggPtl[i]);
            
//            ofDrawSphere(aggPtlPos[i], radiusAggPtl[i]);
            
//            aggPtlSphere[i].setPosition(aggPtlPos[i]);
            aggPtlSphere.setPosition(aggPtlPos[i]);
            aggPtlSphere.setRadius(radiusAggPtl[i]);
            aggPtlSphere.draw();
            
        }else{
            ofColor ptlColor2;
            ptlColor2.setHsb(ofMap(i, 0, aggPtlPos.size(), 0, 255), 180, 190);
//            ptlColor2.a = 170;
            ofSetColor(ptlColor2);
//            ofCircle(aggPtlPos[i], radiusAggPtl[i]);
            
//            ofDrawSphere(aggPtlPos[i], radiusAggPtl[i]);
            aggPtlSphere.setPosition(aggPtlPos[i]);
            aggPtlSphere.setRadius(radiusAggPtl[i]);
            aggPtlSphere.draw();
        }

    }
    lighttest1.disable();
    topCam.end();
    ofDisableLighting();
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
