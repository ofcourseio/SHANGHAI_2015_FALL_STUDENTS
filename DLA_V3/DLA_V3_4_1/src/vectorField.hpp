//
//  vectorField.hpp
//  DLA_V3
//
//  Created by ZhangYi on 12/12/15.
//
//

#ifndef vectorField_hpp
#define vectorField_hpp

#include <stdio.h>
#include "ofMain.h"

class vectorField{
    public:
    
        int fieldWidth;
        int fieldHeight;
        int fieldSize;
        
        int externalWidth,externalHeight;
        
        vector<ofVec2f> field;
        
        vectorField();
        virtual ~vectorField();
    
        void setupField( int innerW, int innerH, int outerW, int outerH);
        
        void clear();
        void fadeField(float fadeAnount);
        void randomizeField(float scale);
        void draw();
        
        ofVec2f getForceFromPos(float xpos,float ypos);
        
        void addOutWardCircle( float x, float y,float radius, float strength );
        void addInWardCircle( float x, float y, float radius, float strength );
        void addClockwiseCircle(float x, float y, float radius, float strength);
        void addCounterClockwiseCircle(float x, float y, float radius, float strength);
        void addVectorCircle(float x, float y, float vx, float vy, float radius, float strength);
    
    
    protected:
        
    private:
    
    
    
};




#endif /* vectorField_hpp */
