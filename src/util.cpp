//
//  util.cpp
//  animationMachine
//
//  Created by White, Bob on 5/28/14.
//
//

#include "util.h"

namespace util
{
    //takes an interger and outputs a string with double digits.
    string dDigiter(int i) {
        string output;
        if(i<10){
            output = "0"+ofToString(i);
        } else {
            output = ofToString(i);
        }
        return output;
    }
    
    float presetMidiNotes(float i){
        float returnedMidiNote;
        
        returnedMidiNote = 80-i;
        
        return returnedMidiNote;
    }
    
}

