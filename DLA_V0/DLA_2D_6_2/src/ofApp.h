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
    
    float winWidth,winHeight;
	//core vars
    ofVec3f corePos;
    float coreRadius;
    //floating particles vars
    vector<ofVec3f> fltPtlPos;
    vector<ofVec3f> fltPtlSpeed;
//    ofVec3f fltPtlAcceleration;
    float fltPtlRadius;//radiusPtl;

    
    //particles aggregated
    vector<ofVec3f> particlesagged; //what's vector<ofVec3f()> ?
    
    vector<float> radiusPtl;
    
};
