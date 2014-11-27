//
//  aTrackGui.cpp
//  animationMachine
//
//  Created by bob white III on 11/29/13.
//
//

#include "aTrackGui.h"
#include "ofApp.h"



//USED TO BE (the mayor of) SINGLETON...
//aTrackGui* aTrackGui::_instance = NULL;
//--------------------------------------------------------------
//aTrackGui* aTrackGui::Instance() {
//    if (_instance == NULL) {
//        _instance = new aTrackGui();
//    }
//    return _instance;
//}



//--------------------------------------------------------------
aTrackGui::aTrackGui() {
    doReset = guiAlloc = false;
}

//--------------------------------------------------------------
void aTrackGui::setup(){
    //pull in my shaders
    lookForShaders();
    
    //load the phong, last shader
    loadExtShader(externalShaders.size()-1);
    
    
    
}

//--------------------------------------------------------------
void aTrackGui::reset() {
    
    //initialize the GUI
    setGUI_1();
    
    //setup the materials
    resetMaterials();
    
    //load the settings from xml
    TRK_gui_1->loadSettings("GUI/xml/gui_1_Track.xml");
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
    TRK_gui_1->saveSettings("GUI/xml/gui_1_Track.xml");
    delete TRK_gui_1;
}

//--------------------------------------------------------------
void aTrackGui::guiEvent_1(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    ofColor c = ofColor(0,0,0);

    for(int i=0;i<TRACKS;i++){
        if (name == "Shader"+ofToString(i)) {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
            useShaders[i] = toggle->getValue();
        }
        if (name == "Shininess"+ofToString(i)) {
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            materials[i].setShininess(slider->getScaledValue());
        }
        //material>diffuse.red
        if (name == "dr"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.r = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setDiffuseColor(c);
                //materials[i].setAmbientColor(c);
            }
        }
        //material>diffuse.green
        if (name == "dg"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.g = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setDiffuseColor(c);
                //materials[i].setAmbientColor(c);
            }
        }
        //material>diffues.blue
        if (name == "db"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.b = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setDiffuseColor(c);
                //materials[i].setAmbientColor(c);
            }
        }
        //material>emissive.red
        if (name == "er"+ofToString(i)) {
            c = materials[i].getEmissiveColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.r = slider->getScaledValue();
            materials[i].setEmissiveColor(c);
        }
        //materials>emissive.green
        if (name == "eg"+ofToString(i)) {
            c = materials[i].getEmissiveColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.g = slider->getScaledValue();
            materials[i].setEmissiveColor(c);
        }
        //materials>emissive.blue
        if (name == "eb"+ofToString(i)) {
            c = materials[i].getEmissiveColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.b = slider->getScaledValue();
            materials[i].setEmissiveColor(c);
        }
        //materials>specular.red
        if (name == "sr"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.r = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setSpecularColor(c);
                
            }
        }
        //materials>specular.green
        if (name == "sg"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.g = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setSpecularColor(c);
                
            }
        }
        //materials>specular.blue
        if (name == "sb"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.b = slider->getScaledValue();
            if(!useShaders[i]){
                //setWSlider(matDiffSlider, c, slider->getScaledValue());
                materials[i].setSpecularColor(c);
                
            }
        }
        //shader>diffuse.red
        if (name == "sdr"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.r = slider->getScaledValue();
            if(useShaders[i]){
                v4Diffuse[i].x = slider->getValue();
            }
        }
        //shader>diffuse.green
        if (name == "sdg"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.g = slider->getScaledValue();
            if(useShaders[i]){
                v4Diffuse[i].y = slider->getValue();
            }
        }
        //shader>diffuse.blue
        if (name == "sdb"+ofToString(i)) {
            c = materials[i].getDiffuseColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.b = slider->getScaledValue();
            if(useShaders[i]){
                v4Diffuse[i].z = slider->getValue();
            }
        }
        //shader>specular.red
        if (name == "ssr"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.r = slider->getScaledValue();
            if(useShaders[i]){
                v4Specular[i].x = slider->getValue();
            }
        }
        //shader>specular.green
        if (name == "ssg"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.g = slider->getScaledValue();
            if(useShaders[i]){
                v4Specular[i].y = slider->getValue();
            }
        }
        //shader>specular.blue
        if (name == "ssb"+ofToString(i)) {
            c = materials[i].getSpecularColor();
            ofxUISlider *slider = (ofxUISlider *)e.widget;
            c.b = slider->getScaledValue();
            if(useShaders[i]){
                v4Specular[i].z = slider->getValue();
            }
        }
    }//end for loop
    
    
    
  
    
    
    if (name == "MatStats") {
        ofxUIButton *but = (ofxUIButton *)e.widget;
        if(but->getValue()==1){
            materialStats();
        }
        
    } else if (name == "ShaderStats") {
        ofxUIButton *but = (ofxUIButton *)e.widget;
        if(but->getValue()==1){
            shaderStats();
        }
    }//END IF
    
    
}//end guiEvent
    
//--------------------------------------------------------------
void aTrackGui::setGUI_1() {
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1000 - xInit * 2;
    float vertH = 40;
    float h = 16;
    
    
    if (guiAlloc) {
        ofRemoveListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent_1);
        delete TRK_gui_1;
    }
        
    
    TRK_gui_1 = new ofxUIScrollableCanvas(0, 0, w + xInit * 2, ofGetHeight());
    TRK_gui_1->setScrollArea(0, 0, 300, ofGetHeight());
    TRK_gui_1->setScrollableDirections(false,true);
    
    TRK_gui_1->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    TRK_gui_1->setFontSize(OFX_UI_FONT_SMALL, 5);

    TRK_gui_1->addWidgetDown(new ofxUILabel("Materials/Shaders", OFX_UI_FONT_MEDIUM));
    
    for(int i=0; i<TRACKS; i++){
    
        //START MATERIAL
        TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
        
        TRK_gui_1->addSpacer(230,2);
        
        
        
        TRK_gui_1->addWidgetDown(new ofxUILabel("Material "+ofToString(i), OFX_UI_FONT_SMALL));
        TRK_gui_1->addWidgetRight(new ofxUIToggle("Shader"+ofToString(i), useShaders[i], 10, 10));
        TRK_gui_1->addSlider("Shininess"+ofToString(i), 0, 128, 255, 230, 10);
        
        TRK_gui_1->addWidgetDown(new ofxUILabel(70,"Diffuse",OFX_UI_FONT_SMALL));
        TRK_gui_1->addWidgetRight(new ofxUILabel(70,"Emissive",OFX_UI_FONT_SMALL));
        TRK_gui_1->addWidgetRight(new ofxUILabel(70,"Specular",OFX_UI_FONT_SMALL));
        
        matDiffSlider.push_back(TRK_gui_1->addSlider("dr"+ofToString(i), 0, 255, 100, h, vertH));
        TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
        matDiffSlider.push_back(TRK_gui_1->addSlider("dg"+ofToString(i), 0, 255, 100, h, vertH));
        matDiffSlider.push_back(TRK_gui_1->addSlider("db"+ofToString(i), 0, 255, 100, h, vertH));
        
        TRK_gui_1->addSpacer(2, vertH+10);
        
        matEmSlider.push_back(TRK_gui_1->addSlider("er"+ofToString(i), 0, 255, 100, h, vertH));
        matEmSlider.push_back(TRK_gui_1->addSlider("eg"+ofToString(i), 0, 255, 100, h, vertH));
        matEmSlider.push_back(TRK_gui_1->addSlider("eb"+ofToString(i), 0, 255, 100, h, vertH));
        
        TRK_gui_1->addSpacer(2, vertH+10);
        
        matSpecSlider.push_back(TRK_gui_1->addSlider("sr"+ofToString(i), 0, 255, 100, h, vertH));
        matSpecSlider.push_back(TRK_gui_1->addSlider("sg"+ofToString(i), 0, 255, 100, h, vertH));
        matSpecSlider.push_back(TRK_gui_1->addSlider("sb"+ofToString(i), 0, 255, 100, h, vertH));
        
        TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
        //shader sliders
        matSpecSlider.push_back(TRK_gui_1->addSlider("sdr"+ofToString(i), 0, 255, 100, h, vertH));
        TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
        matSpecSlider.push_back(TRK_gui_1->addSlider("sdg"+ofToString(i), 0, 255, 100, h, vertH));
        matSpecSlider.push_back(TRK_gui_1->addSlider("sdb"+ofToString(i), 0, 255, 100, h, vertH));
        
        TRK_gui_1->addSpacer(2, vertH+10);
        
        matSpecSlider.push_back(TRK_gui_1->addSlider("ssr"+ofToString(i), 0, 255, 100, h, vertH));
        matSpecSlider.push_back(TRK_gui_1->addSlider("ssg"+ofToString(i), 0, 255, 100, h, vertH));
        matSpecSlider.push_back(TRK_gui_1->addSlider("ssb"+ofToString(i), 0, 255, 100, h, vertH));
        
        //END MATERIAL
    
    }// end for loop
    
    
    //stats
    TRK_gui_1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    TRK_gui_1->addButton("MatStats", false, 10, 10);
    TRK_gui_1->addButton("ShaderStats", false, 10, 10);
    
    TRK_gui_1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));

    TRK_gui_1->autoSizeToFitWidgets();
    TRK_gui_1->getRect()->setWidth(ofGetWidth());
    
    ofAddListener(TRK_gui_1->newGUIEvent, this, &aTrackGui::guiEvent_1);
    
}




//NOT NEEDED ANYMORE>  DELETE AND DELETE COMMENTED CODE IN GUI EVENT
//
//--------------------------------------------------------------
void aTrackGui::setWSlider(vector<ofxUISlider *>sliders, ofColor &c, float v){
    if (wModActive) {
        c.r = c.b = c.g = v;
        for (int i = 0; i < sliders.size(); i++)
            sliders.at(i)->setValue(v);
        
    }
    
}


//--------------------------------------------------------------
void aTrackGui::cycleShaders(){
    shaderIndex++;
    
    if(shaderIndex == externalShaders.size()){
        shaderIndex = 0;
    }
    
    loadExtShader(shaderIndex);
}

//--------------------------------------------------------------
void aTrackGui::loadExtShader(int i){
    string vert = externalShaders[i].path + externalShaders[i].vert.getFileName();
    string frag = externalShaders[i].path + externalShaders[i].frag.getFileName();
    shader_0.load(vert, frag);
    ((ofApp*)ofGetAppPtr())->addMessage("Loaded shader:  "+externalShaders[i].name);
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
void aTrackGui::lookForShaders(){
    string path = "myshaders";
    ofDirectory dir(path);
    dir.listDir();

    for(int j=0;j<dir.numFiles();j++){
        //every directory you find add another extShader struct.
        externalShaders.push_back(extShader());
        
        externalShaders[j].name = dir.getName(j);
        externalShaders[j].path = path+"/"+dir.getName(j)+"/";
        
        //get the files in the subdirectories
        ofDirectory shader(dir.getPath(j));
        shader.allowExt("frag");
        shader.allowExt("vert");
        shader.allowExt("jpg");
        shader.listDir();
        
        //create a list of the files within.
        vector<ofFile> shaders = shader.getFiles();
        
        //pick out the frag,vert,geo,and img files
        for(int k=0;k<shaders.size();k++){
            if (shaders[k].getExtension() == "frag"){

                externalShaders[j].frag = ofFile(shaders[k]);
            }
            if (shaders[k].getExtension() == "vert"){

                externalShaders[j].vert = ofFile(shaders[k]);
            }
            if (shaders[k].getExtension() == "jpg"){

                externalShaders[j].img = ofFile(shaders[k]);
            }
        }
        
    }
    
    /*
    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++){
        //cout << externalShaders[i].frag.getBaseName() << endl;
        //cout << externalShaders[i].frag.getFileName() << endl;
        //cout << externalShaders[i].frag.getAbsolutePath() << endl;
        //cout << externalShaders[i].vert.getBaseName() << endl;
        //cout << externalShaders[i].vert.getFileName() << endl;
        //cout << externalShaders[i].vert.getAbsolutePath() << endl;
        
        cout << externalShaders[i].name << "[";
        cout << externalShaders[i].path << externalShaders[i].vert.getFileName() << ",";
        cout << externalShaders[i].path << externalShaders[i].frag.getFileName() << ",";
        if(externalShaders[i].img.getFileName() != "data"){
            cout << externalShaders[i].path << externalShaders[i].img.getFileName();
        }
        cout << "]" << endl;
    }
    */
    
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
    
    for(int i = 0; i < externalShaders.size(); i++){
        //cout << externalShaders[i].frag.getBaseName() << endl;
        //cout << externalShaders[i].frag.getFileName() << endl;
        //cout << externalShaders[i].frag.getAbsolutePath() << endl;
        //cout << externalShaders[i].vert.getBaseName() << endl;
        //cout << externalShaders[i].vert.getFileName() << endl;
        //cout << externalShaders[i].vert.getAbsolutePath() << endl;
        
        cout << externalShaders[i].name << "[";
        cout << externalShaders[i].path << externalShaders[i].vert.getFileName() << ",";
        cout << externalShaders[i].path << externalShaders[i].frag.getFileName() << ",";
        if(externalShaders[i].img.getFileName() != "data"){
            cout << externalShaders[i].path << externalShaders[i].img.getFileName();
        }
        cout << "]" << endl;
    }
    
}


