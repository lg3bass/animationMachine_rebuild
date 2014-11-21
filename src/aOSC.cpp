//
//  aOSC.cpp
//  animationMachine
//
//  Created by White, Bob on 11/20/14.
//
//

#include "aOSC.h"
#include "ofApp.h"

//--------------------------------------------------------------
aOSC::aOSC(){
    
}

//--------------------------------------------------------------
void aOSC::setup(){
    cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
}

//--------------------------------------------------------------
void aOSC::reset(){
    
}

//--------------------------------------------------------------
void aOSC::update(){
    newOscMessage();
}

//--------------------------------------------------------------
void aOSC::draw(){

    //This just draws the osc port to the screen. Totally unnecessary.
    string buf;
	buf = "osc port: " + ofToString(PORT);
	ofDrawBitmapString(buf, 1100, 10);
}

//--------------------------------------------------------------
void aOSC::exit(){
    
}

//--------------------------------------------------------------
void aOSC::newOscMessage(){
    
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        

		if(m.getAddress() == "/nextscene"){
            ((ofApp*)ofGetAppPtr())->saveCam.nextView(4.0);
            ((ofApp*)ofGetAppPtr())->addMessage(">saveCam.nextView(4.0)");
		} else if (m.getAddress() == "/zeroview"){
            ((ofApp*)ofGetAppPtr())->saveCam.zeroView(4.0);
            ((ofApp*)ofGetAppPtr())->addMessage(">saveCam.zeroView(4.0)");
        } else if(m.getAddress() == "/resetOF"){
            ((ofApp*)ofGetAppPtr())->resetAnimation(((ofApp*)ofGetAppPtr())->numOfABC);
            ((ofApp*)ofGetAppPtr())->addMessage(">resetAnimation()");
		//SCENES
        } else if(m.getAddress() == "/scene1"){
            if (m.getArgAsFloat(0) == 1.0){
                    ((ofApp*)ofGetAppPtr())->addMessage(">loadScene(1): value:"+ofToString(m.getArgAsFloat(0)));
                    ((ofApp*)ofGetAppPtr())->loadScene(1);
            }
		} else if(m.getAddress() == "/scene2"){
            if (m.getArgAsFloat(0) == 1.0){
                    ((ofApp*)ofGetAppPtr())->addMessage(">loadScene(2): value:"+ofToString(m.getArgAsFloat(0)));
                    ((ofApp*)ofGetAppPtr())->loadScene(2);
            }
		} else if(m.getAddress() == "/scene3"){
            if (m.getArgAsFloat(0) == 1.0){
                ((ofApp*)ofGetAppPtr())->addMessage(">loadScene(3): value:"+ofToString(m.getArgAsFloat(0)));
                ((ofApp*)ofGetAppPtr())->loadScene(3);
            }
		} else if(m.getAddress() == "/scene4"){
            if (m.getArgAsFloat(0) == 1.0){
                ((ofApp*)ofGetAppPtr())->addMessage(">loadScene(4): value:"+ofToString(m.getArgAsFloat(0)));
                ((ofApp*)ofGetAppPtr())->loadScene(4);
            }
		} else if(m.getAddress() == "/scene5"){
            if (m.getArgAsFloat(0) == 1.0){
                ((ofApp*)ofGetAppPtr())->addMessage(">loadScene(5): value:"+ofToString(m.getArgAsFloat(0)));
                ((ofApp*)ofGetAppPtr())->loadScene(5);
            }
        } else {
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = "unknown"+m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if (m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                } else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                } else if (m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                } else {
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            //((ofApp*)ofGetAppPtr())->addMessage(msg_string);
        }//end else
 

        for(int i=0;i<((ofApp*)ofGetAppPtr())->numOfABC;i++){

            if(m.getAddress() == ""){
                
            //POSITION
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i))+"_tX"){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.x = m.getArgAsFloat(0);
                ofxUINumberDialer *posX = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myPositionGui.Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tX"));
                posX->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_tY")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.y = m.getArgAsFloat(0);
                ofxUINumberDialer *posY = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myPositionGui.Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tY"));
                posY->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_tZ")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.z = m.getArgAsFloat(0);
                ofxUINumberDialer *posZ = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myPositionGui.Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tZ"));
                posZ->setValue(m.getArgAsFloat(0));
           
            //SCALE
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_sX")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.x = m.getArgAsFloat(0);
                ofxUINumberDialer *scaleX = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myScaleGui.Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sX"));
                scaleX->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_sY")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.y = m.getArgAsFloat(0);
                ofxUINumberDialer *scaleY = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myScaleGui.Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sY"));
                scaleY->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_sZ")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.z = m.getArgAsFloat(0);
                ofxUINumberDialer *scaleZ = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myScaleGui.Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sZ"));
                scaleZ->setValue(m.getArgAsFloat(0));
            
            //ROTATION
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_rX")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.x = m.getArgAsFloat(0);
                ofxUINumberDialer *rotX = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myRotationGui.Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rX"));
                rotX->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i)+"_rY")){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.y = m.getArgAsFloat(0);
                ofxUINumberDialer *rotY = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myRotationGui.Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rY"));
                rotY->setValue(m.getArgAsFloat(0));
                
            } else if(m.getAddress() == ofToString("/"+util::dDigiter(i))+"_rZ"){
                ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.z = m.getArgAsFloat(0);
                ofxUINumberDialer *rotZ = (ofxUINumberDialer *)((ofApp*)ofGetAppPtr())->myRotationGui.Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rZ"));
                rotZ->setValue(m.getArgAsFloat(0));
            
            } else {
                
            }//end if
            
        }//end for
        
        //OSC Material properties (diffuse, emissive)
        for(int j=0;j<10;j++){
            
            if(m.getAddress() == ""){
                
            } else if(m.getAddress() == "/diffuse"+ofToString(j)){
                /*
                string msg_string = "dr0:";
                msg_string += m.getArgAsString(0);
                ((ofApp*)ofGetAppPtr())->addMessage(msg_string);
                */
                
                //DIFFUSE
                //set the color
                diffuse_c.set(ofToFloat(m.getArgAsString(0)), ofToFloat(m.getArgAsString(1)), ofToFloat(m.getArgAsString(2)));
                ((ofApp*)ofGetAppPtr())->myTrackGui.materials[j].setDiffuseColor(diffuse_c);
                
                //set the sliders
                ofxUISlider *difR = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("dr"+ofToString(j));
                difR->setValue(ofToFloat(m.getArgAsString(0)));
                ofxUISlider *difG = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("dg"+ofToString(j));
                difG->setValue(ofToFloat(m.getArgAsString(1)));
                ofxUISlider *difB = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("db"+ofToString(j));
                difB->setValue(ofToFloat(m.getArgAsString(2)));
            } else if(m.getAddress() == "/emissive"+ofToString(j)){
                /*
                 string msg_string = "dr0:";
                 msg_string += m.getArgAsString(0);
                 ((ofApp*)ofGetAppPtr())->addMessage(msg_string);
                 */
                
                //EMISSIVE
                //set the color
                emissive_c.set(ofToFloat(m.getArgAsString(0)), ofToFloat(m.getArgAsString(1)), ofToFloat(m.getArgAsString(2)));
                ((ofApp*)ofGetAppPtr())->myTrackGui.materials[j].setEmissiveColor(emissive_c);
                
                //set the sliders
                ofxUISlider *emisR = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("er"+ofToString(j));
                emisR->setValue(ofToFloat(m.getArgAsString(0)));
                ofxUISlider *emisG = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("eg"+ofToString(j));
                emisG->setValue(ofToFloat(m.getArgAsString(1)));
                ofxUISlider *emisB = (ofxUISlider *)((ofApp*)ofGetAppPtr())->myTrackGui.TRK_gui_1->getWidget("eb"+ofToString(j));
                emisB->setValue(ofToFloat(m.getArgAsString(2)));
            }
 
        
        
        }//end for
        
    }//end while
}


