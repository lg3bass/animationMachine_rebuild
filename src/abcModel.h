//
//  abcModel.h
//  lights_camera_alembic
//
//  Created by bob white III on 8/11/13.
//
//

#ifndef __animationMachine__abcModel__
#define __animationMachine__abcModel__


#include <iostream>
#include "ofMain.h"
#include "ofxAlembic.h"
#include "aGui.h"


class abcModel : public ofNode {
 
    ofVboMesh vbo_mesh;    
    ofxAlembic::Reader aReader;
    
public:

    aGui * myGuiRef;// not used I think???
    
    abcModel(int _id);
    
    void init(std::string file, float divisions, ofxAlembic::Reader r);
    
    void load();
    void calcTime(float t);
    void update();
    void customDraw();
    //void draw();
    void report();
    void launch();// dont think this is needed anymore.
    bool holdAnimation();
    bool finalizeAnimation();
    void setABCPosition();
    void setABCOrientation();
    void setABCScale();
    void setABCRotate();
    void setABCMove();
    void setClipMarkers(int _currentSegment);
    void playSegment(int type);
    void INFOlaunchingToPlay();
    
    int this_id;  // dont think this is public.
    
    //public
    float abcDurration;
    float segments;
    float clipSpeedMod;
    float midiChannel;
    float midiNote;
    int ldrType; // 0=random, 1=linear
    int trackMode; // 0=noteOn, 1=noteOff, 2=noteOn/noteOff
    
    
    float segLength;
    int currentSegment;
    string abcName;
    
    float half_unit;
    float full_unit;
        
    float clipTime;//where are you in the animation
    float midTime;//where the clip holds on noteOn
    float endTime;//in segment mode. where to stop.
    
    bool isDemo; //controlled by the play button.
    bool isAnimating;//is the model animating
    bool isHolding;//is the model holding with a noteOn/noteOff
    bool isFinishing;//
    bool isActive;//anything in here or an empty clip.
    
    bool stageHold;
    bool stageEnd;//are we finalizing the animation run
    
    ofVec3f abcPostion; //global position in WS.
    ofVec3f abcOrientation;
    ofVec3f abcScale = ofVec3f(25, 25, 25);
};




#endif /* defined(__animationMachine__abcModel__) */
