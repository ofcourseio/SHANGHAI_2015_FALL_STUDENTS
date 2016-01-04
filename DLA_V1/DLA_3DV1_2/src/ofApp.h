#pragma once

#include "ofMain.h"

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
    ofVec3f winCen;
    //core vars
    ofVec3f corePos;
    float coreRadius;
    float maxGenRadius;
    int maxPtlNum;
    //setting floating particle;
    int fltPtlNum;
//    float degreeSeed;
//    float degreeSeedPhi;
//    float seedX,seedY,seedZ;
    float theta,u,pX,pY,pZ;
    vector<ofVec3f> fltPtlPosES;
    vector<ofVec3f> fltPtlSpeedS;
    vector<float> fltPtlRadiusES;
    
    
    
    //the vector to record the particle
    vector<ofVec3f> aggPtlPos;
    vector<float> radiusAggPtl;
    bool aggPtlNumFlag;
    int aggPtlNum;
    
    bool keyAnimate;
    int indexHit;
    ofVboMesh totalMesh;
    
    
    ofEasyCam topCam;
//    vector<ofSpherePrimitive> aggPtlSphere;
    ofSpherePrimitive aggPtlSphere;
    ofLight lighttest1;
    
};
