//
//  aLights.h
//  lights_camera_alembic
//
//  Created by bob white III on 8/17/13.
//
//

#ifndef __animationMachine__aLights__
#define __animationMachine__aLights__

#include <iostream>
#include "ofMain.h"

class aLights {
    
public:
    static aLights* Instance();
    
    //methods
    void reset();
    void update();
    void setLightOri(ofLight &light, ofVec3f rot);
 
    //variables
    ofEasyCam cam;
    ofLight spot;
    ofLight point;
    ofLight dir;
    ofLight amb;

    
    ofVec3f dir_rot;
    ofVec3f spot_rot;

protected:
    aLights();
    
private:
    static aLights* _instance;
    
    
};

#endif /* defined(__animationMachine__aLights__) */
