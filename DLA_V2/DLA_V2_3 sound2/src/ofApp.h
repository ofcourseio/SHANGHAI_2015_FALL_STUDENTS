#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void fltPtlresetbyIndex(int i);
//        void soundsetup();
        void soundPlay(int i);
    
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
    ofVec3f winCen;
    //multi core vars
    int coreNum;
    float minCoreRadius,maxCoreRadius;
    float minCorePos,maxCorePos;
    vector<ofVec3f> corePos;
    vector<float> coreRadius;
    
    //floating particles setting
    float  maxGenRadius;
    int maxfltPtlNum;
    float degreeSeed;
    float minfltSpeed,maxfltSpeed;
    float minfltRadius,maxfltRadius;
    vector<ofVec3f> fltPtlPos;
    vector<ofVec3f> fltPtlSpeed;
    vector<ofVec3f> fltPtlAcc;
    vector<float> fltPtlRadius;
    
    ofColor fltPtlCol;
    
    
    //aggregated particles
    vector<ofVec3f> aggPtlPos;
    vector<float> aggPtlRadius;
    vector<float> aggPtlGap;
    
    int maxAggPtlNum;
    
    //view setting,interactive setting
    
    bool keyAnimate;
    bool keyStartUpdate;
    bool autoZoom;
    bool addMaxAggPtlNum;
    int indexHit;
    
    ofEasyCam topCam;
    float camDist;
    //sound setting
    vector<ofSoundPlayer> pnoSound;
    int soundNum;
    float soundIndex;
    ofSoundPlayer mySound;
};
