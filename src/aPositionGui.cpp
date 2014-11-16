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
    
}

//--------------------------------------------------------------
void aPositionGui::reset(){
    setGUI_2();
    //Position_gui_1->loadSettings("GUI/xml/Position_gui_1.xml");
    //Position_gui_1->setVisible(false);
    guiAlloc = true;
    doReset = false;
}

//--------------------------------------------------------------
void aPositionGui::update(){
    
}

//--------------------------------------------------------------
void aPositionGui::draw(){
    
}

//--------------------------------------------------------------
void aPositionGui::exit(){
    //Position_gui_1->saveSettings("GUI/xml/Position_gui_1.xml");
    delete Position_gui_1;
}


//--------------------------------------------------------------
void aPositionGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //get the track number from the name.
    vector<string> result=ofSplitString(name, "_");
    int row = ofToInt(result[0]);



    
        if (name == ofToString(util::dDigiter(row)+"_X")) {
            ofxUINumberDialer *posX = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_X"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.x = posX->getValue();
        }
        if (name == ofToString(util::dDigiter(row)+"_Y")) {
            ofxUINumberDialer *posY = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_Y"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.y = posY->getValue();
        }
        if (name == ofToString(util::dDigiter(row)+"_Z")) {
            ofxUINumberDialer *posZ = (ofxUINumberDialer *)Position_gui_1->getWidget(ofToString(util::dDigiter(row)+"_Z"));
            ((ofApp*)ofGetAppPtr())->abcModels[row].abcPostion.z = posZ->getValue();
        }

}


//--------------------------------------------------------------
void aPositionGui::setGUI_2() {
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
    
    Position_gui_1->addWidgetDown(new ofxUILabel("Positioning", OFX_UI_FONT_MEDIUM));
    
    for(int i=0; i < 10; i++){
        Position_gui_1->addWidgetDown(new ofxUINumberDialer(-720,720,1.0,0,util::dDigiter(i)+"_X",OFX_UI_FONT_SMALL));
        Position_gui_1->addWidgetRight(new ofxUINumberDialer(-720,720,1.0,0,util::dDigiter(i)+"_Y",OFX_UI_FONT_SMALL));
        Position_gui_1->addWidgetRight(new ofxUINumberDialer(-720,720,1.0,0,util::dDigiter(i)+"_Z",OFX_UI_FONT_SMALL));
    }

    
    Position_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    //TRK_gui_2->autoSizeToFitWidgets();
    Position_gui_1->getRect()->setWidth(ofGetWidth());
    
    
    
    
    ofAddListener(Position_gui_1->newGUIEvent, this, &aPositionGui::guiEvent);
}
