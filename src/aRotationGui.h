//
//  aRotationGui.h
//  animationMachine
//
//  Created by White, Bob on 11/19/14.
//
//
#pragma once

#ifndef __animationMachine__aRotationGui__
#define __animationMachine__aRotationGui__

#include <iostream>
#include "ofMain.h"
#include "ofxUI.h"
#include "util.h"

class aRotationGui {
    public:
        aRotationGui();
        
        void setup();
        void reset();
        void loadGUI(int sceneIndex);
        void saveGUI(int sceneIndex);
        void update();
        void draw();
        void exit();
        
        void guiEvent(ofxUIEventArgs &);
        void setGUI_Rot(int numOfLoaders);//positioning/rotate/scale
        void toggleVisibility(bool _view = true);
        void resetGUI(int numOfLoaders, int selectLdr, bool allLdrs = true);
        
        ofxUIScrollableCanvas *Rotation_gui_1;
        bool guiAlloc;
        bool wModActive;
        bool doReset;
        
    private:
    
};



#endif /* defined(__animationMachine__aRotationGui__) */
