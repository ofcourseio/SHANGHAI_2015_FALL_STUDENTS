#include "ofApp.h"
//DLA 3D V2.0.1
//multi core multi fltPtl
//next versiion gui;
//add aggregate gap;
//framerate optimized
//add shader test
//add moveback function
//--------------------------------------------------------------
void ofApp::setup(){
    

    //set 3d core

    
    //initialize aggPtls

    
    
    //setting inital floating particle list


    
    fltPtlCol.set(74, 82, 160, 220);
    
    
//    topCam.setDistance(500+0.5*abs(maxCorePos - minCorePos));

//    topCam.setFarClip(10000);
   
    
    
    
    
    
    
    
}
//--------------------------------------------------------------




//--------------------------------------------------------------
void ofApp::update(){

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


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
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
