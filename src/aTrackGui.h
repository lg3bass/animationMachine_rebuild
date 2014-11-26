//
//  aTrackGui.h
//  animationMachine
//
//  Created by bob white III on 11/29/13.
//
//

#pragma once

#ifndef __animationMachine__aTrackGui__
#define __animationMachine__aTrackGui__

#include <iostream>
#include "ofMain.h"
#include "ofxUI.h"


#define TRACKS 10

class aTrackGui{
    public:    
        //static aTrackGui* Instance();//pointer to oneself.
        aTrackGui();
    
        void setup();
        void reset();
        void update();
        void draw();
        void exit();

        //setting up multiple gui's.  Right now I got one.
        ofxUIScrollableCanvas *TRK_gui_1;//Materials/Shaders
        //ofxUIScrollableCanvas *TRK_gui_2;//Positioning/Rotate/Scale
        //ofxUICanvas *TRK_gui_3;
        //ofxUICanvas *TRK_gui_4;
        //ofxUICanvas *TRK_gui_5;
    
        //GUI methods
        void guiEvent_1(ofxUIEventArgs &);
        void setGUI_1();//materials
        void setWSlider(vector<ofxUISlider *>sliders, ofColor &c, float v);
        void toggleVisibility(bool _view = true);

        bool guiAlloc;
        bool wModActive;
        bool doReset;
    
        //Materials/Shaders Variables
        void resetMaterials();
        void lookForShaders();
    
        ofMaterial materials[TRACKS];
    
        vector<ofxUISlider *> matDiffSlider;
        vector<ofxUISlider *> matSpecSlider;
        vector<ofxUISlider *> matEmSlider;
    
        //shaders
        ofShader shaders[TRACKS];
        ofShader shader_0;
        ofShader shader_1;
        ofShader shader_2;
    
        bool useShaders[TRACKS] = {true}; //start off with the shaders activated.
    
        ofVec4f v4Diffuse[TRACKS] = {ofVec4f(1.0,1.0,1.0,1.0)};
        ofVec4f v4Emissive[TRACKS] = {ofVec4f(0.5,0.5,0.5,0.5)};
        ofVec4f v4Specular[TRACKS] = {ofVec4f(1.0,1.0,1.0,1.0)};
    
        void cycleShaders();
        void materialStats();
        void shaderStats();

    
        //additional shaders
        ofImage img;
    
    
    
    protected:
    
        //aTrackGui();
    
    private:
    
        //may need to move this to public
        struct extShader {
            ofFile vert;
            ofFile frag;
            ofFile geo;
            ofFile img;
            string path;
            string name;
        };
    
        vector<extShader> externalShaders;
        //static aTrackGui* _instance;
    
    
};

#endif /* defined(__animationMachine__aTrackGui__) */
