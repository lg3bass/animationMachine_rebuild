//
//  aPositionGui.h
//  animationMachine
//
//  Created by White, Bob on 11/15/14.
//
//
#pragma once

#ifndef __animationMachine__aPositionGui__
#define __animationMachine__aPositionGui__

#include <iostream>
#include "ofMain.h"
#include "ofxUI.h"
#include "util.h"

class aPositionGui {
    public:
        aPositionGui();
    
        void setup();
        void reset();
        void loadGUI(int sceneIndex);
        void saveGUI(int sceneIndex);
        void update();
        void draw();
        void exit();
    
        void guiEvent(ofxUIEventArgs &);
        void setGUI_2(int numOfLoaders);//positioning/rotate/scale
        void toggleVisibility(bool _view = true);
        void resetGUI(int numOfLoaders, int selectLdr, bool allLdrs = true);
        void setupGUI(int numOfLoaders);
    
        ofxUIScrollableCanvas *Position_gui_1;
        bool guiAlloc;
        bool wModActive;
        bool doReset;

    private:
    
};


#endif /* defined(__animationMachine__aPositionGui__) */
