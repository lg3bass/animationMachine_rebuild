//
//  aRotationGui.cpp
//  animationMachine
//
//  Created by White, Bob on 11/19/14.
//
//

#include "aRotationGui.h"
#include "ofApp.h"

//--------------------------------------------------------------
aRotationGui::aRotationGui(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aRotationGui::setup(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aRotationGui::reset(){
    setGUI_Rot(28);//feed in this number
    Rotation_gui_1->loadSettings("GUI/xml/Rotation_gui_1.xml");
    Rotation_gui_1->setVisible(false);
    guiAlloc = true;
    doReset = false;
}

//--------------------------------------------------------------
void aRotationGui::update(){
    
}

//--------------------------------------------------------------
void aRotationGui::draw(){
    
}

//--------------------------------------------------------------
void aRotationGui::exit(){
    Rotation_gui_1->saveSettings("GUI/xml/Rotation_gui_1.xml");
    delete Rotation_gui_1;
}


//--------------------------------------------------------------
void aRotationGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //get the track number from the name.
    vector<string> result=ofSplitString(name, "_");
    int row = ofToInt(result[0]);
    if (name == ofToString("CLEAR ALL")) {
        ofxUILabelButton *clearBut = (ofxUILabelButton *)Rotation_gui_1->getWidget("CLEAR ALL");
        if(clearBut->getValue()){
            resetGUI(28, row,true);
        }
    } else if (ofIsStringInString(name, "TRK_CLR")) {
        ofxUIImageButton *clearBut = (ofxUIImageButton *)Rotation_gui_1->getWidget(util::dDigiter(row)+"_TRK_CLR");
        if(clearBut->getValue()){
            resetGUI(row,row,false);
        }
    } else if (name == ofToString(util::dDigiter(row)+"_rX")) {
        ofxUINumberDialer *oriX = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(row)+"_rX"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcOrientation.x = oriX->getValue();
    } else if (name == ofToString(util::dDigiter(row)+"_rY")) {
        ofxUINumberDialer *oriY = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(row)+"_rY"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcOrientation.y = oriY->getValue();
    } else if (name == ofToString(util::dDigiter(row)+"_rZ")) {
        ofxUINumberDialer *oriZ = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(row)+"_rZ"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcOrientation.z = oriZ->getValue();
    }
    
    
    
    
}


//--------------------------------------------------------------
void aRotationGui::setGUI_Rot(int numOfLoaders) {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    
    if (guiAlloc) {
        ofRemoveListener(Rotation_gui_1->newGUIEvent, this, &aRotationGui::guiEvent);
        delete Rotation_gui_1;
    }
    
    
    Rotation_gui_1 = new ofxUIScrollableCanvas(0, 0, w + xInit * 2, ofGetHeight());
    Rotation_gui_1->setScrollArea(0, 0, 300, ofGetHeight());
    Rotation_gui_1->setScrollableDirections(false,true);
    
    Rotation_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    Rotation_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);
    
    Rotation_gui_1->addWidgetDown(new ofxUILabel("Rotation", OFX_UI_FONT_MEDIUM));
    
    Rotation_gui_1->addWidgetDown(new ofxUILabelButton(70,false,"CLEAR ALL",OFX_UI_FONT_SMALL));
    
    Rotation_gui_1->addSpacer(300,5);
    Rotation_gui_1->addSpacer(10);
    Rotation_gui_1->addSpacer();
    for(int i=0; i < numOfLoaders; i++){
        Rotation_gui_1->addWidgetDown(new ofxUILabel(util::dDigiter(i), OFX_UI_FONT_SMALL));
        
        Rotation_gui_1->addWidgetRight(new ofxUIImageButton(20,20,false,"GUI/clear.png",util::dDigiter(i)+"_TRK_CLR"));
        Rotation_gui_1->addWidgetRight(new ofxUINumberDialer(-360,360,0.0,0,util::dDigiter(i)+"_rX",OFX_UI_FONT_SMALL));
        Rotation_gui_1->addWidgetRight(new ofxUINumberDialer(-360,360,0.0,0,util::dDigiter(i)+"_rY",OFX_UI_FONT_SMALL));
        Rotation_gui_1->addWidgetRight(new ofxUINumberDialer(-360,360,0.0,0,util::dDigiter(i)+"_rZ",OFX_UI_FONT_SMALL));

    }
    Rotation_gui_1->addWidgetNorthOf(new ofxUILabel("RotX", OFX_UI_FONT_SMALL), "00_rX");
    Rotation_gui_1->addWidgetNorthOf(new ofxUILabel("RotY", OFX_UI_FONT_SMALL), "00_rY");
    Rotation_gui_1->addWidgetNorthOf(new ofxUILabel("RotZ", OFX_UI_FONT_SMALL), "00_rZ");
    Rotation_gui_1->addWidgetNorthOf(new ofxUILabel("Scale", OFX_UI_FONT_SMALL), "00_S");
    
    
    Rotation_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    //Rotation_gui_1->autoSizeToFitWidgets();
    Rotation_gui_1->getRect()->setWidth(ofGetWidth());
    
    ofAddListener(Rotation_gui_1->newGUIEvent, this, &aRotationGui::guiEvent);
}

//--------------------------------------------------------------
void aRotationGui::resetGUI(int numOfLoaders, int selectLdr, bool allLdrs){
    int startRange = 0;
    int endRange = numOfLoaders;
    
    if(!allLdrs){
        startRange = selectLdr;
        endRange = selectLdr+1;
    }
    
    for(int i=startRange;i<endRange;i++){
        
        //Orientation
        ofxUINumberDialer *oriX = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rX"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.x = oriX->getValue();
        oriX->setValue(0.0);
        ofxUINumberDialer *oriY = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rY"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.y = oriY->getValue();
        oriY->setValue(0.0);
        ofxUINumberDialer *oriZ = (ofxUINumberDialer *)Rotation_gui_1->getWidget(ofToString(util::dDigiter(i)+"_rZ"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcOrientation.z = oriZ->getValue();
        oriZ->setValue(0.0);
        
    }
}


//--------------------------------------------------------------
void aRotationGui::toggleVisibility(bool _view){
    if(_view == false){
        Rotation_gui_1->setVisible(false);
    } else {
        Rotation_gui_1->toggleVisible();
    }
}