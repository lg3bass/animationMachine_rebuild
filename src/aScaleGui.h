//
//  aScaleGui.h
//  animationMachine
//
//  Created by White, Bob on 11/20/14.
//
//
#pragma once

#ifndef __animationMachine__aScaleGui__
#define __animationMachine__aScaleGui__

#include <iostream>
#include "ofMain.h"
#include "ofxUI.h"
#include "util.h"

class aScaleGui {
public:
    aScaleGui();
    
    void setup();
    void reset();
    void update();
    void draw();
    void exit();
    
    void guiEvent(ofxUIEventArgs &);
    void setGUI_Scale(int numOfLoaders);//positioning/rotate/scale
    void toggleVisibility(bool _view = true);
    void resetGUI(int numOfLoaders, int selectLdr, bool allLdrs = true);
    
    ofxUIScrollableCanvas *Scale_gui_1;
    bool guiAlloc;
    bool wModActive;
    bool doReset;
    
private:
    
};


#endif /* defined(__animationMachine__aScaleGui__) */
