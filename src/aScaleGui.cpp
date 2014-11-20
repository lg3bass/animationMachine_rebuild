//
//  aScaleGui.cpp
//  animationMachine
//
//  Created by White, Bob on 11/20/14.
//
//

#include "aScaleGui.h"
#include "ofApp.h"

//--------------------------------------------------------------
aScaleGui::aScaleGui(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aScaleGui::setup(){
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aScaleGui::reset(){
    setGUI_Scale(28);//feed in this number
    Scale_gui_1->loadSettings("GUI/xml/Scale_gui_1.xml");
    Scale_gui_1->setVisible(false);
    guiAlloc = true;
    doReset = false;
}

//--------------------------------------------------------------
void aScaleGui::update(){
    
}

//--------------------------------------------------------------
void aScaleGui::draw(){
    
}

//--------------------------------------------------------------
void aScaleGui::exit(){
    Scale_gui_1->saveSettings("GUI/xml/Scale_gui_1.xml");
    delete Scale_gui_1;
}


//--------------------------------------------------------------
void aScaleGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //get the track number from the name.
    vector<string> result=ofSplitString(name, "_");
    int row = ofToInt(result[0]);
    if (name == ofToString("CLEAR ALL")) {
        ofxUILabelButton *clearBut = (ofxUILabelButton *)Scale_gui_1->getWidget("CLEAR ALL");
        if(clearBut->getValue()){
            resetGUI(28, row,true);
        }
    } else if (ofIsStringInString(name, "TRK_CLR")) {
        ofxUIImageButton *clearBut = (ofxUIImageButton *)Scale_gui_1->getWidget(util::dDigiter(row)+"_TRK_CLR");
        if(clearBut->getValue()){
            resetGUI(row,row,false);
        }
    } else if (name == ofToString(util::dDigiter(row)+"_sX")) {
        ofxUINumberDialer *scaleX = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(row)+"_sX"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcScale.x = scaleX->getValue();
    } else if (name == ofToString(util::dDigiter(row)+"_sY")) {
        ofxUINumberDialer *scaleY = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(row)+"_sY"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcScale.y = scaleY->getValue();
    } else if (name == ofToString(util::dDigiter(row)+"_sZ")) {
        ofxUINumberDialer *scaleZ = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(row)+"_sZ"));
        ((ofApp*)ofGetAppPtr())->abcModels[row].abcScale.z = scaleZ->getValue();
    }
    
    
}


//--------------------------------------------------------------
void aScaleGui::setGUI_Scale(int numOfLoaders) {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    if (guiAlloc) {
        ofRemoveListener(Scale_gui_1->newGUIEvent, this, &aScaleGui::guiEvent);
        delete Scale_gui_1;
    }
    
    Scale_gui_1 = new ofxUIScrollableCanvas(0, 0, w + xInit * 2, ofGetHeight());
    Scale_gui_1->setScrollArea(0, 0, 300, ofGetHeight());
    Scale_gui_1->setScrollableDirections(false,true);
    
    Scale_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    Scale_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);
    
    Scale_gui_1->addWidgetDown(new ofxUILabel("Scale", OFX_UI_FONT_MEDIUM));
    
    Scale_gui_1->addWidgetDown(new ofxUILabelButton(70,false,"CLEAR ALL",OFX_UI_FONT_SMALL));
    
    Scale_gui_1->addSpacer(300,5);
    Scale_gui_1->addSpacer(10);
    Scale_gui_1->addSpacer();
    for(int i=0; i < numOfLoaders; i++){
        Scale_gui_1->addWidgetDown(new ofxUILabel(util::dDigiter(i), OFX_UI_FONT_SMALL));
        
        Scale_gui_1->addWidgetRight(new ofxUIImageButton(20,20,false,"GUI/clear.png",util::dDigiter(i)+"_TRK_CLR"));
        Scale_gui_1->addWidgetRight(new ofxUINumberDialer(-100,100,25.0,0,util::dDigiter(i)+"_sX",OFX_UI_FONT_SMALL));
        Scale_gui_1->addWidgetRight(new ofxUINumberDialer(-100,100,25.0,0,util::dDigiter(i)+"_sY",OFX_UI_FONT_SMALL));
        Scale_gui_1->addWidgetRight(new ofxUINumberDialer(-100,100,25.0,0,util::dDigiter(i)+"_sZ",OFX_UI_FONT_SMALL));
    }

    Scale_gui_1->addWidgetNorthOf(new ofxUILabel("ScaleX", OFX_UI_FONT_SMALL), "00_sX");
    Scale_gui_1->addWidgetNorthOf(new ofxUILabel("ScaleY", OFX_UI_FONT_SMALL), "00_sY");
    Scale_gui_1->addWidgetNorthOf(new ofxUILabel("ScaleZ", OFX_UI_FONT_SMALL), "00_sZ");
    
    Scale_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    //Scale_gui_1->autoSizeToFitWidgets();
    Scale_gui_1->getRect()->setWidth(ofGetWidth());
    
    ofAddListener(Scale_gui_1->newGUIEvent, this, &aScaleGui::guiEvent);
}

//--------------------------------------------------------------
void aScaleGui::resetGUI(int numOfLoaders, int selectLdr, bool allLdrs){
    int startRange = 0;
    int endRange = numOfLoaders;
    
    if(!allLdrs){
        startRange = selectLdr;
        endRange = selectLdr+1;
    }
    
    for(int i=startRange;i<endRange;i++){
        //Global positioning

        ofxUINumberDialer *scaleX = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sX"));
        scaleX->setValue(25.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.x = scaleX->getValue();
        ofxUINumberDialer *scaleY = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sY"));
        scaleY->setValue(25.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.y = scaleY->getValue();
        ofxUINumberDialer *scaleZ = (ofxUINumberDialer *)Scale_gui_1->getWidget(ofToString(util::dDigiter(i)+"_sZ"));
        scaleZ->setValue(25.0);
        ((ofApp*)ofGetAppPtr())->abcModels[i].abcScale.z = scaleZ->getValue();
    }
}


//--------------------------------------------------------------
void aScaleGui::toggleVisibility(bool _view){
    if(_view == false){
        Scale_gui_1->setVisible(false);
    } else {
        Scale_gui_1->toggleVisible();
    }
}
