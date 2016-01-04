//
//  vectorField.cpp
//  DLA_V3
//
//  Created by ZhangYi on 12/12/15.
//
//

#include "vectorField.hpp"
#include "ofMain.h"
vectorField::vectorField(){
    
    /*fieldWidth  = 60;
     fieldHeight = 40;
     */
}


//------------------------------------------------------------------------------------
void vectorField::setupField(int innerW, int innerH, int outerW, int outerH){
    
    fieldWidth        =innerW;
    fieldHeight       =innerH;
    externalWidth     =outerW;
    externalHeight    =outerH;
    
    field.clear();
    
    fieldSize = fieldWidth * fieldHeight;
    for (int i = 0; i < fieldSize; ++i) {
        ofVec2f pt;
        pt.set(0,0);
        field.push_back(pt);
    }
}

//------------------------------------------------------------------------------------
void vectorField::clear(){
    for (int i = 0; i < fieldSize; ++i) {
        field[i].set(0, 0);
    }
}

//------------------------------------------------------------------------------------
void vectorField::fadeField(float fadeAmount){
    for (int i = 0; i < fieldSize; ++i) {
        field[i].set(field[i].x * fadeAmount, field[i].y * fadeAmount);
    }
}

//------------------------------------------------------------------------------------
void vectorField::randomizeField(float scale){
    for (int i = 0; i < fieldSize; ++i) {
        float x = (float)(ofRandom(-1,1)) * scale;
        float y = (float)(ofRandom(-1,1)) * scale;
        field[i].set(x,y);
    }
}

//------------------------------------------------------------------------------------
void vectorField::draw(){
    float scalex = (float)externalHeight / (float)fieldWidth;
    float scaley = (float)externalHeight / (float)fieldHeight;
    
    for (int i = 0; i < fieldWidth; i++) {
        for (int j = 0; j < fieldHeight; j++) {
            
            int pos = j * fieldWidth +i;
            
            float px = i * scalex;
            float py = j * scaley;
            float px2 = px + field[pos].x * 5;
            float py2 = px + field[pos].y * 5;
            
            ofLine(px, py, px2, py2);
            
            ofVec2f line;
            line.set(px2-px, py2-py);
            float length = line.length();
            line.normalize();
            line.rotate(90);
            ofLine(px - line.x * length * 0.2, py - line.y * length * 0.2, px + line.x*length*0.2, py + line.y*length*0.);
            
        }
    }
}

//------------------------------------------------------------------------------------
ofVec2f vectorField::getForceFromPos(float xpos, float ypos){
    
    ofVec2f frc;
    frc.set(0, 0);
    
    float xPct = xpos / (float)externalWidth;
    float yPct = ypos / (float)externalHeight;
    
    if ((xPct < 0 || xPct > 1) || (yPct < 0 || yPct > 1) ) {
        return frc;
    }
    
    int fieldPosX = (int)(xPct * fieldWidth);
    int fieldPosY = (int)(yPct * fieldHeight);
    //safety
    fieldPosX = MAX(0, MIN(fieldPosX, fieldWidth - 1));
    fieldPosY = MAX(0, MIN(fieldPosY, fieldHeight - 1));
    //pos in array
    int pos = fieldPosY * fieldWidth + fieldPosX;
    
    frc.set(field[pos].x * 0.1, field[pos].y * 0.1 );
    return frc;
}

//------------------------------------------------------------------------------------
void vectorField::addInWardCircle(float x, float y, float radius, float strength){
    
    float pctx     = x / (float)externalWidth;
    float pcty     = y / (float)externalHeight;
    float radiusPct = radius / (float)externalWidth;
    
    int fieldPosX    = (int)(pctx * (float)fieldWidth);
    int fieldPosY    = (int)(pcty * (float)fieldHeight);
    float fieldRadius = (float)(radiusPct * fieldWidth);
    
    int startx = MAX(fieldPosX - fieldRadius, 0);
    int starty = MAX(fieldPosY - fieldRadius, 0);
    int endx = MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy = MIN(fieldPosY + fieldRadius, fieldHeight);
    
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
            if (distance < 0.0001) distance = 0.0001;  // since we divide by distance, do some checking here, devide by 0 is BADDDD
            
            if (distance < fieldRadius){
                
                float pct = 1.0f - (distance / fieldRadius);
                
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x += unit_px * strongness;
                field[pos].y += unit_py * strongness;
            }
        }
    }
}

//------------------------------------------------------------------------------------
void vectorField::addOutWardCircle(float x, float y, float radius, float strength){
    
    float pctx       = x / (float)externalWidth;
    float pcty       = y / (float)externalHeight;
    float radiusPct  = radius / (float)externalWidth;
    
    int fieldPosX    = (int)(pctx * (float)fieldWidth);
    int fieldPosY    = (int)(pcty * (float)fieldHeight);
    float fieldRadius = (float)(radiusPct * fieldWidth);
    
    
    int startx	= MAX(fieldPosX - fieldRadius, 0);
    int starty	= MAX(fieldPosY - fieldRadius, 0);
    int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
    
    for (int i = startx; i < endx; i++) {
        for (int j = starty; j < endy; j++) {
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX - i)* (fieldPosX -i) + (fieldPosY - j) * (fieldPosY - j));
            
            if (distance < 0.0001) distance = 0.0001;
            
            if (distance < fieldRadius) {
                
                float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_px * strongness;
                field[pos].y -= unit_py * strongness;
            }
            
        }
    }
}


//------------------------------------------------------------------------------------
void vectorField::addClockwiseCircle(float x, float y, float radius, float strength){
    
    float pctx       = x / (float)externalWidth;
    float pcty       = y / (float)externalHeight;
    float radiusPct  = radius / (float)externalWidth;
    
    int fieldPosX    = (int)(pctx * (float)fieldWidth);
    int fieldPosY    = (int)(pcty * (float)fieldHeight);
    float fieldRadius = (float)(radiusPct * fieldWidth);
    
    int startx	= MAX(fieldPosX - fieldRadius, 0);
    int starty	= MAX(fieldPosY - fieldRadius, 0);
    int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
    
    for (int i = startx; i < endx; i++) {
        for (int j = starty; j < endy; j++) {
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX - i)* (fieldPosX -i) + (fieldPosY - j) * (fieldPosY - j));
            
            if (distance < 0.0001) distance = 0.0001;
            
            if (distance < fieldRadius) {
                
                float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_py * strongness;
                field[pos].y -= unit_px * strongness;
            }
        }
    }
}

//------------------------------------------------------------------------------------
void vectorField::addCounterClockwiseCircle(float x, float y, float radius, float strength){
    float pctx       = x / (float)externalWidth;
    float pcty       = y / (float)externalHeight;
    float radiusPct  = radius / (float)externalWidth;
    
    int fieldPosX    = (int)(pctx * (float)fieldWidth);
    int fieldPosY    = (int)(pcty * (float)fieldHeight);
    float fieldRadius = (float)(radiusPct * fieldWidth);
    
    int startx	= MAX(fieldPosX - fieldRadius, 0);
    int starty	= MAX(fieldPosY - fieldRadius, 0);
    int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
    
    for (int i = startx; i < endx; i++) {
        for (int j = starty; j < endy; j++) {
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX - i)* (fieldPosX -i) + (fieldPosY - j) * (fieldPosY - j));
            
            if (distance < 0.0001) distance = 0.0001;
            
            if (distance < fieldRadius) {
                
                float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_py * strongness;
                field[pos].y -= unit_px * strongness;
            }
        }
    }
}

//------------------------------------------------------------------------------------
void vectorField::addVectorCircle(float x, float y, float vx, float vy, float radius, float strength){
    float pctx       = x / (float)externalWidth;
    float pcty       = y / (float)externalHeight;
    float radiusPct  = radius / (float)externalWidth;
    
    int fieldPosX    = (int)(pctx * (float)fieldWidth);
    int fieldPosY    = (int)(pcty * (float)fieldHeight);
    float fieldRadius = (float)(radiusPct * fieldWidth);
    
    int startx	= MAX(fieldPosX - fieldRadius, 0);
    int starty	= MAX(fieldPosY - fieldRadius, 0);
    int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
    
    for (int i = startx; i < endx; i++) {
        for (int j = starty; j < endy; j++) {
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX - i)* (fieldPosX -i) + (fieldPosY - j) * (fieldPosY - j));
            
            if (distance < 0.0001) distance = 0.0001;
            
            if (distance < fieldRadius) {
                
                float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                field[pos].x -= vx * strongness;
                field[pos].y -= vy* strongness;
            }
        }
    }
    
}

//------------------------------------------------------------------------------------
vectorField::~vectorField(){
    
}

