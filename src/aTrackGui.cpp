//
//  aTrackGui.cpp
//  animationMachine
//
//  Created by bob white III on 11/29/13.
//
//

#include "aTrackGui.h"

aTrackGui* aTrackGui::_instance = NULL;

aTrackGui* aTrackGui::Instance() {
    if (_instance == NULL) {
        _instance = new aTrackGui();
    }
    return _instance;
}


aTrackGui::aTrackGui() {
    doReset = guiAlloc = false;
}

void aTrackGui::setup(){
    //TO-DO
    //-- populate the matieral vector with content.
    
    
}


void aTrackGui::reset() {
    
    setGUI();
    
    TRK_gui_1->loadSettings("GUI/gui_Track.xml");
    TRK_gui_1->setVisible(false);
    
    guiAlloc = true;
    doReset = false;

    //initialize the materials
    for(int i=0; i<10; i++){
    
    materials[i].setShininess(128);
    materials[i].setSpecularColor(ofColor(255, 255, 255, 255));
    materials[i].setEmissiveColor(ofColor(0, 0, 0, 255));
    materials[i].setDiffuseColor(ofColor(255, 255, 255, 255));
    materials[i].setAmbientColor(ofColor(255, 255, 255, 255));
    }

    
}

void aTrackGui::update() {
    
}

void aTrackGui::draw() {
    
}

void aTrackGui::exit() {
    TRK_gui_1->saveSettings("GUI/gui_Track.xml");
    delete TRK_gui_1;
}

void aTrackGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //TO-DO
    //--setup all the listeners for the matierial sliders.
    //--need to set this up in a loop. too many.

 //Material 1
if (name == "Mat 1 Shine") {
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    materials[0].setShininess(slider->getScaledValue());
    
//material diffuse
} else if (name == "dr1") {
    ofColor c = materials[0].getDiffuseColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.r = slider->getScaledValue();
    setWSlider(matDiffSlider, c, slider->getScaledValue());
    materials[0].setDiffuseColor(c);
    materials[0].setAmbientColor(c);
} else if (name == "dg1") {
    ofColor c = materials[0].getDiffuseColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.g = slider->getScaledValue();
    setWSlider(matDiffSlider, c, slider->getScaledValue());
    materials[0].setDiffuseColor(c);
    materials[0].setAmbientColor(c);
} else if (name == "db1") {
    ofColor c = materials[0].getDiffuseColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.b = slider->getScaledValue();
    setWSlider(matDiffSlider, c, slider->getScaledValue());
    materials[0].setDiffuseColor(c);
    materials[0].setAmbientColor(c);
} else if (name == "da1") {
    ofColor c = materials[0].getDiffuseColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.a = slider->getScaledValue();
    materials[0].setDiffuseColor(c);
    materials[0].setAmbientColor(c);
}
 /*
//material emissive colour
} else if (name == "MER1") {
    ofColor c = myLights2->material1.getEmissiveColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.r = slider->getScaledValue();
    setWSlider(matEmSlider, c, slider->getScaledValue());
    myLights2->material1.setEmissiveColor(c);
} else if (name == "MEG1") {
    ofColor c = myLights2->material1.getEmissiveColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.g = slider->getScaledValue();
    setWSlider(matEmSlider, c, slider->getScaledValue());
    myLights2->material1.setEmissiveColor(c);
} else if (name == "MEB1") {
    ofColor c = myLights2->material1.getEmissiveColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.b = slider->getScaledValue();
    setWSlider(matEmSlider, c, slider->getScaledValue());
    myLights2->material1.setEmissiveColor(c);
} else if (name == "MEA1") {
    ofColor c = myLights2->material1.getEmissiveColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.a = slider->getScaledValue();
    myLights2->material1.setEmissiveColor(c);
    
    //material specular colour
} else if (name == "MSR1") {
    ofColor c = myLights2->material1.getSpecularColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.r = slider->getScaledValue();
    setWSlider(matSpecSlider, c, slider->getScaledValue());
    myLights2->material1.setSpecularColor(c);
    
} else if (name == "MSG1") {
    ofColor c = myLights2->material1.getSpecularColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.g = slider->getScaledValue();
    setWSlider(matSpecSlider, c, slider->getScaledValue());
    myLights2->material1.setSpecularColor(c);
} else if (name == "MSB1") {
    ofColor c = myLights2->material1.getSpecularColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.b = slider->getScaledValue();
    setWSlider(matSpecSlider, c, slider->getScaledValue());
    myLights2->material1.setSpecularColor(c);
} else if (name == "MSA1") {
    ofColor c = myLights2->material1.getSpecularColor();
    ofxUISlider *slider = (ofxUISlider *)e.widget;
    c.a = slider->getScaledValue();
    myLights2->material1.setSpecularColor(c);
    
    */
    
}

void aTrackGui::setGUI() {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    
    if (guiAlloc) {
        ofRemoveListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent);
        delete TRK_gui_1;
    }
    
    
    TRK_gui_1 = new ofxUICanvas(0, 0, w + xInit * 2, ofGetHeight());
    TRK_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    TRK_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);

    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 1", OFX_UI_FONT_MEDIUM));
    TRK_gui_1->addSlider("Mat 1 Shine", 0, 128, 255, 230, 10);
    
    TRK_gui_1->addSpacer(230,10);
        
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr1", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg1", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db1", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er1", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg1", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb1", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr1", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg1", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb1", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addLabel("Material 2", OFX_UI_FONT_MEDIUM);
    TRK_gui_1->addSlider("Mat 2 Shine", 0, 128, 255, 230, 10);

    TRK_gui_1->addSpacer(230,10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr2", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg2", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db2", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er2", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg2", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb2", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr2", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg2", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb2", 0, 255, 100, h, vertH));
    
    
    
    
    // after you build the gui top to bottom. Last thing -- add the headers.
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Diffuse",OFX_UI_FONT_SMALL),"dr1");
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Emissive",OFX_UI_FONT_SMALL),"er1");
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Specular",OFX_UI_FONT_SMALL),"sr1");
    
    

    
    TRK_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    ofAddListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent);
    
}

void aTrackGui::setWSlider(vector<ofxUISlider *>sliders, ofColor &c, float v){
    if (wModActive) {
        c.r = c.b = c.g = v;
        for (int i = 0; i < sliders.size(); i++)
            sliders.at(i)->setValue(v);
        
    }
    
}

void aTrackGui::toggleVisibility(bool _view){
    if(_view == false){
        TRK_gui_1->setVisible(false);
        //TRK_gui_2->setVisible(false);
        //TRK_gui_3->setVisible(false);
        //TRK_gui_4->setVisible(false);
        //TRK_gui_5->setVisible(false);
    } else {
        TRK_gui_1->toggleVisible();
        //TRK_gui_2->toggleVisible();
        //TRK_gui_3->toggleVisible();
        //TRK_gui_4->toggleVisible();
        //TRK_gui_5->toggleVisible();
    }
}


