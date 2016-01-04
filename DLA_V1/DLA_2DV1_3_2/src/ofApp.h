#pragma once

#include "ofMain.h"
#include "ofVec3d.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    //setting up paras;
    float winWidth,winHeight;
    ofVec3d winCen;
    //core vars
    ofVec3d corePos;
    float coreRadius;
    float maxGenRadius;
    int maxPtlNum;
//    //floating particles vars
//    ofVec3d fltPtlPos;
//    ofVec3d fltPtlSpeed;
//    float fltPtlRadius;
    //multi ptl hitting;
    int fltPtlNum;
    float degreeSeed;
    vector<ofVec3d> fltPtlPosES;
    vector<ofVec3d> fltPtlSpeedS;
    vector<float> fltPtlRadiusES;
    
    
    
    //the vector to record the particle
    vector<ofVec3d> aggPtlPos;
    vector<float> radiusAggPtl;
    
    bool keyAnimate;
    int indexHit;
    
    
    
};
