#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void fltPtlresetbyIndex(int i);
    
        ofVec3f moveback(ofVec3f a,ofVec3f b ,float ar, float br);
    
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
    float u;
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
    float enterThread;
    int cutIndex;
    float cutNumEst;
    //view setting,interactive setting
    
    bool keyAnimate;
    bool keyStartUpdate;
    bool autoZoom;
    bool addMaxAggPtlNum;
    bool drawAggPtl;
    int indexHit;
    
    ofEasyCam topCam;
    float camDist;
    
    ofShader shader1;
    ofShader shader2;
    
    ofMesh dlaMesh;
    
    
    
};
