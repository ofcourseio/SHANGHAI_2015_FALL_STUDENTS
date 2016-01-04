#include "ofApp.h"
//DLA 2D V2.0.7
//multi core multi fltPtl
//next versiion gui;
//add aggregate gap;
//backward loop bug occurs;
//sound deleted
//framerate optimized
//add shader test
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2, winHeight/2,0);
    //CORES SETTINGS
    coreNum = 12;
    minCoreRadius = 5.f;
    maxCoreRadius = 25.f;
    minCorePos = -400.f;
    maxCorePos = 400.f;
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
    maxGenRadius = 5000.0f;
    maxfltPtlNum = 140;
    minfltSpeed = 7.0f;
    maxfltSpeed = 27.0f;
    minfltRadius = 3.0f;
    maxfltRadius = 25.0f;
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
    
    maxAggPtlNum = 3000;
    keyAnimate = true;
//    topCam.setDistance(500+0.5*abs(maxCorePos - minCorePos));
    topCam.setDistance(500);
    topCam.setFarClip(15000);
//    topCam.setFarClip(10000);
    autoZoom = true;
    
    enterThread = sqrt(2)*maxCorePos + 2.22 * maxfltRadius;
    dlaMesh.setMode(OF_PRIMITIVE_LINES);
//    shader1.load("shader");
//    shader2.load("shader2");
    drawAggPtl = true;
    
    drawthread =false;
    
}
//--------------------------------------------------------------





//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + " fps");

    if ( keyAnimate ) {
        for (int i = 0 ; i < maxfltPtlNum; ++i) {
            fltPtlPos[i] = fltPtlPos[i] + fltPtlSpeed[i];
            if (fltPtlPos[i].distance(winCen) < enterThread) {
                //startsearch Index to cut the unnecessary compare;
                cutNumEst = 0.23 * 4 * pow(enterThread/(maxfltRadius + minfltRadius), 2); //the estimated number to cut;
                
                if (aggPtlPos.size() > (int)cutNumEst) {
                    cutIndex = int(0.55 * cutNumEst);
                    for (int j = cutIndex; j < aggPtlPos.size() ; ++j) {
                        
                        float distCompare =aggPtlRadius[j] + fltPtlRadius[i];
                        
                        if (fltPtlPos[i].distance(aggPtlPos[j]) < distCompare) {
                            indexHit = i;
                            //move floating particle back to avoid overlapping/ control overlaping gap
                            float disAct = fltPtlPos[i].distance(aggPtlPos[j]);
                            float disShould = aggPtlRadius[j] + fltPtlRadius[i];
                            ofVec3f moveBack = fltPtlPos[i] - aggPtlPos[j];
                            moveBack.normalize();
                            moveBack = moveBack * (disShould - disAct);
                            fltPtlPos[i] = fltPtlPos[i] + moveBack;
                            ofFloatColor tempMeshCol;
                            
                            tempMeshCol.setHsb(ofMap(j, 0, maxAggPtlNum, 0.0f, 1.f) , 0.8, 0.95);
                            
                            dlaMesh.addVertex(aggPtlPos[j]);
                            dlaMesh.addColor(tempMeshCol);
                            dlaMesh.addVertex(fltPtlPos[i]);
                            dlaMesh.addColor(tempMeshCol);
                            
                            float fixedDis = fltPtlPos[i].distance(winCen);
                            if (fixedDis > enterThread) {
                                enterThread = 2.2 * maxfltRadius + fixedDis;
                            }
                            
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
                }else{
                    for (int j = 0; j < aggPtlPos.size() ; ++j) {
                        
                        float distCompare =aggPtlRadius[j] + fltPtlRadius[i];
                        
                        if (fltPtlPos[i].distance(aggPtlPos[j]) < distCompare) {
                            indexHit = i;
                            //move floating particle back to avoid overlapping/ control overlaping gap
                            float disAct = fltPtlPos[i].distance(aggPtlPos[j]);
                            float disShould = aggPtlRadius[j] + fltPtlRadius[i];
                            ofVec3f moveBack = fltPtlPos[i] - aggPtlPos[j];
                            moveBack.normalize();
                            moveBack = moveBack * (disShould - disAct);
                            fltPtlPos[i] = fltPtlPos[i] + moveBack;
                            
                            ofFloatColor tempMeshCol;
                            
                            tempMeshCol.setHsb(ofMap(j, 0, maxAggPtlNum, 0.0f, 1.f) , 0.8, 0.95);
                            
                            dlaMesh.addVertex(aggPtlPos[j]);
                            dlaMesh.addColor(tempMeshCol);
                            dlaMesh.addVertex(fltPtlPos[i]);
                            dlaMesh.addColor(tempMeshCol);
                            
                            float fixedDis = fltPtlPos[i].distance(winCen);
                            if (fixedDis > enterThread) {
                                enterThread = 2.2 * maxfltRadius + fixedDis;
                            }
                            
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
            
        }
    }
    
    if (autoZoom) {
        camDist = ofMap(aggPtlPos.size(), 500, 1000+1.5*aggPtlPos.size(), 500, 2000);
        topCam.setDistance(camDist);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofCircle(corePos[0],25);
    ofDrawBitmapString("aggPtlNum:" + ofToString(aggPtlPos.size()), 10,20);
    ofDrawBitmapString("press 'z' to  toggle auto zoom: " + ofToString( autoZoom ), 10,30);
    ofDrawBitmapString("cutNumEst:" + ofToString(cutNumEst), 10,40);
    ofDrawBitmapString("cutIndex:" + ofToString(cutIndex), 10,50);
    ofDrawBitmapString("timeElapsed:" + ofToString(ofGetElapsedTimef()), 10,60);
    
    topCam.begin();
    ofTranslate(-winCen.x, -winCen.y, 0);
    ofSetColor(255, 255, 255);
    if (drawthread) {
        ofNoFill();
        ofCircle(winCen, enterThread);
    }

    ofFill();
    ofSetColor(fltPtlCol);
    for (int j = 0; j < maxfltPtlNum; ++j) {
        ofCircle(fltPtlPos[j], fltPtlRadius[j]);
    }
    
    
//    shader1.begin();

    
//    shader2.begin();
//        shader1.setUniform1f("width", ofGetWidth());
//        shader1.setUniform1f("height", ofGetHeight());
//        shader1.setUniform1f("time", ofGetElapsedTimef());
//        shader1.setUniform2f("mouse", mouseX,ofGetHeight() - mouseY);
//        shader1.setUniform1f("alpha", 0.45 * sin(0.02 + PI + ofGetElapsedTimef()) + 0.55);
//    shader2.setUniform1f("width", ofGetWidth());
//    shader2.setUniform1f("height", ofGetHeight());
//    shader2.setUniform1f("time", ofGetElapsedTimef());
//    shader2.setUniform2f("mouse", mouseX,ofGetHeight() - mouseY);
//    shader2.setUniform1f("alpha", 0.5 * sin(ofGetElapsedTimef()) + 0.5);
    if (drawAggPtl) {
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
    }
    
    
    dlaMesh.draw();
    
    
//    shader1.end();

//    shader2.end();
    
    
    
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
    if (key == 'a') {
        maxAggPtlNum += maxAggPtlNum;
        keyAnimate = true;
    }
    if (key == 'd') {
        drawAggPtl = !drawAggPtl;
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
