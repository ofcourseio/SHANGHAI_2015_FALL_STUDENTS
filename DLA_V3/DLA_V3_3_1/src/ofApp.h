#pragma once

#include "ofMain.h"
#include "dlaSystem.hpp"
#include "vectorField.hpp"

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
        void drawInfo();
    
    dlaSystem dla;
    vectorField VF;
    
    ofEasyCam topCam;
    float camDist;
    bool autoZoom;
    bool bDrawInfo;
    ofShader shader;
};
