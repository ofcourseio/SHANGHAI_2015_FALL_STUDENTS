//
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(100);
    ofEnableDepthTest();
    dla.setup();
    cout << "bl: " << dla.bldrawAggPtl << endl;
    
    dla.dlaCoresetup();
    dla.dlaaggPtlsetup();
    dla.dlafltPtlsetup();
    
    autoZoom = true;
    bDrawInfo = true;
    showthread = true;
    topCam.setDistance(500);
    topCam.setFarClip(15000);
    
    shader.load("morph");
    divWidth= divHeight = 200;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + " fps");
    if (ofGetFrameNum() % 60 == 0) shader.load("morph");
    
    dla.dlaUpdate();

    if (autoZoom) {
        camDist = ofMap(500 - dla.coreNum + dla.aggPtlPos.size(), 500, 1000+1.5*dla.aggPtlPos.size(), dla.enterThread + 400, dla.enterThread +2800);
//        camDist = ofMap(500 + ofGetElapsedTimef(), 500, 1500, 500, 2000);
        topCam.setDistance(camDist);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    drawInfo();
    
    topCam.begin();

    ofTranslate(-dla.winCen.x, -dla.winCen.y, 0);
    if (showthread) {
        ofSetColor(255, 255, 255);
        ofNoFill();
        ofCircle(dla.winCen, dla.enterThread);
    }
    //debug enterThread

    
    ofFill();
    //
    if (dla.bldrawFltPtl) {
        dla.dlaDrawfltPtls();
    }

    if (dla.bldrawAggPtl) {
        dla.dlaDrawaggPtls();
    }
    
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("scale", 100.0);
    shader.setUniform1f("width", divWidth);
    shader.setUniform1f("height", divHeight);
//    dlaMesh.draw();
    if (dla.bldrawMesh) {
        dla.dlaDrawMesh();
    }
    shader.end();
    topCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        dla.keyAnimate = !dla.keyAnimate;
    }
    if (key == 'z') {
        autoZoom = !autoZoom;
    }
    if (key == 'a') {
        dla.maxAggPtlNum += dla.maxAggPtlNum;
        dla.keyAnimate = true;
    }
    if (key == 'd') {
        dla.bldrawAggPtl = !dla.bldrawAggPtl;
    }
    if (key == '2') {
        dla.runIn2d = true;
        dla.runIn3d = false;
    }
    if (key == '3') {
        dla.runIn2d = false;
        dla.runIn3d = true;
    }
    if (key == 'f') {
        dla.blDeform2dDLA = !dla.blDeform2dDLA;
    }
    if (key == 'r') {
        dla.dlaReset();
    }
    if (key == 'i') {
        bDrawInfo = !bDrawInfo;
    }
    if (key == 'p') {
        dla.bldrawFltPtl = !dla.bldrawFltPtl;
    }
    if (key == 't') {
        showthread = !showthread;
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

//--------------------------------------------------------------
void ofApp::drawInfo(){
    if (bDrawInfo) {
        ofSetColor(140, 190, 240);
        ofDrawBitmapString("aggPtlNum:" + ofToString(dla.aggPtlPos.size()) + " fltPtlNum: " + ofToString(dla.maxfltPtlNum), 10,20);
        ofDrawBitmapString("press 'z' to  toggle auto zoom: " + ofToString( autoZoom ), 10,32);
        ofDrawBitmapString("cutNumEst:" + ofToString(dla.cutNumEst) + " cutIndex:" + ofToString(dla.cutIndex), 10,44);
        ofDrawBitmapString("timeElapsed:" + ofToString(ofGetElapsedTimef()), 10,56);
        ofDrawBitmapString("press f to toggle deform  Toggel:" + ofToString(dla.blDeform2dDLA), 10,68);
        ofDrawBitmapString("press 2 and 3 to swith 2d and 3d mode: 2D: " + ofToString(dla.runIn2d) + " 3D: " + ofToString(dla.runIn3d) , 10,80);
        ofDrawBitmapString("press r to reset the program" , 10,92);
        ofDrawBitmapString("press i to show/hide info", 10,104);
        ofDrawBitmapString("press p to toggle fltPtl drawing", 10,116);
    }


}
