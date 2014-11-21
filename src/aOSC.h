//
//  aOSC.h
//  animationMachine
//
//  Created by White, Bob on 11/20/14.
//
//
#pragma once

#ifndef __animationMachine__aOSC__
#define __animationMachine__aOSC__

#include <iostream>
#include "ofMain.h"
#include "ofxOsc.h"
#include "util.h"

#define PORT 12345

class aOSC {

public:
    aOSC();
    
    void setup();
    void reset();
    void update();
    void draw();
    void exit();

    ofxOscReceiver receiver;
    void newOscMessage();
    
    //material OSC vars.
    ofColor diffuse_c;
    ofColor emissive_c;
    ofColor specular_c;
private:
    
    
};

#endif /* defined(__animationMachine__aOSC__) */
