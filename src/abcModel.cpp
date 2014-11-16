//
//  abcModel.cpp
//  lights_camera_alembic
//
//  Created by bob white III on 8/11/13.
//
//

#include "abcModel.h"
#include "ofxAlembic.h"



//New abcModel(file,divisions,
//--------------------------------------------------------------
abcModel::abcModel(int _id){
    this_id = _id;
    
    /*
        
    aReader = r;  //Question: do I need to dispose of this object?        
    string path = file;    
    
    if(path == "empty"){
        isActive = false;
    } else {
        isActive = true;
        //open the file if active
        aReader.open(path);
    }
     // show all drawable names
	r.dumpNames();
    
    //params
    //how many segments
    segments = divisions;
    
    */ 
     
    //DEFAULTS
    
    //params
    //how many segments
    segments = 0;
    //track speed
    clipSpeedMod = 0.07;
    //what midi channel/track
    midiChannel = 0;
    //what specific note
    midiNote = 0;
    //track type(0:random,1:linear)
    ldrType = 0;
    //track mode(0:note On,1:note Off, 2:note On and Off)
    trackMode = 0;
    //how big are the segments
    segLength = 0;
    //which segment is currently playing.
    currentSegment = 0;
    
    isDemo = false;
    isAnimating = false;
    isHolding = false;
    isFinishing = false;
    
    full_unit = 1.0;
    half_unit = 0.5;
    
    abcPostion = ofVec3f(0, 0, 0);
    
    vbo_mesh.setMode(OF_PRIMITIVE_TRIANGLES);

}

void abcModel::init(std::string file, float divisions, ofxAlembic::Reader r) {

    //this_id = _id;
    aReader = r;  //Question: do I need to dispose of this object?
    string path = file;
    
    if(path == "empty"){
        isActive = false;
    } else {
        isActive = true;
        //open the file if active
        aReader.open(path);
        abcDurration = aReader.getMaxTime();
    }
    
    abcName = path;
    
    // show all drawable names
	r.dumpNames();
    
    //params
    //how many segments
    segments = divisions;
    
}


void abcModel::load() {
    //ofxUINumberDialer *trackDialer = (ofxUINumberDialer *)myGuiRef->gui_loader->getWidget(util::dDigiter(this_id)+"_TRK_SPEED");
    //clipSpeedMod = trackDialer->getValue();
}


// ???? Dont think this is needed anymore. 
void abcModel::launch() {
    clipTime = 0.0;
    isHolding = false;
    stageHold = false;
    stageEnd = false;
}


//-----------------------------------------------------
void abcModel::playSegment(int _type){
    if(currentSegment == segments-1){
        currentSegment = 0;
    } else {
        if(_type == 0){//if random
            currentSegment = floor(ofRandom(0, segments));
        } else {//if linear
            currentSegment++;
        }
    }
       //set the markers
    setClipMarkers(currentSegment);
    
   //set the flags.
    isFinishing = false;
    isAnimating = true;
    if(trackMode == 1){
        isHolding = true;//note Off only
    } else {
        isHolding = false;
    }
    
    
    
    //finally output what is slated to play. Uncomment to see what is playing
    INFOlaunchingToPlay();
}

//-----------------------------------------------------

//TO-DO:  You need to calculate markers for aReader.getMaxTime() somehow. That way you can simplify the calcTime procedure.
void abcModel::setClipMarkers(int _currentSegment){
    
    full_unit = (segLength/30)/segments;
    half_unit = full_unit/2;
    
    clipTime = _currentSegment*full_unit;
    midTime = clipTime+half_unit;
    endTime = clipTime+full_unit;
}



//-----------------------------------------------------
void abcModel::calcTime(float t){
    //set the position in this Alembic model
    if(isDemo){
        //map the .abc durration from 0.0 - 1.0
        float scaledTime = ofMap(t,0.0,1.0,0.0,aReader.getMaxTime());
        aReader.setTime(scaledTime);//animTime
    } else {    
        if(isAnimating) {
            
                switch (trackMode) {
                    case 3:
                        //nothing selected
                        
                        
                        break;
                    case 2:
                        //Note On AND Off
                        if(clipTime < midTime) {
                            clipTime += clipSpeedMod;
                            if(clipTime > midTime){
                                clipTime = midTime;//stop the clip halfway
                            }
                            //cout << "clipTime:" << clipTime << endl;
                        }
                        break;
                    case 1:
                        //Note On ONLY
                        if(!isHolding){
                            if(clipTime < endTime) {
                                clipTime += clipSpeedMod;
                                if(clipTime > endTime){
                                    clipTime = endTime;
                                }
                            } else {
                                isAnimating = false;
                            }
                        }
                        break;
                    case 0:
                        //Note On ONLY
                        if(clipTime < endTime) {
                            clipTime += clipSpeedMod;
                            if(clipTime > endTime){
                                clipTime = endTime;
                            }
                        } else {
                            isAnimating = false;
                        }

                        break;

                }

        } else {
            if(isHolding) {
                finalizeAnimation();
            } else {
                
            }
        }//end isAnimating
        
        aReader.setTime(clipTime);
        
    } // end isDemo

}

//--------------------------------------------------------------
bool abcModel::holdAnimation(){
    
    clipTime = aReader.getMaxTime()/segments;
    //isHolding = true;
    return true;
}

//--------------------------------------------------------------
bool abcModel::finalizeAnimation(){
    
    if(clipTime < endTime) {
        clipTime += clipSpeedMod;
        if(clipTime > endTime){
            clipTime = endTime;
        }
        //cout << "endTime:" << clipTime << endl;
    } else {
        isHolding = false;
        isAnimating = false;
    }    
    return true;
}

//--------------------------------------------------------------
void abcModel::setWSPosition(){
    
    setGlobalPosition(abcPostion.x, abcPostion.y, abcPostion.z);
    
}

//--------------------------------------------------------------
void abcModel::update(){

    //set the position 
    
    
    /*
    for (int i = 0; i < aReader.size(); i++)
	{
		ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        
		if (aReader.get(i, mesh))
		{
			//mesh.draw();
            vbo_mesh = mesh;
            //vbo_mesh.draw();
            
		}
	}
     */
    
    
}


//--------------------------------------------------------------
void abcModel::customDraw() {
    
    for (int i = 0; i < aReader.size(); i++)
	{
		//ofMesh mesh;
        //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        
		if (aReader.get(i, vbo_mesh))
		{
			//mesh.draw();
            //vbo_mesh = mesh;
            vbo_mesh.draw();
            
		}
	}
    
}

/*
void abcModel::draw(){
    
    //tried to move to update but it was only rendering one mesh per track.
    //vbo_mesh.draw();
    
    for (int i = 0; i < aReader.size(); i++)
	{
		//ofMesh mesh;
        //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
 
		if (aReader.get(i, vbo_mesh))
		{
			//mesh.draw();
            //vbo_mesh = mesh;
            vbo_mesh.draw();
		}
	}
}
*/

//--------------------------------------------------------------
void abcModel::report() {
    // show all drawable names
	aReader.dumpNames();
}

//--------------------------------------------------------------
void abcModel::INFOlaunchingToPlay() {
    cout    << "----->LDR (index:" << this_id    
            << ",name:" << abcName
            << ",speed:" << clipSpeedMod
            << ",ch:" << midiChannel
            << ",note:" << midiNote
            << ",type:" << ldrType
            << ",mode:" << trackMode
            << ",segments:" << segments
            << ",frames:" << segLength
            << ",currentSegment:" << currentSegment
            << ",TIME:" << clipTime << "-" << midTime << "-" << endTime
            << ",DURRATION:" << abcDurration
            << ")" << endl;
}




