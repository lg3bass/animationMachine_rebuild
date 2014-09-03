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

#endif /* defined(__animationMachine__aTrackGui__) */

class aTrackGui{
    public:
    
        static aTrackGui* Instance();//pointer to oneself.

        ofxUICanvas *TRK_gui_1;
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
    
        ofMaterial materials[10];
    
        vector<ofxUISlider *> matDiffSlider;
        vector<ofxUISlider *> matSpecSlider;
        vector<ofxUISlider *> matEmSlider;
    
    protected:
    
        aTrackGui();
    
    private:
    
        static aTrackGui* _instance;
    
    
};
