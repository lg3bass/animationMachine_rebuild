//
//  aTrackGui.h
//  animationMachine
//
//  Created by bob white III on 11/29/13.
//
//

#ifndef __animationMachine__aTrackGui__
#define __animationMachine__aTrackGui__

#include <iostream>
#include "ofMain.h"
#include "ofxUI.h"

#define TRACKS 10

#endif /* defined(__animationMachine__aTrackGui__) */

class aTrackGui{
    public:    
        static aTrackGui* Instance();//pointer to oneself.

        //setting up multiple gui's.  Right now I got one.
        ofxUIScrollableCanvas *TRK_gui_1;
        ofxUICanvas *TRK_gui_2;
        ofxUICanvas *TRK_gui_3;
        ofxUICanvas *TRK_gui_4;
        ofxUICanvas *TRK_gui_5;
    
        void setup();
        void reset();
        void update();
        void draw();
        void exit();
    
        //GUI methods
        void guiEvent(ofxUIEventArgs &);
        void setGUI();//sets gui and gui2
        void setWSlider(vector<ofxUISlider *>sliders, ofColor &c, float v);
        void toggleVisibility(bool _view = true);

        bool guiAlloc;
        bool wModActive;
        bool doReset;
    
        //materials
        void resetMaterials();
    
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
    
        void materialStats();
        void shaderStats();

    
    
    protected:
    
        aTrackGui();
    
    private:
    
        static aTrackGui* _instance;
    
    
};
