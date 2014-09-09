//
//  aTrackGui.cpp
//  animationMachine
//
//  Created by bob white III on 11/29/13.
//
//

#include "aTrackGui.h"

aTrackGui* aTrackGui::_instance = NULL;
//--------------------------------------------------------------
aTrackGui* aTrackGui::Instance() {
    if (_instance == NULL) {
        _instance = new aTrackGui();
    }
    return _instance;
}

//--------------------------------------------------------------
aTrackGui::aTrackGui() {
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aTrackGui::setup(){
    //shaders
    //added from snakeNoise Project
    shader_0.load("shaders/phong/shader.vert", "shaders/phong/shader.frag");
}

//--------------------------------------------------------------
void aTrackGui::reset() {
    
    //initialize the GUI
    setGUI();
    
    //setup the materials
    resetMaterials();
    
    //load the settings from xml
    TRK_gui_1->loadSettings("GUI/gui_Track.xml");
    TRK_gui_1->setVisible(false);
    
    
    guiAlloc = true;
    doReset = false;

}

//--------------------------------------------------------------
void aTrackGui::update() {

}

//--------------------------------------------------------------
void aTrackGui::draw() {

}

//--------------------------------------------------------------
void aTrackGui::exit() {
    TRK_gui_1->saveSettings("GUI/gui_Track.xml");
    delete TRK_gui_1;
}

//--------------------------------------------------------------
void aTrackGui::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    ofColor c = ofColor(0,0,0);
    
    //TO-DO
    //--setup all the listeners for the matierial sliders.
    //--need to set this up in a loop. too many.

    if (name == "Shader0") {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[0] = toggle->getValue();
    } else if (name == "Shader1"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[1] = toggle->getValue();
    } else if (name == "Shader2"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[2] = toggle->getValue();
    } else if (name == "Shader3"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[3] = toggle->getValue();
    } else if (name == "Shader4"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[4] = toggle->getValue();
    } else if (name == "Shader5"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[5] = toggle->getValue();
    } else if (name == "Shader6"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[6] = toggle->getValue();
    } else if (name == "Shader7"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[7] = toggle->getValue();
    } else if (name == "Shader8"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[8] = toggle->getValue();
    } else if (name == "Shader9"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useShaders[9] = toggle->getValue();
    
    //material shininess
    } else if (name == "Shininess0") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[0].setShininess(slider->getScaledValue());
    } else if (name == "Shininess1") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[1].setShininess(slider->getScaledValue());
    } else if (name == "Shininess2") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[2].setShininess(slider->getScaledValue());
    } else if (name == "Shininess3") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[3].setShininess(slider->getScaledValue());
    } else if (name == "Shininess4") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[4].setShininess(slider->getScaledValue());
    } else if (name == "Shininess5") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[5].setShininess(slider->getScaledValue());
    } else if (name == "Shininess6") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[6].setShininess(slider->getScaledValue());
    } else if (name == "Shininess7") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[7].setShininess(slider->getScaledValue());
    } else if (name == "Shininess8") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[8].setShininess(slider->getScaledValue());
    } else if (name == "Shininess9") {
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        materials[9].setShininess(slider->getScaledValue());
        
        
        //------------------------------------------------
        //NEW materials[0] diffuse
        //diffuse red
    } else if (name == "dr0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setDiffuseColor(c);
            //materials[0].setAmbientColor(c);
        }
    } else if (name == "dr1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setDiffuseColor(c);
            //materials[1].setAmbientColor(c);
        }
    } else if (name == "dr2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setDiffuseColor(c);
            //materials[2].setAmbientColor(c);
        }
    } else if (name == "dr3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setDiffuseColor(c);
            //materials[3].setAmbientColor(c);
        }
    } else if (name == "dr4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setDiffuseColor(c);
            //materials[4].setAmbientColor(c);
        }
    } else if (name == "dr5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setDiffuseColor(c);
            //materials[5].setAmbientColor(c);
        }
    } else if (name == "dr6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setDiffuseColor(c);
            //materials[6].setAmbientColor(c);
        }
    } else if (name == "dr7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setDiffuseColor(c);
            //materials[7].setAmbientColor(c);
        }
    } else if (name == "dr8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setDiffuseColor(c);
            //materials[8].setAmbientColor(c);
        }
    } else if (name == "dr9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setDiffuseColor(c);
            //materials[9].setAmbientColor(c);
        }
        
        
        //diffuse green
    } else if (name == "dg0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setDiffuseColor(c);
            //materials[0].setAmbientColor(c);
        }
    } else if (name == "dg1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setDiffuseColor(c);
            //materials[1].setAmbientColor(c);
        }
    } else if (name == "dg2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setDiffuseColor(c);
            //materials[2].setAmbientColor(c);
        }
    } else if (name == "dg3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setDiffuseColor(c);
            //materials[3].setAmbientColor(c);
        }
    } else if (name == "dg4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setDiffuseColor(c);
            //materials[4].setAmbientColor(c);
        }
    } else if (name == "dg5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setDiffuseColor(c);
            //materials[5].setAmbientColor(c);
        }
    } else if (name == "dg6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setDiffuseColor(c);
            //materials[6].setAmbientColor(c);
        }
    } else if (name == "dg7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setDiffuseColor(c);
            //materials[7].setAmbientColor(c);
        }
    } else if (name == "dg8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setDiffuseColor(c);
            //materials[8].setAmbientColor(c);
        }
    } else if (name == "dg9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setDiffuseColor(c);
            //materials[9].setAmbientColor(c);
        }
        
        //diffuse blue
    } else if (name == "db0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setDiffuseColor(c);
            //materials[0].setAmbientColor(c);
        }
    } else if (name == "db1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setDiffuseColor(c);
            //materials[1].setAmbientColor(c);
        }
    } else if (name == "db2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setDiffuseColor(c);
            //materials[2].setAmbientColor(c);
        }
    } else if (name == "db3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setDiffuseColor(c);
            //materials[3].setAmbientColor(c);
        }
    } else if (name == "db4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setDiffuseColor(c);
            //materials[4].setAmbientColor(c);
        }
    } else if (name == "db5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setDiffuseColor(c);
            //materials[5].setAmbientColor(c);
        }
    } else if (name == "db6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setDiffuseColor(c);
            //materials[6].setAmbientColor(c);
        }
    } else if (name == "db7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setDiffuseColor(c);
            //materials[7].setAmbientColor(c);
        }
    } else if (name == "db8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setDiffuseColor(c);
            //materials[8].setAmbientColor(c);
        }
    } else if (name == "db9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setDiffuseColor(c);
            //materials[9].setAmbientColor(c);
        }
        

    //------------------------------------------------
    //NEW materials[0] emmissive
    //emmissive red
    } else if (name == "er0") {
        c = materials[0].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[0].setEmissiveColor(c);
    } else if (name == "er1") {
        c = materials[1].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[1].setEmissiveColor(c);
    } else if (name == "er2") {
        c = materials[2].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[2].setEmissiveColor(c);
    } else if (name == "er3") {
        c = materials[3].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[3].setEmissiveColor(c);
    } else if (name == "er4") {
        c = materials[4].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[4].setEmissiveColor(c);
    } else if (name == "er5") {
        c = materials[5].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[5].setEmissiveColor(c);
    } else if (name == "er6") {
        c = materials[6].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[6].setEmissiveColor(c);
    } else if (name == "er7") {
        c = materials[7].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[7].setEmissiveColor(c);
    } else if (name == "er8") {
        c = materials[8].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[8].setEmissiveColor(c);
    } else if (name == "er9") {
        c = materials[9].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        materials[9].setEmissiveColor(c);
        
    //emmissive green
    } else if (name == "eg0") {
        c = materials[0].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[0].setEmissiveColor(c);
    } else if (name == "eg1") {
        c = materials[1].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[1].setEmissiveColor(c);
    } else if (name == "eg2") {
        c = materials[2].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[2].setEmissiveColor(c);
    } else if (name == "eg3") {
        c = materials[3].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[3].setEmissiveColor(c);
    } else if (name == "eg4") {
        c = materials[4].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[4].setEmissiveColor(c);
    } else if (name == "eg5") {
        c = materials[5].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[5].setEmissiveColor(c);
    } else if (name == "eg6") {
        c = materials[6].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[6].setEmissiveColor(c);
    } else if (name == "eg7") {
        c = materials[7].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[7].setEmissiveColor(c);
    } else if (name == "eg8") {
        c = materials[8].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[8].setEmissiveColor(c);
    } else if (name == "eg9") {
        c = materials[9].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        materials[9].setEmissiveColor(c);
        
        
        
    //emmissive blue
    } else if (name == "eb0") {
        c = materials[0].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[0].setEmissiveColor(c);
    } else if (name == "eb1") {
        c = materials[1].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[1].setEmissiveColor(c);
    } else if (name == "eb2") {
        c = materials[2].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[2].setEmissiveColor(c);
    } else if (name == "eb3") {
        c = materials[3].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[3].setEmissiveColor(c);
    } else if (name == "eb4") {
        c = materials[4].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[4].setEmissiveColor(c);
    } else if (name == "eb5") {
        c = materials[5].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[5].setEmissiveColor(c);
    } else if (name == "eb6") {
        c = materials[6].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[6].setEmissiveColor(c);
    } else if (name == "eb7") {
        c = materials[7].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[7].setEmissiveColor(c);
    } else if (name == "eb8") {
        c = materials[8].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[8].setEmissiveColor(c);
    } else if (name == "eb9") {
        c = materials[9].getEmissiveColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        materials[9].setEmissiveColor(c);
        
        //materials[0] Specular colour
        //specular red
    } else if (name == "sr0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setSpecularColor(c);
            
        }
    } else if (name == "sr1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setSpecularColor(c);
            
        }
    } else if (name == "sr2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setSpecularColor(c);
            
        }
    } else if (name == "sr3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setSpecularColor(c);
            
        }
    } else if (name == "sr4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setSpecularColor(c);
            
        }
    } else if (name == "sr5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setSpecularColor(c);
            
        }
    } else if (name == "sr6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setSpecularColor(c);
            
        }
    } else if (name == "sr7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setSpecularColor(c);
            
        }
    } else if (name == "sr8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setSpecularColor(c);
            
        }
    } else if (name == "sr9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setSpecularColor(c);
            
        }
        
        
        
        //specular green
    } else if (name == "sg0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setSpecularColor(c);
            
        }
    } else if (name == "sg1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setSpecularColor(c);
            
        }
    } else if (name == "sg2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setSpecularColor(c);
            
        }
    } else if (name == "sg3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setSpecularColor(c);
            
        }
    } else if (name == "sg4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setSpecularColor(c);
            
        }
    } else if (name == "sg5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setSpecularColor(c);
            
        }
    } else if (name == "sg6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setSpecularColor(c);
            
        }
    } else if (name == "sg7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setSpecularColor(c);
            
        }
    } else if (name == "sg8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setSpecularColor(c);
            
        }
    } else if (name == "sg9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setSpecularColor(c);
            
        }
        
        
        //specular blue
    } else if (name == "sb0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[0]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[0].setSpecularColor(c);
            
        }
    } else if (name == "sb1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[1]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[1].setSpecularColor(c);
            
        }
    } else if (name == "sb2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[2]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[2].setSpecularColor(c);
            
        }
    } else if (name == "sb3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[3]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[3].setSpecularColor(c);
            
        }
    } else if (name == "sb4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[4]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[4].setSpecularColor(c);
            
        }
    } else if (name == "sb5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[5]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[5].setSpecularColor(c);
            
        }
    } else if (name == "sb6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[6]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[6].setSpecularColor(c);
            
        }
    } else if (name == "sb7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[7]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[7].setSpecularColor(c);
            
        }
    } else if (name == "sb8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[8]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[8].setSpecularColor(c);
            
        }
    } else if (name == "sb9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(!useShaders[9]){
            //setWSlider(matDiffSlider, c, slider->getScaledValue());
            materials[9].setSpecularColor(c);
            
        }

        //------------------------------------------------
        //SHADER diffuse
        //diffuse red
    } else if (name == "sdr0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[0]){
            v4Diffuse[0].x = slider->getValue();
        }
    } else if (name == "sdr1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[1]){
            v4Diffuse[1].x = slider->getValue();
        }
    } else if (name == "sdr2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[2]){
            v4Diffuse[2].x = slider->getValue();
        }
    } else if (name == "sdr3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[3]){
            v4Diffuse[3].x = slider->getValue();
        }
    } else if (name == "sdr4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[4]){
            v4Diffuse[4].x = slider->getValue();
        }
    } else if (name == "sdr5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[5]){
            v4Diffuse[5].x = slider->getValue();
        }
    } else if (name == "sdr6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[6]){
            v4Diffuse[6].x = slider->getValue();
        }
    } else if (name == "sdr7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[7]){
            v4Diffuse[7].x = slider->getValue();
        }
    } else if (name == "sdr8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[8]){
            v4Diffuse[8].x = slider->getValue();
        }
    } else if (name == "sdr9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[9]){
            v4Diffuse[9].x = slider->getValue();
        }
        
        
        //diffuse green
    } else if (name == "sdg0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[0]){
            v4Diffuse[0].y = slider->getValue();
        }
    } else if (name == "sdg1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[1]){
            v4Diffuse[1].y = slider->getValue();
        }
    } else if (name == "sdg2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[2]){
            v4Diffuse[2].y = slider->getValue();
        }
    } else if (name == "sdg3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[3]){
            v4Diffuse[3].y = slider->getValue();
        }
    } else if (name == "sdg4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[4]){
            v4Diffuse[4].y = slider->getValue();
        }
    } else if (name == "sdg5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[5]){
            v4Diffuse[5].y = slider->getValue();
        }
    } else if (name == "sdg6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[6]){
            v4Diffuse[6].y = slider->getValue();
        }
    } else if (name == "sdg7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[7]){
            v4Diffuse[7].y = slider->getValue();
        }
    } else if (name == "sdg8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[8]){
            v4Diffuse[8].y = slider->getValue();
        }
    } else if (name == "sdg9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[9]){
            v4Diffuse[9].y = slider->getValue();
        }
        
        //diffuse blue
    } else if (name == "sdb0") {
        c = materials[0].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[0]){
            v4Diffuse[0].z = slider->getValue();
        }
    } else if (name == "sdb1") {
        c = materials[1].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[1]){
            v4Diffuse[1].z = slider->getValue();
        }
    } else if (name == "sdb2") {
        c = materials[2].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[2]){
            v4Diffuse[2].z = slider->getValue();
        }
    } else if (name == "sdb3") {
        c = materials[3].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[3]){
            v4Diffuse[3].z = slider->getValue();
        }
    } else if (name == "sdb4") {
        c = materials[4].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[4]){
            v4Diffuse[4].z = slider->getValue();
        }
    } else if (name == "sdb5") {
        c = materials[5].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[5]){
            v4Diffuse[5].z = slider->getValue();
        }
    } else if (name == "sdb6") {
        c = materials[6].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[6]){
            v4Diffuse[6].z = slider->getValue();
        }
    } else if (name == "sdb7") {
        c = materials[7].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[7]){
            v4Diffuse[7].z = slider->getValue();
        }
    } else if (name == "sdb8") {
        c = materials[8].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[8]){
            v4Diffuse[8].z = slider->getValue();
        }
    } else if (name == "sdb9") {
        c = materials[9].getDiffuseColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[9]){
            v4Diffuse[9].z = slider->getValue();
        }
        
        //SHADER Specular colour
        //specular red
    } else if (name == "ssr0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[0]){
            v4Specular[0].x = slider->getValue();
        }
    } else if (name == "ssr1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[1]){
            v4Specular[1].x = slider->getValue();
        }
    } else if (name == "ssr2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[2]){
            v4Specular[2].x = slider->getValue();
        }
    } else if (name == "ssr3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[3]){
            v4Specular[3].x = slider->getValue();
        }
    } else if (name == "ssr4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[4]){
            v4Specular[4].x = slider->getValue();
        }
    } else if (name == "ssr5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[5]){
            v4Specular[5].x = slider->getValue();
        }
    } else if (name == "ssr6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[6]){
            v4Specular[6].x = slider->getValue();
        }
    } else if (name == "ssr7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[7]){
            v4Specular[7].x = slider->getValue();
        }
    } else if (name == "ssr8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[8]){
            v4Specular[8].x = slider->getValue();
        }
    } else if (name == "ssr9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.r = slider->getScaledValue();
        if(useShaders[9]){
            v4Specular[9].x = slider->getValue();
        }
        
        
        //specular green
    } else if (name == "ssg0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[0]){
            v4Specular[0].y = slider->getValue();
        }
    } else if (name == "ssg1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[1]){
            v4Specular[1].y = slider->getValue();
        }
    } else if (name == "ssg2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[2]){
            v4Specular[2].y = slider->getValue();
        }
    } else if (name == "ssg3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[3]){
            v4Specular[3].y = slider->getValue();
        }
    } else if (name == "ssg4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[4]){
            v4Specular[4].y = slider->getValue();
        }
    } else if (name == "ssg5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[5]){
            v4Specular[5].y = slider->getValue();
        }
    } else if (name == "ssg6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[6]){
            v4Specular[6].y = slider->getValue();
        }
    } else if (name == "ssg7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[7]){
            v4Specular[7].y = slider->getValue();
        }
    } else if (name == "ssg8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[8]){
            v4Specular[8].y = slider->getValue();
        }
    } else if (name == "ssg9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.g = slider->getScaledValue();
        if(useShaders[9]){
            v4Specular[9].y = slider->getValue();
        }
        
        
        //specular blue
    } else if (name == "ssb0") {
        c = materials[0].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[0]){
            v4Specular[0].z = slider->getValue();
        }
    } else if (name == "ssb1") {
        c = materials[1].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[1]){
            v4Specular[1].z = slider->getValue();
        }
    } else if (name == "ssb2") {
        c = materials[2].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[2]){
            v4Specular[2].z = slider->getValue();
        }
    } else if (name == "ssb3") {
        c = materials[3].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[3]){
            v4Specular[3].z = slider->getValue();
        }
    } else if (name == "ssb4") {
        c = materials[4].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[4]){
            v4Specular[4].z = slider->getValue();
        }
    } else if (name == "ssb5") {
        c = materials[5].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[5]){
            v4Specular[5].z = slider->getValue();
        }
    } else if (name == "ssb6") {
        c = materials[6].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[6]){
            v4Specular[6].z = slider->getValue();
        }
    } else if (name == "ssb7") {
        c = materials[7].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[7]){
            v4Specular[7].z = slider->getValue();
        }
    } else if (name == "ssb8") {
        c = materials[8].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[8]){
            v4Specular[8].z = slider->getValue();
        }
    } else if (name == "ssb9") {
        c = materials[9].getSpecularColor();
        ofxUISlider *slider = (ofxUISlider *)e.widget;
        c.b = slider->getScaledValue();
        if(useShaders[9]){
            v4Specular[9].z = slider->getValue();
        }
        
    } else if (name == "MatStats") {
        ofxUIButton *but = (ofxUIButton *)e.widget;
        if(but->getValue()==1){
            materialStats();
        }
        
    } else if (name == "ShaderStats") {
        ofxUIButton *but = (ofxUIButton *)e.widget;
        if(but->getValue()==1){
            materialStats();
        }
    }//END IF
    
    
    
}//end guiEvent
    
//--------------------------------------------------------------
void aTrackGui::setGUI() {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    
    if (guiAlloc) {
        ofRemoveListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent);
        delete TRK_gui_1;
    }
        
    
    TRK_gui_1 = new ofxUIScrollableCanvas(0, 0, w + xInit * 2, ofGetHeight());
    TRK_gui_1->setScrollArea(0, 0, 300, ofGetHeight());
    TRK_gui_1->setScrollableDirections(false,true);
    
    TRK_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    TRK_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);

    TRK_gui_1->addWidgetDown(new ofxUILabel("Materials/Shaders", OFX_UI_FONT_MEDIUM));
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 0", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader0", useShaders[0], 10, 10));
    TRK_gui_1->addSlider("Shininess0", 0, 128, 255, 230, 10);
    
    TRK_gui_1->addSpacer(230,10);
        
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr0", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg0", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db0", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er0", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg0", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb0", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr0", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg0", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb0", 0, 255, 100, h, vertH));

    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr0", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg0", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb0", 0, 255, 100, h, vertH));

    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr0", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg0", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb0", 0, 255, 100, h, vertH));
    
    //START MATERIAL SET 1
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 1", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader1", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess1", 0, 128, 255, 230, 10);
    
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
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr1", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg1", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb1", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr1", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg1", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb1", 0, 255, 100, h, vertH));
    
    //END MATERIAL SET 1
    
    //START MATERIAL SET 2
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 2", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader2", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess2", 0, 128, 255, 230, 10);
    
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

    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr2", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg2", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb2", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr2", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg2", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb2", 0, 255, 100, h, vertH));
    //END MATERIAL SET 2
    
    //START MATERIAL SET 3
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 3", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader3", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess3", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr3", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg3", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db3", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er3", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg3", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb3", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr3", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg3", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb3", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr3", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg3", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb3", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr3", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg3", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb3", 0, 255, 100, h, vertH));
    //END MATERIAL SET 3
 
    //START MATERIAL SET 4
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 4", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader4", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess4", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr4", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg4", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db4", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er4", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg4", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb4", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr4", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg4", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb4", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr4", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg4", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb4", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr4", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg4", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb4", 0, 255, 100, h, vertH));
    //END MATERIAL SET 4
 
    //START MATERIAL SET 5
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 5", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader5", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess5", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr5", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg5", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db5", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er5", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg5", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb5", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr5", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg5", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb5", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr5", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg5", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb5", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr5", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg5", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb5", 0, 255, 100, h, vertH));
    //END MATERIAL SET 5
    
    //START MATERIAL SET 6
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 6", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader6", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess6", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr6", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg6", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db6", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er6", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg6", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb6", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr6", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg6", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb6", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr6", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg6", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb6", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr6", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg6", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb6", 0, 255, 100, h, vertH));
    //END MATERIAL SET 6

    //START MATERIAL SET 7
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 7", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader7", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess7", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr7", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg7", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db7", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er7", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg7", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb7", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr7", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg7", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb7", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr7", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg7", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb7", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr7", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg7", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb7", 0, 255, 100, h, vertH));
    //END MATERIAL SET 7

    //START MATERIAL SET 8
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 8", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader8", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess8", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr8", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg8", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db8", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er8", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg8", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb8", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr8", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg8", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb8", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr8", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg8", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb8", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr8", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg8", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb8", 0, 255, 100, h, vertH));
    //END MATERIAL SET 8

    //START MATERIAL SET 9
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    TRK_gui_1->addSpacer(230,2);
    
    TRK_gui_1->addWidgetDown(new ofxUILabel("Material 9", OFX_UI_FONT_SMALL));
    TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader9", useShaders[1], 10, 10));
    TRK_gui_1->addSlider("Shininess9", 0, 128, 255, 230, 10);
    
    matDiffSlider.push_back(TRK_gui_1->addSlider("dr9", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matDiffSlider.push_back(TRK_gui_1->addSlider("dg9", 0, 255, 100, h, vertH));
    matDiffSlider.push_back(TRK_gui_1->addSlider("db9", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matEmSlider.push_back(TRK_gui_1->addSlider("er9", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eg9", 0, 255, 100, h, vertH));
    matEmSlider.push_back(TRK_gui_1->addSlider("eb9", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("sr9", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sg9", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sb9", 0, 255, 100, h, vertH));
    
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    //shader sliders
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdr9", 0, 255, 100, h, vertH));
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdg9", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("sdb9", 0, 255, 100, h, vertH));
    
    TRK_gui_1->addSpacer(2, vertH+10);
    
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssr9", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssg9", 0, 255, 100, h, vertH));
    matSpecSlider.push_back(TRK_gui_1->addSlider("ssb9", 0, 255, 100, h, vertH));
    //END MATERIAL SET 9
    
    //stats
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    TRK_gui_1->addButton("MatStats", false, 10, 10);
    TRK_gui_1->addButton("ShaderStats", false, 10, 10);
    
    // after you build the gui top to bottom. Last thing -- add the headers.
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Diffuse",OFX_UI_FONT_SMALL),"dr0");
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Emissive",OFX_UI_FONT_SMALL),"er0");
    TRK_gui_1->addWidgetNorthOf(new ofxUILabel("Specular",OFX_UI_FONT_SMALL),"sr0");
    
    TRK_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));

    TRK_gui_1->autoSizeToFitWidgets();
    TRK_gui_1->getRect()->setWidth(ofGetWidth());
    
    
    ofAddListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent);
    
}

//--------------------------------------------------------------
void aTrackGui::setWSlider(vector<ofxUISlider *>sliders, ofColor &c, float v){
    if (wModActive) {
        c.r = c.b = c.g = v;
        for (int i = 0; i < sliders.size(); i++)
            sliders.at(i)->setValue(v);
        
    }
    
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void aTrackGui::resetMaterials(){
    //initialize the materials
    for(int i=0; i<TRACKS; i++){
        materials[i].setShininess(128);
        materials[i].setSpecularColor(ofColor(255, 255, 255, 255));
        materials[i].setEmissiveColor(ofColor(0, 0, 0, 255));
        materials[i].setDiffuseColor(ofColor(255, 255, 255, 255));
        materials[i].setAmbientColor(ofColor(255, 255, 255, 255));
    }
}


//--------------------------------------------------------------
void aTrackGui::materialStats(){
    for(int i=0; i<TRACKS;i++) {
        cout << "Material " << i << ":  ";
        cout << "SHADER(" << ofToString(useShaders[i]) << "),";
        cout << "AMB(" << ofToString(materials[i].getAmbientColor()) << "),";
        cout << "DIF(" << ofToString(materials[i].getDiffuseColor()) << "),";
        cout << "EMS(" << ofToString(materials[i].getEmissiveColor()) << "),";
        cout << "SPC(" << ofToString(materials[i].getSpecularColor()) << "),";
        cout << "SHINE(" << ofToString(materials[i].getShininess()) << ")" << endl;
    
    }
}

//--------------------------------------------------------------
void aTrackGui::shaderStats(){
    for(int i=0; i<TRACKS;i++) {
        cout << "Material " << i << ":  " ;
        cout << "AMB(" << ofToString(materials[i].getAmbientColor()) << "),";
        cout << "DIF(" << ofToString(materials[i].getDiffuseColor()) << "),";
        cout << "EMS(" << ofToString(materials[i].getEmissiveColor()) << "),";
        cout << "SPC(" << ofToString(materials[i].getSpecularColor()) << "),";
        cout << "SHINE(" << ofToString(materials[i].getShininess()) << ")," << endl;
        
    }
}


