//
//  dlaSystem.hpp
//  DLA_V3
//
//  Created by ZhangYi on 12/11/15.
//
//

#ifndef dlaSystem_hpp
#define dlaSystem_hpp

#include <stdio.h>
#include "ofMain.h"

class dlaSystem
{
    public:
    void setup();
    void dlaCoresetup();
    void dlaUpdate();
    void dlafltPtlsetup();
    void dlaaggPtlsetup();
    
    void dlaDrawCores();
    void dlaDrawfltPtls();
    void dlaDrawaggPtls();
    void dlaDrawMesh();
    void dlaReset();
    void deformDLA();
    
    ofVec3f moveback(ofVec3f fltPos, ofVec3f aggPos,float aggRadius, float fltRadius);
    void fltPtlresetbyIndex(int index);
    ofVec3f randomPtonSphere(ofVec3f cen, float maxRadius);
    ofVec3f randomPtonCircle(ofVec3f cen, float maxRadius);
    
    
    //basic settings;
    float winWidth,winHeight;
    ofVec3f winCen,winOrg;
    int maxAggPtlNum;
    
    //basic core paras;
    int coreNum;
    float minCoreRadius,maxCoreRadius;
    float minCorePos,maxCorePos;
    vector<ofVec3f> corePos;
    vector<float> coreRadius;
    
    //basic fltPtl paras
    float maxGenRadius;
    int maxfltPtlNum;
    float minfltSpeed,maxfltSpeed;
    float minfltRadius,maxfltRadius;
    
    float degreeSeed,u;
    
    //
    vector<ofVec3f> fltPtlPos;
    vector<ofVec3f> fltPtlSpeed;
    vector<ofVec3f> fltPtlAcc;
    vector<float> fltPtlRadius;
    
    ofColor fltPtlCol;
    
    
    //aggregated particles
    vector<ofVec3f> aggPtlPos;
    vector<float> aggPtlRadius;
    vector<float> aggPtlGap;
    //
    
    ofMesh dlaMesh;
    ofMesh dfMesh;
    
    
    float enterThread;
    int cutIndex;
    float cutNumEst;
    
    int indexHit;
    bool bldrawAggPtl;
    bool bldrawFltPtl;
    bool keyAnimate;
    bool runIn2d;
    bool runIn3d;
    bool addMaxAggPtlNum;
    bool bldrawMesh;
    
    bool blDeform2dDLA;
    
    
};




#endif /* dlaSystem_hpp */
