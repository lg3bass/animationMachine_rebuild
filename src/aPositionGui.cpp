//
//  aPositionGui.cpp
//  animationMachine
//
//  Created by White, Bob on 11/15/14.
//
//

#include "aPositionGui.h"
#include "ofApp.h"

//--------------------------------------------------------------
aPositionGui::aPositionGui(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aPositionGui::setup(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aPositionGui::reset(){
    setGUI_2(28);//feed in this number
    //Position_gui_1->loadSettings("GUI/xml/Position_gui_1.xml");
    //loadGUI(1);
    Position_gui_1->setVisible(false);
    guiAlloc = true;
    doReset = false;
}

//--------------------------------------------------------------
void aPositionGui::loadGUI(int sceneIndex){
    Position_gui_1->loadSettings("GUI/xml/Position_gui_"+ofToString(sceneIndex)+".xml");
    
}

//--------------------------------------------------------------
void aPositionGui::saveGUI(int sceneIndex){
    Position_gui_1->saveSettings("GUI/xml/Position_gui_"+ofToString(sceneIndex)+".xml");
    
}

//--------------------------------------------------------------
void aPositionGui::update(){
    
}

//--------------------------------------------------------------
void aPositionGui::draw(){
    
}

//--------------------------------------------------------------
void aPositionGui::exit(){
    //saveGUI(1);
    delete Position_gui_1;
}


//--------------------------------------------------------------
void aPositionGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //get the track number from the name.
    vector<string> result=ofSplitString(name, "_");
    int row = ofToInt(result[0]);
        if (name == ofToString("CLEAR ALL")) {
            ofxUILabelButton *clearBut = (ofxUILabelButton *)Position_gui_1->getWidget("CLEAR ALL");
            if(clearBut->getValue()){
                resetGUI(28, row,true);
            }
        } else if (ofIsStringInString(name, "TRK_CLR")) {
            ofxUIImageButton *clearBut = (ofxUIImageButton *)Position_gui_1->getWidget(util::dDigiter(row)+"_TRK_CLR");
            if(clearBut->getValue()){
                resetGUI(row,row,false);
            }
        } else if (name == ofToString(util::dDigiter(row)+"_tX")) {
            ofxUINumberDialer *posX = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_tX"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.x = posX->getValue();
        } else if (name == ofToString(util::dDigiter(row)+"_tY")) {
            ofxUINumberDialer *posY = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_tY"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.y = posY->getValue();
        } else if (name == ofToString(util::dDigiter(row)+"_tZ")) {
            ofxUINumberDialer *posZ = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_tZ"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.z = posZ->getValue();
        }





}


//--------------------------------------------------------------
void aPositionGui::setGUI_2(int numOfLoaders) {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    
    if (guiAlloc) {
        ofRemoveListener(Position_gui_1->newGUIEvent, this, &aPositionGui::guiEvent);
        delete Position_gui_1;
    }
    
    
    Position_gui_1 = new ofxUIScrollableCanvas(0, 0, w + xInit * 2, ofGetHeight());
    Position_gui_1->setScrollArea(0, 0, 300, ofGetHeight());
    Position_gui_1->setScrollableDirections(false,true);
    
    Position_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    Position_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);
    
    Position_gui_1->addWidgetDown(new ofxUILabel("Position", OFX_UI_FONT_MEDIUM));
    
    Position_gui_1->addWidgetDown(new ofxUILabelButton(70,false,"CLEAR ALL",OFX_UI_FONT_SMALL));
    
    Position_gui_1->addSpacer(300,5);
    Position_gui_1->addSpacer(10);
    Position_gui_1->addSpacer();
    for(int i=0; i < numOfLoaders; i++){
        Position_gui_1->addWidgetDown(new ofxUILabel(util::dDigiter(i), OFX_UI_FONT_SMALL));
        
        Position_gui_1->addWidgetRight(new ofxUIImageButton(20,20,false,"GUI/clear.png",util::dDigiter(i)+"_TRK_CLR"));
        Position_gui_1->addWidgetRight(new ofxUINumberDialer(-720,720,0.0,0,util::dDigiter(i)+"_tX",OFX_UI_FONT_SMALL));
        Position_gui_1->addWidgetRight(new ofxUINumberDialer(-720,720,0.0,0,util::dDigiter(i)+"_tY",OFX_UI_FONT_SMALL));
        Position_gui_1->addWidgetRight(new ofxUINumberDialer(-720,720,0.0,0,util::dDigiter(i)+"_tZ",OFX_UI_FONT_SMALL));
    }
    Position_gui_1->addWidgetNorthOf(new ofxUILabel("PosX", OFX_UI_FONT_SMALL), "00_tX");
    Position_gui_1->addWidgetNorthOf(new ofxUILabel("PosY", OFX_UI_FONT_SMALL), "00_tY");
    Position_gui_1->addWidgetNorthOf(new ofxUILabel("PosZ", OFX_UI_FONT_SMALL), "00_tZ");
    
    
    Position_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    //Position_gui_1->autoSizeToFitWidgets();
    Position_gui_1->getRect()->setWidth(ofGetWidth());
    
    ofAddListener(Position_gui_1->newGUIEvent, this, &aPositionGui::guiEvent);
}

//--------------------------------------------------------------
void aPositionGui::resetGUI(int numOfLoaders, int selectLdr, bool allLdrs){
    int startRange = 0;
    int endRange = numOfLoaders;
    
    //if False do only a range of one. reset a single loader
    if(!allLdrs){
        startRange = selectLdr;
        endRange = selectLdr+1;
    }

    for(int i=startRange;i<endRange;i++){
        //Global positioning
        ofxUINumberDialer *posX = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tX"));
        posX->setValue(0.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.x = posX->getValue();
        ofxUINumberDialer *posY = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tY"));
        posY->setValue(0.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.y = posY->getValue();
        ofxUINumberDialer *posZ = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tZ"));
        posZ->setValue(0.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.z = posZ->getValue();

        
    }
 }

//--------------------------------------------------------------
void aPositionGui::setupGUI(int numOfLoaders){
    int startRange = 0;
    int endRange = numOfLoaders;

    for(int i=startRange;i<endRange;i++){
        //Global positioning
        ofxUINumberDialer *posX = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tX"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.x = posX->getValue();
        ofxUINumberDialer *posY = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tY"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.y = posY->getValue();
        ofxUINumberDialer *posZ = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(i)+"_tZ"));
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcPostion.z = posZ->getValue();
        
    }
}

//--------------------------------------------------------------
void aPositionGui::toggleVisibility(bool _view){
    if(_view == false){
        Position_gui_1->setVisible(false);
    } else {
        Position_gui_1->toggleVisible();
    }
}
