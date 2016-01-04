//
//  dlaSystem.cpp
//  DLA_V3
//
//  Created by ZhangYi on 12/11/15.


#include "dlaSystem.hpp"

//------------------------------------------------------------
void dlaSystem::setup(){
    winWidth = ofGetWidth();
    winHeight = ofGetHeight();
    winCen.set(winWidth/2, winHeight/2,0);
    winOrg.set(0, 0, 0);
    
    maxAggPtlNum = 5000;
    
    keyAnimate = true;
    
    bldrawAggPtl = true;
    fltPtlCol.set(174, 182, 190, 220);

//    runIn2d = true;
    runIn3d = true;
    dlaMesh.setMode(OF_PRIMITIVE_LINES);
    dladrawMesh = true;
}

//------------------------------------------------------------
void dlaSystem::dlaCoresetup(){
    coreNum = 12;
    minCoreRadius = 5.f;
    maxCoreRadius = 25.f;
    minCorePos = -400.f;
    maxCorePos = 400.f;
    
    for (int i = 0; i < coreNum; ++i) {
        ofVec3f tempCorePos;
        
        if (runIn2d) {
            tempCorePos.set(ofRandom(minCorePos, maxCorePos) + winCen.x, ofRandom(minCorePos, maxCorePos) + winCen.y ,0 );

        }else if(runIn3d){
            tempCorePos.set(ofRandom(minCorePos, maxCorePos) + winCen.x, ofRandom(minCorePos, maxCorePos) + winCen.y ,ofRandom(minCorePos, maxCorePos) );

        }
        
        corePos.push_back(tempCorePos);
        float tempCoreRadius = ofRandom(minCoreRadius, maxCoreRadius);
        coreRadius.push_back(tempCoreRadius);
    }
    
    enterThread = sqrt(2)*maxCorePos + 2.22 * maxfltRadius;
    
    
}

//------------------------------------------------------------
void dlaSystem::dlaaggPtlsetup(){
    for (int i = 0; i < coreNum; ++i) {
        aggPtlPos.push_back(corePos[i]);
        aggPtlRadius.push_back(coreRadius[i]);
    }
    if (dladrawMesh) {
        dlaMesh.draw();
    }
}

//------------------------------------------------------------
void dlaSystem::dlafltPtlsetup(){
    maxGenRadius = 4000.0f;
    maxfltPtlNum = 320;
    minfltSpeed = 7.0f;
    maxfltSpeed = 27.0f;
    minfltRadius = 3.0f;
    maxfltRadius = 25.0f;
    
    for (int i = 0; i < maxfltPtlNum; ++i) {
        //fltPtlPos settings
        ofVec3f tempPos;
        if (runIn2d) {
            tempPos.set(randomPtonCircle( winCen, maxGenRadius));
        }
        if (runIn3d) {
            tempPos.set(randomPtonSphere( winCen, maxGenRadius));
        }
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
    
    
}


//------------------------------------------------------------
void dlaSystem::dlaUpdate(){
    
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
                            fltPtlPos[i] = moveback(fltPtlPos[i], aggPtlPos[j], aggPtlRadius[j], fltPtlRadius[i]);
                            
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
                            fltPtlPos[i] = moveback(fltPtlPos[i], aggPtlPos[j], aggPtlRadius[j], fltPtlRadius[i]);
                            
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
        
    
    
}

//------------------------------------------------------------
void dlaSystem::dlaDrawaggPtls(){
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

//------------------------------------------------------------
void dlaSystem::dlaDrawCores(){
    for (int i = 0; i < coreNum; ++i) {
        ofCircle(corePos[i], coreRadius[i]);
    }
}

//------------------------------------------------------------
void dlaSystem::dlaDrawfltPtls(){
    ofSetColor(fltPtlCol);
    for (int j = 0; j < maxfltPtlNum; ++j) {
        ofCircle(fltPtlPos[j], fltPtlRadius[j]);
    }
}

//------------------------------------------------------------
ofVec3f dlaSystem::moveback(ofVec3f fltPos, ofVec3f aggPos,float aggRadius, float fltRadius){
    float disAct = fltPos.distance(aggPos);
    float disShould = aggRadius + fltRadius;
    ofVec3f tpmoveBack = fltPos - aggPos;
    tpmoveBack.normalize();
    tpmoveBack = tpmoveBack * (disShould - disAct);
    fltPos = fltPos + tpmoveBack;
    return fltPos;
}

//------------------------------------------------------------
void dlaSystem::fltPtlresetbyIndex(int index){
    ofVec3f tempPos;
    if (runIn2d) {
        tempPos.set(randomPtonCircle( winCen, maxGenRadius));
    }
    if (runIn3d) {
        tempPos.set(randomPtonSphere( winCen, maxGenRadius));
    }
    
    fltPtlPos[index].set(tempPos);
    
    ofVec3f tempSpeed;
    tempSpeed = winCen - tempPos;
    tempSpeed.normalize();
    tempSpeed = tempSpeed * ofRandom(minfltSpeed, maxfltSpeed);
    fltPtlSpeed[index].set(tempSpeed);
    
    float tempRadius = ofRandom(minfltRadius, maxfltRadius);
    fltPtlRadius[index] = tempRadius;
}

//------------------------------------------------------------
ofVec3f dlaSystem::randomPtonCircle(ofVec3f cen, float maxRadius){
    degreeSeed = ofRandom(0, 2 * PI);
    
    ofVec3f ptOnCircle;
    ptOnCircle.x = maxGenRadius * sin(degreeSeed) + winCen.x;
    ptOnCircle.y = maxGenRadius * sqrt(1 - u*u) * cos(degreeSeed) + winCen.y;
    ptOnCircle.z = 0;
    return ptOnCircle;
    
}

//------------------------------------------------------------
ofVec3f dlaSystem::randomPtonSphere(ofVec3f cen, float maxRadius){
    degreeSeed = ofRandom(0, 2 * PI);
    u = ofRandom(-1 ,1);
    
    ofVec3f ptOnSphere;
    ptOnSphere.x = maxGenRadius * sqrt(1 - u*u) * sin(degreeSeed) + winCen.x;
    ptOnSphere.y = maxGenRadius * sqrt(1 - u*u) * cos(degreeSeed) + winCen.y;
    ptOnSphere.z = maxGenRadius * u;
    return ptOnSphere;
    
}

//------------------------------------------------------------
void dlaSystem::dlaCreatMesh(){
    
}


