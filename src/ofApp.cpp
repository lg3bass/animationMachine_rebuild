#include "ofApp.h"

/*
 * Starter file for Alembic Media Player
 *
 *
 *
 */


#include "ofxAlembic.h"

//--------------------------------------------------------------
void ofApp::setup(){
    appStart = true;
    
    
    //enabled for the kashimShaders
    ofEnableDepthTest();
    ofDisableArbTex();
    testIMG.loadImage("shaders/kashimAstro/img.jpg");
    //end enabled for the kashimShaders
    
    doneBuilding = false;
    
    //turn this on to show lots of output data.
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    // to turn off the [ error ] ofxAlembic::IGeom: cast error.
    ofSetLogLevel(OF_LOG_FATAL_ERROR);
    
    //setup Midi and set input source to (0=IAC, 1=Network Midi)
    setupMidi(0);
    
    //OSC
    myOSC.setup();

    //ON-SCREEN MESSAGING
    current_msg_string = 0;
    
    //SYPHON
    //much nicer than processing's vs.:)
    ofSetWindowTitle("Lights Camera Alembic Syphon");
    mainOutputSyphonServer.setName("Screen Output");
    
 	mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
    //END SYPHON
    
    
    ofBackground(0);

    ofSetFrameRate(60);
    ofEnableAntiAliasing();
    //ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
    ofSetSmoothLighting(true);
    
    glDisable(GL_CULL_FACE);
    
    //used in the buttons at the top.
    currentScene = 1;
    
    //LIGHTS
    myLights = aLights::Instance();
    
    //GUI
    myGui = aGui::Instance();
    myGui->setup(numOfABC);//set the nmber of loader slots
    
    //aTrackGui
    //myTrackGui = aTrackGui::Instance();
    //myTrackGui->setup();
    
    myTrackGui.setup();
    
    myPositionGui.setup();
    myRotationGui.setup();
    myScaleGui.setup();
    
    gui_loader_Alloc = false;
    
    //reset lights and lights gui.
    reset();
    
    saveCam.setup(&cam,"xml"); // add you ofeasycam and the folder where the xmls are
    saveCam.isSettingCam = false;//flag to display the press 'n' to save message.
    
    
}



void ofApp::reset()
{
    //pass through the reset commands.
    myLights->reset();
    myGui->reset();
    //myTrackGui->reset();
    myTrackGui.reset();
    
    //GUI > Position
    myPositionGui.reset();
    myPositionGui.toggleVisibility(false);
    
    //GUI > Rotation
    myRotationGui.reset();
    myRotationGui.toggleVisibility(false);
    
    //GUI > Scale
    myScaleGui.reset();
    myScaleGui.toggleVisibility(false);
    cam.reset();
    
    //set up the default gui_loader
    setGUI_loader(numOfABC);
    
    //set this up to read from the button at the top.
    loadScene(currentScene); //run this on initial setup.
    
    //start with all the gui's turned off
    myGui->gui->setVisible(false);
    myGui->gui2->setVisible(false);
    gui_loader->setVisible(false);
    
    //GUI > materials/shaders
    //myTrackGui->toggleVisibility(false);
    myTrackGui.toggleVisibility(false);

    

}

void ofApp::loadScene(int sceneIndex){
    
    //process the filenames
    string filename = "GUI/gui_loader_Settings_" + ofToString(sceneIndex) + ".xml";
    
    //check if the file exists
    ofFile fileToRead(ofToDataPath(filename));
    if(fileToRead.exists()){
        appStart = false;
        
        addMessage("loading scene "+ofToString(sceneIndex));
        
        //load the settings
        gui_loader->loadSettings(filename);
        
        gui_loader_Alloc = true;
        
        //Load Alembic Models. gather data from gui_loader and load the models.
        setupABCLoaders(numOfABC);
        
        myPositionGui.loadGUI(sceneIndex);
        myScaleGui.loadGUI(sceneIndex);
        myRotationGui.loadGUI(sceneIndex);
        
        doneBuilding = true;
        
    
    } else {
        addMessage("scene "+ofToString(sceneIndex)+" doesn't exist yet");
        if(appStart){
            addMessage("creating new "+ofToString(sceneIndex));
            gui_loader->loadSettings(filename);
            gui_loader_Alloc = true;
            setupABCLoaders(numOfABC);
            
            myPositionGui.loadGUI(sceneIndex);
            myScaleGui.loadGUI(sceneIndex);
            myRotationGui.loadGUI(sceneIndex);
            
            doneBuilding = true;
            appStart = false;
        }
    }
    
    
    
    //set the banks button bar
    ofxUIToggleMatrix *tbanks = (ofxUIToggleMatrix *)gui_loader->getWidget("BANKS");
    vector<ofxUIToggle*> saveTog = tbanks->getToggles();
    saveTog[sceneIndex-1]->setValue(true);

    ofxUILabelToggle *demoMode = (ofxUILabelToggle *)gui_loader->getWidget("DEMO");
    demoMode->setValue(false);
    
}

void ofApp::clearScene(int sceneIndex){
    clearParamsInABCloaders(0,numOfABC);
    myPositionGui.resetGUI(numOfABC, 0,true);
    myScaleGui.resetGUI(numOfABC, 0,true);
    myRotationGui.resetGUI(numOfABC, 0,true);
}


void ofApp::saveScene(int sceneIndex){
    gui_loader_Alloc = false;
    doneBuilding = false;
    
    string filename = "GUI/gui_loader_Settings_" + ofToString(sceneIndex) + ".xml";
    
    gui_loader->saveSettings(filename);
    
    gui_loader_Alloc = true;
    
    myPositionGui.saveGUI(sceneIndex);
    myScaleGui.saveGUI(sceneIndex);
    myRotationGui.saveGUI(sceneIndex);
    
    
    //re-setup loaders and commit changes.
    setupABCLoaders(numOfABC);
    
    doneBuilding = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle("size:"+ofToString(ofGetWidth())+","+ofToString(ofGetHeight())+", port: "+ofToString(midiIn.getPortName(midiIn.getPort()))+", fps: "+ofToString(ofGetFrameRate())+", cam: "+ofToString(saveCam.currentIdx));
    
    //pass update to my singletons
    myTrackGui.update();
    myPositionGui.update();
    myRotationGui.update();
    myScaleGui.update();
    
    //ON-SCREEN MESSAGING
    eraseMessages();
    
    //OSC
    myOSC.newOscMessage();
    //newOscMessage();
    
    //loop through all the abc files and calculate the time in each.
    for(int i = 0; i < abcModels.size(); i++){
        //animTime is passed but not used.
        abcModels[i].calcTime(myGui->animTime);//advances the frames in the alembic files.
        
        abcModels[i].setABCPosition();//sets the position.
        abcModels[i].setABCOrientation();//sets the orientation.
        abcModels[i].setABCScale();

        //abcModels[i].setABCRotate();
        //abcModels[i].setABCMove();
    }
    
    
    if (myGui->doReset)
        reset();
    
    
    //this is the center point around which the light rotates.
    //TO-DO: use this same point as the world space position of the axis.
    ofVec3f center = ofVec3f(0);
    if (myGui->autoRotatePoint) {
        myLights->point.setPosition(cos(ofGetElapsedTimef()*.6f) * myGui->radius * 2 + center.x,sin(ofGetElapsedTimef()*.8f) * myGui->radius * 2 + center.y,-cos(ofGetElapsedTimef()*.8f) * myGui->radius * 2 + center.z);
    }
    
    
    saveCam.update();
    
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    //register the cursor position.
    float dx = dragPt.x;
	float dy = dragPt.y;
    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //added 20140903. Moved from setup
    glEnable(GL_DEPTH_TEST);
    
    if (myGui->cull)
        glEnable(GL_CULL_FACE);
    
    cam.begin();
    
    if (myGui->showAxis){
        //draw x/y/z axis
        ofSetLineWidth(5);
        ofSetColor(255, 0, 0);
        ofLine(0, 0, 200, 0);
        ofSetColor(0, 255, 0);
        ofLine(0, 0, 0, 200);
        ofSetColor(0, 0, 255);
        ofLine(0, 0, 0, 0, 0, 200);
    }
    
    if (myGui->useAmb)
        myLights->amb.enable();
    else
        myLights->amb.disable();
    
    if (myGui->useDir)
        myLights->dir.enable();
    else
        myLights->dir.disable();
    
    if (myGui->useSpot)
        myLights->spot.enable();
    else
        myLights->spot.disable();
    
    if (myGui->usePoint)
        myLights->point.enable();
    else
        myLights->point.disable();
    
    //enabling lights above will call ofEnableLighting() which will
    //enable GL_COLOR_MATERIAL. This which means calls to ofSetColor()
    //would change material properties, which we dont want here. We
    //want it controlled by the sliders, so we turn it off then turn
    //on our material
    glDisable(GL_COLOR_MATERIAL);
    
    
    //THIS IS WHERE THE ANIMATION HAPPENS.
    glPushMatrix();
    
    //Loop through the tracks,specifically the loaders within and shade and materialze.
    for(int t=0;t<tracks.size();t++){
        if(tracks[t].myLdrs.size()>0){
            for(int i=0; i<tracks[t].myLdrs.size();i++){
                
                //t=track. every model gets rendered per track.
                if(myTrackGui.useShaders[t]){
                    myTrackGui.shader_0.begin();
                    
                    //This is how you pass variables into the shader.
                    myTrackGui.shader_0.setUniform4f("diffuseColor", myTrackGui.v4Diffuse[t].x,myTrackGui.v4Diffuse[t].y,myTrackGui.v4Diffuse[t].z,1);
                    myTrackGui.shader_0.setUniform4f("specularColor", myTrackGui.v4Specular[t].x,myTrackGui.v4Specular[t].y,myTrackGui.v4Specular[t].z,1);
                    
                } else {
                    myTrackGui.materials[t].begin();
                }
                
                //shaders only - pass Light direction and ambient color.  same for all.
                myTrackGui.shader_0.setUniform3f("lightDir", 1,1,1);
                myTrackGui.shader_0.setUniform3f("ambientColor", 0.5, 0.5, 0.5);
                
                
                //more shader fun
                myTrackGui.shader_0.setUniformTexture("texture",testIMG,1);
                myTrackGui.shader_0.setUniform1f("time", ofGetElapsedTimef());

                //-------------------------------------------------
                //DRAW TO THE SCREEN
                //=================================================
                if(!showLdr){
                //here is where you're actually drawing the models.
                    if(abcModels[tracks[t].myLdrs[i].x].isActive) {
                        abcModels[tracks[t].myLdrs[i].x].draw();
                    }
                }

                if(myTrackGui.useShaders[t]){
                    myTrackGui.shader_0.end();
                } else {
                    myTrackGui.materials[t].end();
                }
                
            }
            
        }
        
    }

    
    glPopMatrix();
    
    myLights->amb.disable();
    myLights->dir.disable();
    myLights->spot.disable();
    myLights->point.disable();
    
    ofDisableLighting();
    
    if (myGui->useSpot && myGui->showSpotSource) {
        ofSetColor(myLights->spot.getDiffuseColor());
        myLights->spot.draw();
    }
    
    if (myGui->usePoint && myGui->showPointSource) {
        ofSetColor(myLights->point.getDiffuseColor());
        myLights->point.draw();
    }
    
    if (myGui->useDir && myGui->showDirSource) {
        ofSetColor(myLights->dir.getDiffuseColor());
        myLights->dir.draw();
    }
    
    cam.end();
    
    if (myGui->cull)
        glDisable(GL_CULL_FACE);
    
    //added 20140903
    glDisable(GL_DEPTH_TEST);
    
    ofSetColor(255, 255, 255);
    
    ofEnableAlphaBlending();
    
    //Syphon
    mClient.draw(50, 50);
	mainOutputSyphonServer.publishScreen();
    
    
    //saveCam.information();
    
    //Display OSC PORT
    myOSC.draw();
    
    //Display Midi notes, OSC, etc.
    drawMessages();
    
}// end draw


//--------------------------------------------------------------
void ofApp::exit() {
    
	myGui->exit();//save the gui XML
    myTrackGui.exit();
    myPositionGui.exit();
    myRotationGui.exit();
    myScaleGui.exit();
    
	delete gui_loader;
    
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}


//--------------------------------------------------------------
void ofApp::setupABCLoaders(int num) {
    
    myABCs.clear();
    abcModels.clear();
    
    cout << "setupABCLoaders()" << endl;
    
    //Set up all the ABCLoaders.
    for(int i = 0; i < num; i++){
        
        //create abcReader(s)
        ofxAlembic::Reader *newabc = new ofxAlembic::Reader;
        myABCs.push_back(newabc);
        
        //set the play(preview) button off
        ofxUIImageToggle *playBut = (ofxUIImageToggle *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_PLAY");
        playBut->setValue(false);
        
        
        //get the contents of the Text Input field in gui_loader. This contains the file path.
        ofxUITextInput *loader_label = (ofxUITextInput *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_READER");
        
        //add blank abcModels
        abcModels.push_back(abcModel(i)); //QUESTION: Why is the asterick needed on myABCs?
        
        
        //setup the abcModel(s)
        //syntax: init(file,divisions,reader,id)
        abcModels[i].init(loader_label->getTextString(),0,*myABCs[i]);
        
    }
    
    tracks.clear();
    
    //Set up all the Tracks.
    createTracks(num);
    
    //Set the attributes in the loaders based on what is currently loaded in the GUI.
    setParamsInABCloaders(num);
    //myPositionGui.setupGUI(numOfABC);
    
    trackReport();

    
    
}


/*  This function loops through the UI and uses that data
    to create Tracks.  specifically it looks for midi channel, Note, type
*/
//--------------------------------------------------------------
void ofApp::createTracks(int num){
    //var num is not being used right now.
    
    
    //create 10 empty tracks
    for(int t=0;t<10;t++){
        aTrack::aTrack *newTrack = new aTrack::aTrack("empty", false, t);
        tracks.push_back(*newTrack);
    }
    
    //loop through the loader instances and pull the data from the UI.
    for(int i = 0; i < abcModels.size(); i++){
        string behavior = "";
        int midiChannel = 0;
        bool playsOnNote = false;
        
        
        //midi track/channel
        ofxUINumberDialer *midiDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_MIDI");
        midiChannel = floor(midiDialer->getValue());
        
        //note number
        ofxUINumberDialer *noteDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_NOTE");
        int midiNote = noteDialer->getValue();
        if(midiNote > 0) {
            playsOnNote = true;
        } else {
            playsOnNote = false;
        }
        
        //new behavior
        ofxUIToggle *togType = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_random");
        //cout << togType->getValue() << endl;
        if(togType->getValue()){
            behavior = "random";
        } else {
            behavior = "linear";
        }
        
        
        //segments
        ofxUINumberDialer *segDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SEGMENTS");
        int seg = segDialer->getValue();
        
        
        //What loaders are in each track.
        for(int l=0;l<tracks.size();l++){
            if(l+1 == midiChannel){
                if(tracks[l].behavior == "empty"){
                    tracks[l].behavior = behavior;
                    tracks[l].playNote = playsOnNote;
                    tracks[l].segments = seg;
                }
                ofVec2f id;
                id.set(i,midiNote);
                tracks[l].myLdrs.push_back(id);
            }// if
        }// for l
    }//for i
    
}

//--------------------------------------------------------------
void ofApp::setParamsInABCloaders(int num) {
    
    /*
     //params to set
     //public
     float segments;
     float clipSpeedMod;
     float midiChannel;
     float midiNote;
     int ldrType; // 0=random, 1=linear
     int trackMode; // 0=noteOn, 1=noteOn/noteOff
     float segLength;
     int currentSegment;
     
     */
    
    
    // loop through the loaders and set the params.
    for(int i = 0; i < num; i++){
        
        //IMPORTANT: componsate for the Maya cm->m
        abcModels[i].setScale(25.0);
        
        //demo Mode
        abcModels[i].isDemo = false;
        
        ofxUISlider *trackSlider = (ofxUISlider *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SPD");
        trackSlider->setLabelVisible(false);
        float sldr_val = ofMap(trackSlider->getValue(), 0.0, 1.0, 0.00, 0.12);
        abcModels[i].clipSpeedMod = sldr_val;//abcModel.cpp
        
        
        //track midi
        ofxUINumberDialer *midiDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_MIDI");
        abcModels[i].midiChannel = midiDialer->getValue();
        
        //track note
        ofxUINumberDialer *noteDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_NOTE");
        abcModels[i].midiNote = noteDialer->getValue();

        //track type
        ofxUIToggle *togType = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_random");
        if(togType->getValue()){
            abcModels[i].ldrType = 0;
        } else {
            abcModels[i].ldrType = 1;
        }
        
        /*
        //track mode
        ofxUIRadio *butMode = (ofxUIRadio *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_MODE");
        vector<ofxUIToggle*> mode_toggles = butMode->getToggles();
        if(mode_toggles[0]->getValue()) {
            abcModels[i].trackMode = 0;//reporting[1,0] then set "noteOn:0"
        } else {
            abcModels[i].trackMode = 2;
        }
        */
        
        //track mode (NEW)
        setNoteInTrigger(i, "ON");

//        ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_ON");
//        ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_OFF");
//        if(midiOn){
//            if(midiOff){
//                abcModels[i].trackMode = 2;
//            } else {
//                abcModels[i].trackMode = 0;
//            }
//        } else {
//            //midi Off Only
//            abcModels[i].trackMode = 1;
//        }
        
        //segments
        ofxUINumberDialer *segDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SEGMENTS");
        abcModels[i].segments = segDialer->getValue();
        
        //seg len
        ofxUINumberDialer *segLnDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SEGLN");
        abcModels[i].segLength = segLnDialer->getValue();
        
        
        abcModels[i].setClipMarkers(0);
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::clearParamsInABCloaders(int start, int end) {
    
    
    // loop through the loaders and clear the params.
    for(int i = start; i < end; i++){
        
        ofxUITextInput *uitrack = (ofxUITextInput *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_READER");
        uitrack->setTextString("empty");
        
        //track speed
        ofxUISlider *trackSlider = (ofxUISlider *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SPD");
        trackSlider->setValue(0.05);
        
        //set the text dialer.
        //float sldr_val = ofMap(trackSlider->getValue(), 0.0, 1.0, 0.00, 0.12);
        //abcModels[row].clipSpeedMod = sldr_val;//abcModel.cpp
        
        
        
        //track midi
        ofxUINumberDialer *midiDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_MIDI");
        midiDialer->setValue(1);
        
        //track note
        ofxUINumberDialer *noteDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_NOTE");
        noteDialer->setValue(63-i);
        
        //track type
//        ofxUIRadio *butType = (ofxUIRadio *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_TYPE");
//        butType->activateToggle(util::dDigiter(i)+"_random");
        
        ofxUIToggle *togType = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_random");
        togType->setValue(false);
        
        //track mode
//        ofxUIRadio *butMode = (ofxUIRadio *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_MODE");
//        butMode->activateToggle(util::dDigiter(i)+"_ON");
        
        ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_ON");
        midiOn->setValue(true);
        ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(i)+"_OFF");
        midiOff->setValue(true);
        
        //segments
        ofxUINumberDialer *segDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SEGMENTS");
        segDialer->setValue(0);
        
        //seg len
        ofxUINumberDialer *segLnDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_SEGLN");
        segLnDialer->setValue(0);
        
        
        abcModels[i].setClipMarkers(0);
    }
    
}

//--------------------------------------------------------------
void ofApp::resetAnimation(int num){
    // loop through the loaders and move the play head back to the beginning.
    for(int i = 0; i < num; i++){
        
        abcModels[i].currentSegment = -1;
        
    }
}



//MIDI CODE
//--------------------------------------------------------------
void ofApp::setupMidi(int input) {
	// print input ports to console
	// since I escalated the debug level. this is not going to work
    midiIn.listPorts(); // via instance
	
    
    //print out the avail midi ports.
    addMessage("Midi ports:");
    for(int i=0;i<midiIn.getPortList().size();i++){
       addMessage(midiIn.getPortList()[i]);
    }
    
    
	
	// open port by number (you may need to change this)
	midiIn.openPort(input);
	//midiIn.openPort("IAC Driver Bus 1");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(false);
    
}


//--------------------------------------------------------------
void ofApp::toggleMidiPort() {
    
    //test if the existing port is open
    if(midiIn.isOpen()){
        //get the existing port
        int port = midiIn.getPort();
        
        //close the existing port
        midiIn.closePort();
        
        //cycle through and display
        if (port == midiIn.getNumPorts()-1){
            port = 0;
            midiIn.openPort(port);
            addMessage(midiIn.getPortName(port));
        } else {
            port++;
            midiIn.openPort(port);
            addMessage(midiIn.getPortName(port));
            
        }
    }
}


//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    
    //trigger animation
    noteIn();
}

//--------------------------------------------------------------
void ofApp::setNoteInTrigger(int row, string _clicked) {
    ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(row)+"_ON");
    ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(row)+"_OFF");
    
    if((midiOn->getValue() == true) && (midiOff->getValue() == false)){
        abcModels[row].trackMode = 0;
    }
    
    if((midiOn->getValue() == false) && (midiOff->getValue() == true)){
        abcModels[row].trackMode = 1;
    }

    if((midiOn->getValue() == true) && (midiOff->getValue() == true)){
        abcModels[row].trackMode = 2;
    }
    
    if((midiOn->getValue() == false) && (midiOff->getValue() == false)){
        abcModels[row].trackMode = 3;
    }
}

//--------------------------------------------------------------
void ofApp::noteIn() {
    
    if (ofxMidiMessage::getStatusString(midiMessage.status) == "Note On") {
        
        bool specificNote = false;
        int currentPlayingIndex = 0;
        
        //cout << ofxMidiMessage::getStatusString(midiMessage.status) << " -- value:" << midiMessage.value << " pitch: " << midiMessage.pitch << " delta: " << midiMessage.deltatime << " ch: " << midiMessage.channel << endl;
        
        string msg_string;
        msg_string += "MIDI-IN: ";
        msg_string += ofToString(midiMessage.pitch);
        
        addMessage(msg_string);
        
        
        //make sure the track is not empty. Does the track have content.
        if(tracks[midiMessage.channel-1].myLdrs.size()>0){
            
            //loop through the loader and look for one that has a specific note.
            for(int i=0; i<tracks[midiMessage.channel-1].myLdrs.size();i++) {
                if(tracks[midiMessage.channel-1].myLdrs[i].y > 0){
                    //play the specific note
                    if(midiMessage.pitch == tracks[midiMessage.channel-1].myLdrs[i].y) {
                        currentPlayingIndex = tracks[midiMessage.channel-1].myLdrs[i].x;
                        if(tracks[midiMessage.channel-1].behavior == "random"){
                            abcModels[currentPlayingIndex].playSegment(0);
                        } else {
                            abcModels[currentPlayingIndex].playSegment(1);
                        }
                        //flag the loader as tied to a specific note.
                        specificNote = true;
                    }
                }
            }//end for
            
            if(!specificNote) {
                //exclude the tracks that are assigned to a specific note.
                int availLdrs = 0;
                for(int j=0; j<tracks[midiMessage.channel-1].myLdrs.size();j++){
                    
                    if(tracks[midiMessage.channel-1].myLdrs[j].y == 0 ){
                        if(!abcModels[tracks[midiMessage.channel-1].myLdrs[j].x].isAnimating) {
                            availLdrs++;
                        }
                    }
                }
                
                
                // check if there are any loaders avail. if not dont play.
                if(availLdrs > 0) {
                    //RANDOM
                    if(tracks[midiMessage.channel-1].behavior == "random"){
                        do {
                            currentPlayingIndex = pickRandomLoader(midiMessage.channel-1);//pickRandomLoader: applicable for linear mode???
                        } while (abcModels[currentPlayingIndex].isAnimating);
                        
                        //PLAY THE MODEL IN RANDOM MODE
                        abcModels[currentPlayingIndex].playSegment(0);//0 = play random
                        
                    }
                    //LINEAR
                    if(tracks[midiMessage.channel-1].behavior == "linear") {
                        for(int i=0; i<tracks[midiMessage.channel-1].myLdrs.size();i++) {
                            if(!abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].isAnimating) {
                                currentPlayingIndex = tracks[midiMessage.channel-1].myLdrs[i].x;
                                abcModels[currentPlayingIndex].playSegment(1); //1 = play linear.
                            }
                        }
                    }//end linear
                }//end availLdrs
            }//if NOT specificNote
            
        }//if has content.
        
        
        
    } else if (ofxMidiMessage::getStatusString(midiMessage.status) == "Note Off"){
        
        //cout << ofxMidiMessage::getStatusString(midiMessage.status) << " -- value:" << midiMessage.value << " pitch: " << midiMessage.pitch << " delta: " << midiMessage.deltatime << " ch: " << midiMessage.channel << endl;
        

        
        //make sure the track is not empty. Does the track have content.
        if(tracks[midiMessage.channel-1].myLdrs.size()>0){
            
            //loop through the loaders.
            for(int i=0; i<tracks[midiMessage.channel-1].myLdrs.size();i++) {
                
                //logic: there should only be one that is animating at a time in the track. Is the loader Animating?
                if(abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].isAnimating) {
                    
                    //if it is animating, match against which midi note is playing.
                    if(tracks[midiMessage.channel-1].myLdrs[i].y == midiMessage.pitch){
                        
                        //only actually do this if the trackMode is 1.
                        //reminder: trackMode = NoteOn or NoteOff enabled.
                        //trackMode 0 = animate on noteOn ONLY.
                        //trackMode 1 = animate on noteOff ONLY.
                        //trackMode 2 = animate noteOn then finish animating on noteOff message.
                        if(abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].trackMode == 1) {
                            
                            //release the hold onthe animation on note off message.
                            abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].isHolding = false;
                        
                        }
                        if(abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].trackMode == 2) {
                            
                            //you're no longer animating( playing abc frames)
                            abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].isAnimating = false;
                            abcModels[tracks[midiMessage.channel-1].myLdrs[i].x].isHolding = true;
                            
                            
                        }//end if trackMode
                    }//end match against midi note.
                    
                    
                }//end if animating
            }//end for
        }//end if midiChannel
    
    
    
    
    }//end elseIf
    
    
}

//-------------------------------------------------------------
int ofApp::pickRandomLoader(int ch){
    
    int selector = 0;
    //pick a random loader within the track.
    
    do{
        selector = ofRandom(tracks[ch].myLdrs.size());
    } while (tracks[ch].myLdrs[selector].y > 0);
    
    
    int abc_index = tracks[ch].myLdrs[selector].x;
    
    
    
    
    //output: Show what is selected to play
    //tracks[ch].whatIsPlaying(selector);
    
    return abc_index;
    
}


//--------------------------------------------------------------
void ofApp::LoaderGuiEvent(ofxUIEventArgs &e)
{
    
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    //get the track number from the name.
    vector<string> result=ofSplitString(name, "_");
    int row = ofToInt(result[0]);
    //selectedLoaderRow = row;//not used
    
    
    if(doneBuilding){ //only if the loaders are done.
        
        //if current row eq last selected row on file then
        
        if(ofIsStringInString(name, "CLEAR")){
            ofxUILabelButton *clearBut = (ofxUILabelButton *)gui_loader->getWidget("CLEAR");
            if(clearBut->getValue()){
                cout << "Clear Scene: " << currentScene << endl;
                clearScene(currentScene);
            }
        } else if (ofIsStringInString(name, "LOAD")){
            ofxUILabelButton *loadBut = (ofxUILabelButton *)gui_loader->getWidget("LOAD");
            if(loadBut->getValue()){
                cout << "load Scene: " << currentScene << endl;
                loadScene(currentScene);
            }
        } else if (ofIsStringInString(name, "SAVE")){
            ofxUILabelButton *saveBut = (ofxUILabelButton *)gui_loader->getWidget("SAVE");
            if(saveBut->getValue()){
                cout << "save Scene: " << currentScene << endl;
                saveScene(currentScene);
            }
        } else if (ofIsStringInString(name, "BANKS")){
            ofxUIToggleMatrix *tbanks = (ofxUIToggleMatrix *)gui_loader->getWidget("BANKS");
            vector<ofxUIToggle*> saveTog = tbanks->getToggles();
            for(int i=0; i<saveTog.size();i++){
                if(saveTog[i]->getValue() == 1){
                    //ofxUISetColor(ofColor::red);
                    currentScene = i+1;
                    
                    cout << "currentScene:" << currentScene << endl;
                    
                }
                
            }
        } else if (ofIsStringInString(name, "TRK_PLAY")){
            ofxUIImageToggle *playBut = (ofxUIImageToggle *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_PLAY");
            
            if(playBut->getValue() == 1){
                abcModels[row].isDemo = true;
            }
            if(playBut->getValue() == 0){
                abcModels[row].isDemo = false;
            }
            
            cout << util::dDigiter(row) << "_TRK_PLAY" << ":ofxUIImageToggle (Play Button Toggle) >" << playBut->getValue() << endl;
        } else if (ofIsStringInString(name, "TRK_CLR")){
           
            ofxUIImageButton *clearBut = (ofxUIImageButton *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_CLR");
            if(clearBut->getValue()){
                cout << util::dDigiter(row) << "_TRK_CLR" << clearBut->getValue() << endl;
                clearParamsInABCloaders(row,row+1);
            
            }
            
            
        
        } else if(ofIsStringInString(name, "TRK_SPD")){
            ofxUISlider *trackSlider = (ofxUISlider *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_SPD");
            
            //set the text dialer.
            float sldr_val = ofMap(trackSlider->getValue(), 0.0, 1.0, 0.00, 0.12);
            abcModels[row].clipSpeedMod = sldr_val;//abcModel.cpp
            cout << util::dDigiter(row) << "_TRK_SPD" << ":ofxUISlider (Clip speed modifier) >" << ofToString(sldr_val) << endl;
         
        } else if (ofIsStringInString(name, "TRK_MIDI")){
            ofxUINumberDialer *midiDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_MIDI");
            abcModels[row].midiChannel = midiDialer->getValue();
            cout << util::dDigiter(row) << "_TRK_MIDI" << ":ofxUINumberDialer (Midi Channel/Track) >" << midiDialer->getValue() << endl;
            
        } else if (ofIsStringInString(name, "TRK_NOTE")){
            ofxUINumberDialer *noteDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_NOTE");
            abcModels[row].midiNote = noteDialer->getValue();
            if(noteDialer->getValue() > 0){
                tracks[abcModels[row].midiChannel-1].playNote = true;
            } else {
                tracks[abcModels[row].midiChannel-1].playNote = false;
            }
            
            cout << util::dDigiter(row) << "_TRK_NOTE" << ":ofxUINumberDialer (Midi Note Number) >" << noteDialer->getValue() << endl;
            
        } else if (ofIsStringInString(name, "random")){
            ofxUIToggle *randseq = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(row)+"_random");
            cout << util::dDigiter(row) << "_random" << ":ofxUIToggle (random/sequence) >" << randseq->getValue() << endl;
            if(randseq->getValue()) {
                abcModels[row].ldrType = 0;
                tracks[abcModels[row].midiChannel-1].behavior = "random";
            } else {
                abcModels[row].ldrType = 1;
                tracks[abcModels[row].midiChannel-1].behavior = "linear";
            }
            
        // New Midi
        
        } else if (ofIsStringInString(name, "ON")){
            setNoteInTrigger(row,"ON");
            cout << "trackMode is now " << ofToString(abcModels[row].trackMode) << endl;
        } else if (ofIsStringInString(name, "OFF")){
            setNoteInTrigger(row,"OFF");
            cout << "trackMode is now " << ofToString(abcModels[row].trackMode) << endl;
        } else if (ofIsStringInString(name, "TRK_SEGMENTS")){
            ofxUINumberDialer *segDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_SEGMENTS");
            abcModels[row].segments = segDialer->getValue();
            tracks[abcModels[row].midiChannel-1].segments = segDialer->getValue();
            cout << util::dDigiter(row) << "_TRK_NOTE" << ":ofxUINumberDialer (ABC sections) >" << segDialer->getValue() << endl;
        } else if (ofIsStringInString(name, "TRK_SEGLN")){
            ofxUINumberDialer *segLnDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(row)+"_TRK_SEGLN");
            abcModels[row].segLength = segLnDialer->getValue();
            cout << util::dDigiter(row) << "_TRK_SEGLN" << ":ofxUINumberDialer (ABC segment length[time]) >" << segLnDialer->getValue() << endl;
        } else if (ofIsStringInString(name, "DEMO")){
            ofxUILabelToggle *demoMode = (ofxUILabelToggle *)gui_loader->getWidget("DEMO");
            cout << "DEMO MODE:" << demoMode->getValue() << endl;
            toggleDemoMode(demoMode->getValue(), row);
        }
    }
}

void ofApp::setGUI_loader(int num){
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float w = 1100 - xInit * 2;
    float vertH = 40;
    float h = 8;
    
    if (gui_loader_Alloc) {
        ofRemoveListener(gui_loader->newGUIEvent, this, &ofApp::LoaderGuiEvent);
        delete gui_loader;
    }
    
    gui_loader = new ofxUICanvas(0, 0, w + xInit * 2, ofGetHeight());
    gui_loader->setFont("GUI/HelveticaNeueLTStd-Bd.otf");
    gui_loader->setFontSize(OFX_UI_FONT_SMALL, 5);
    
    
    gui_loader->addWidgetRight(new ofxUILabelButton(50,false,"CLEAR",OFX_UI_FONT_SMALL));
    gui_loader->addWidgetRight(new ofxUILabelButton(50,false,"LOAD",OFX_UI_FONT_SMALL));
    gui_loader->addWidgetRight(new ofxUILabelButton(50,false,"SAVE",OFX_UI_FONT_SMALL));
    gui_loader->addWidgetRight(new ofxUIToggleMatrix(18,18,1,6,"BANKS",OFX_UI_FONT_SMALL));
    ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *) gui_loader->getWidget("BANKS");
    mtx->setAllowMultiple(false);
    
    
    gui_loader->addSpacer(240,2);
    
    for(int i = 0; i < num; i++)
    {
        string counter = util::dDigiter(i);
        
        
        gui_loader->addWidgetDown(new ofxUIImageToggle(20,20,false,"GUI/play.png",util::dDigiter(i)+"_TRK_PLAY"));
        gui_loader->addWidgetRight(new ofxUIImageButton(20,20,false,"GUI/clear.png",util::dDigiter(i)+"_TRK_CLR"));
        gui_loader->addWidgetRight(new ofxUITextInput(310, util::dDigiter(i)+"_TRK_READER", "empty", OFX_UI_FONT_SMALL));
        
        gui_loader->addWidgetRight(new ofxUISlider(util::dDigiter(i)+"_TRK_SPD", 0.00f, 0.12f, 0.05, 100, 18));
        
        gui_loader->addWidgetRight(new ofxUINumberDialer(1, 10, 1, 0, util::dDigiter(i)+"_TRK_MIDI", OFX_UI_FONT_SMALL));
        gui_loader->addWidgetRight(new ofxUINumberDialer(0, 88, 63-i, 0, util::dDigiter(i)+"_TRK_NOTE", OFX_UI_FONT_SMALL));
    
        
        //Play mode (random/sequence)
        gui_loader->addWidgetRight(new ofxUIToggle(util::dDigiter(i)+"_random",false,20,20));
        
        //Midi Trigger
        gui_loader->addWidgetRight(new ofxUIToggle(util::dDigiter(i)+"_ON",true,20,20));
        gui_loader->addWidgetRight(new ofxUIToggle(util::dDigiter(i)+"_OFF",true,20,20));
        
        //File segments
        gui_loader->addWidgetRight(new ofxUINumberDialer(1, 50, 1.0, 0,util::dDigiter(i)+"_TRK_SEGMENTS", OFX_UI_FONT_SMALL));
        gui_loader->addWidgetRight(new ofxUINumberDialer(0, 600, 30, 0,util::dDigiter(i)+"_TRK_SEGLN", OFX_UI_FONT_SMALL));
        
        
    }
    // show all the active loaders
    gui_loader->addWidgetDown(new ofxUILabelToggle(50,false,"DEMO",OFX_UI_FONT_SMALL));
    
    // set the labels over the top row
    gui_loader->addWidgetNorthOf(new ofxUISpacer(55,2,"speed_spacer"),"00_TRK_SPEED");
    gui_loader->addWidgetNorthOf(new ofxUILabel("SPEED",OFX_UI_FONT_SMALL),"speed_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(30,2,"midi_spacer"),"00_TRK_MIDI");
    gui_loader->addWidgetNorthOf(new ofxUILabel("MIDI",OFX_UI_FONT_SMALL),"midi_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(30,2,"note_spacer"),"00_TRK_NOTE");
    gui_loader->addWidgetNorthOf(new ofxUILabel("NOTE",OFX_UI_FONT_SMALL),"note_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(120,2,"type_spacer"),"00_random");
    gui_loader->addWidgetNorthOf(new ofxUILabel("RANDOM",OFX_UI_FONT_SMALL),"type_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(120,2,"mode_spacer"),"00_ON");
    gui_loader->addWidgetNorthOf(new ofxUILabel("NOTE ON/OFF",OFX_UI_FONT_SMALL),"mode_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(30,2,"seg_spacer"),"00_TRK_SEGMENTS");
    gui_loader->addWidgetNorthOf(new ofxUILabel("SEG",OFX_UI_FONT_SMALL),"seg_spacer");
    
    gui_loader->addWidgetNorthOf(new ofxUISpacer(30,2,"segln_spacer"),"00_TRK_SEGLN");
    gui_loader->addWidgetNorthOf(new ofxUILabel("FRM",OFX_UI_FONT_SMALL),"segln_spacer");
    
    gui_loader->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(120,200));
    
    ofAddListener(gui_loader->newGUIEvent, this, &ofApp::LoaderGuiEvent);
    
}

//--------------------------------------------------------------
void ofApp::toggleDemoMode(int _ToggleBut, int _loaderRow){
    for(int i=0; i<numOfABC;i++){
        ofxUIImageToggle *playBut = (ofxUIImageToggle *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_PLAY");
        if(abcModels[i].isActive){
            if(_ToggleBut == 0){
                playBut->setValue(false);
                abcModels[i].isDemo = false;
            } else if (_ToggleBut == 1){
                playBut->setValue(true);
                abcModels[i].isDemo = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	if(key & OF_KEY_MODIFIER){
		if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            cout << "F KEY:" << key << endl;
        }else{
            
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    cout << "Left Apple Pressed" << endl;
                    modkey = true;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Pressed" << endl;
                    modkey = true;
                    break;
            }
		}
	}else{
        switch (key) {
            case ' ':
                myGui->wModActive = true;
                cout << "space out" << endl;
                //move this somewhere else.
                resetAnimation(numOfABC);
                break;
            case 'a':
                if(modkey) {
                    myGui->showAxis = !myGui->showAxis;
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material11.frag");
                }
                break;
            case '1':
                if(modkey) loadScene(1);
                break;
            case '2':
                if(modkey) loadScene(2);
                break;
            case '3':
                if(modkey) loadScene(3);
                break;
            case '4':
                if(modkey) loadScene(4);
                break;
            case '5':
                if(modkey) loadScene(5);
                break;
            case '6':
                if(modkey) loadScene(6);
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            case 'l':
                //loader screens
                if(modkey) {
                    cout << "l key pressed" << endl;
                    gui_loader->toggleVisible();
                    showLdr = !showLdr;
                    if(showLights) {
                        myGui->gui->toggleVisible();
                        myGui->gui2->toggleVisible();
                        showLights = false;
                    }
                    if(showTrack) {
                        //myTrackGui->TRK_gui_1->toggleVisible();
                        myTrackGui.toggleVisibility();
                        showTrack = false;
                    }
                    if(showPos) {
                        myPositionGui.toggleVisibility();
                        showPos = false;
                    }
                    if(showRot) {
                        myRotationGui.toggleVisibility();
                        showRot = false;
                    }
                    if(showScale) {
                        myScaleGui.toggleVisibility();
                        showScale = false;
                    }
                }
                break;
            case 'g':
                //gui screens
                if(modkey){
                    myGui->gui->toggleVisible();
                    myGui->gui2->toggleVisible();
                    showLights = !showLights;
                    if(showLdr) {
                        gui_loader->toggleVisible();
                        showLdr = false;
                    }
                    if(showTrack){
                        //myTrackGui->TRK_gui_1->toggleVisible();
                        myTrackGui.toggleVisibility();
                        showTrack = false;
                    }
                    if(showPos) {
                        myPositionGui.toggleVisibility();
                        showPos = false;
                    }
                    if(showRot) {
                        myRotationGui.toggleVisibility();
                        showRot = false;
                    }
                    if(showScale) {
                        myScaleGui.toggleVisibility();
                        showScale = false;
                    }
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material15.frag");
                }
                break;
            case 'm'://CTRL+M is minimize
                //midi port
                toggleMidiPort();
                break;
            case 't':
                //gui screens
                if(modkey){
                    //myTrackGui->TRK_gui_1->toggleVisible();
                    myTrackGui.toggleVisibility();
                    showTrack = !showTrack;
                    if(showLdr) {
                        gui_loader->toggleVisible();
                        showLdr = false;
                    }
                    if(showLights) {
                        myGui->gui->toggleVisible();
                        myGui->gui2->toggleVisible();
                        showLights = false;
                    }
                    if(showPos) {
                        myPositionGui.toggleVisibility();
                        showPos = false;
                    }
                    if(showRot) {
                        myRotationGui.toggleVisibility();
                        showRot = false;
                    }
                    if(showScale) {
                        myScaleGui.toggleVisibility();
                        showScale = false;
                    }
                } else {
                     myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material4.frag");
                }
                break;
            case 'o':
                if(modkey) {
                    if(currentScene < 6){
                        currentScene+=1;
                    } else {
                        currentScene = 1;
                    }
                    cout << "cycle loadScene: "<< currentScene << endl;
                    
                    loadScene(currentScene);
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material9.frag");
                    
                }
                
                break;
            
            case '[':
                if(modkey) saveCam.prevView(4.0);
                break;
            case ']':
                if(modkey) saveCam.nextView(4.0);
                break;
            case 's':
                if(modkey) {
                    saveCam.updateView(-1);//-1= current view
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material12.frag");
                }
                break;
            case 'n':
                if(modkey) saveCam.newView();
                break;
            case 'z':
                if(modkey) saveCam.zeroView();
                break;
            case 'h'://CTRL+h is hide
                
                addMessage("+===========HELP===========+");
                addMessage("SPACE - resetAnimation()");
                addMessage("CTRL+a - show axis");
                addMessage("CTRL+l - loader GUI");
                addMessage("CTRL+g - Lights GUI");
                addMessage("CTRL+w - Position GUI");
                addMessage("CTRL+e - Scale GUI");
                addMessage("CTRL+r - Rotate GUI");
                addMessage("CTRL+t - Mat/Shader GUI");
                
                addMessage("m - cycle MIDI port");
                addMessage("CTRL+o - cycle load scene");
                addMessage("CTRL+1-6 - load select scene");
                addMessage("CTRL+[] - prev/next camera");
                addMessage("CTRL+s - save Camera");
                addMessage("CTRL+n - new Camera View");
                addMessage("CTRL+z - ZERO Camera View");
                addMessage("h - help");
                
                addMessage("");
                addMessage("CTRL+m - Minimize App");
                addMessage("CTRL+h - Hide App");
                addMessage("CTRL+Q/ESC - Quit App");
                addMessage("+===========++++===========+");
                
                break;
            case 'q':
                myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material.frag");
                break;           
            case 'w':
                //TRANSLATE
                if(modkey){
                    myPositionGui.toggleVisibility();
                    showPos = !showPos;
                    if(showLdr) {
                        gui_loader->toggleVisible();
                        showLdr = false;
                    }
                    if(showLights) {
                        myGui->gui->toggleVisible();
                        myGui->gui2->toggleVisible();
                        showLights = false;
                    }
                    if(showTrack) {
                        myTrackGui.toggleVisibility();
                        showTrack = false;
                    }
                    if(showRot) {
                        myRotationGui.toggleVisibility();
                        showRot = false;
                    }
                    if(showScale) {
                        myScaleGui.toggleVisibility();
                        showScale = false;
                    }
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material1.frag");
                }
                break;
            case 'r':
                //ROTATE
                if(modkey){
                    myRotationGui.toggleVisibility();
                    showRot = !showRot;
                    if(showLdr) {
                        gui_loader->toggleVisible();
                        showLdr = false;
                    }
                    if(showLights) {
                        myGui->gui->toggleVisible();
                        myGui->gui2->toggleVisible();
                        showLights = false;
                    }
                    if(showTrack) {
                        myTrackGui.toggleVisibility();
                        showTrack = false;
                    }
                    if(showPos) {
                        myPositionGui.toggleVisibility();
                        showPos = false;
                    }
                    if(showScale) {
                        myScaleGui.toggleVisibility();
                        showScale = false;
                    }
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material2.frag");
                }
                break;
            case 'e':
                //SCALE
                if(modkey){
                    myScaleGui.toggleVisibility();
                    showScale = !showScale;
                    if(showLdr) {
                        gui_loader->toggleVisible();
                        showLdr = false;
                    }
                    if(showLights) {
                        myGui->gui->toggleVisible();
                        myGui->gui2->toggleVisible();
                        showLights = false;
                    }
                    if(showTrack) {
                        myTrackGui.toggleVisibility();
                        showTrack = false;
                    }
                    if(showPos) {
                        myPositionGui.toggleVisibility();
                        showPos = false;
                    }
                    if(showRot) {
                        myRotationGui.toggleVisibility();
                        showRot = false;
                    }
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material3.frag");
                }
                break;
            case 'y':
                myTrackGui.shader_0.load("shaders/kashimAstro/aterial.vert","shaders/kashimAstro/material6.frag");
                break;
            case 'u':
                myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material7.frag");
                break;
            case 'i':
                myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material8.frag");
                break;
            case 'p':
                //positioning
                myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material10.frag");
                break;
            case 'd':
                if(modkey){
                    ofxUILabelToggle *demoMode = (ofxUILabelToggle *)gui_loader->getWidget("DEMO");
                    if(demoMode->getValue()){
                        demoMode->setValue(false);
                        
                    } else {
                        demoMode->setValue(true);
                    }
                    cout << "DEMO MODE NOW:" << demoMode->getValue() << endl;
                    toggleDemoMode(demoMode->getValue(), 0);
                } else {
                    myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material13.frag");
                }
                break;
            case 'f':
                myTrackGui.shader_0.load("shaders/kashimAstro/material.vert","shaders/kashimAstro/material14.frag");
                break;
            case 'j':
                myTrackGui.shader_0.load("shaders/phong/shader.vert","shaders/kashimAstro/shader.frag");
                break;
            default:
                break;
        }
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key & OF_KEY_MODIFIER){
		if(key >= OF_KEY_F1 && key <= OF_KEY_F12){
            // if the f keys are pressed.
            
        }else{
            switch(key){
                case OF_KEY_LEFT_SUPER:
                    cout << "Left Apple Released" << endl;
                    modkey = false;
                    break;
                case OF_KEY_RIGHT_SUPER:
                    cout << "Right Apple Released" << endl;
                    modkey = false;
                    break;
            }
        }
    }else{
        if (key == ' '){
            myGui->wModActive = false;
            myTrackGui.wModActive = false;
        }

    }
    
    
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    saveCam.isSettingCam = true;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if (myGui->gui->isHit(x, y)) {
        cam.disableMouseInput();
    }
    if (myGui->gui2->isHit(x, y)) {
        cam.disableMouseInput();
    }
    if (gui_loader->isHit(x,y)) {
        cam.disableMouseInput();
    }
    if (myTrackGui.TRK_gui_1->isHit(x,y)) {
        cam.disableMouseInput();
    }
    if (myPositionGui.Position_gui_1->isHit(x,y)){
        cam.disableMouseInput();
    }
    if (myRotationGui.Rotation_gui_1->isHit(x,y)){
        cam.disableMouseInput();
    }
    if (myScaleGui.Scale_gui_1->isHit(x,y)){
        cam.disableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cam.enableMouseInput();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::drawMessages() {
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 1050, 22 + 15 * i);
	}
}

//--------------------------------------------------------------
void ofApp::eraseMessages() {
    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
}

//--------------------------------------------------------------
void ofApp::addMessage(string msg) {
    
    if(msg == "+===========HELP===========+"){
        current_msg_string = 0;//print at the top.
    }
    
    msg_strings[current_msg_string] = msg;
    timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}


//--------------------------------------------------------------
void ofApp::trackReport() {
    // OUTPUT/TRACE
    //proof is in the pudding. output what we go so far.
    cout << "TRACKS:" << "-----------------------------" << endl;
    
    for(int t=0;t<tracks.size();t++){
        if(tracks[t].myLdrs.size()>0){
            tracks[t].getInfo();
        }
        for(int i=0; i<tracks[t].myLdrs.size();i++){
            abcModels[tracks[t].myLdrs[i].x].INFOlaunchingToPlay();
        }
    }
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo info){
	if( info.files.size() > 0 ){
        
        string abcFile = "";
        dragPt = info.position;
		
        //pass in the path of the drag object
        ofDirectory dir(info.files[0]);

        if(dir.isDirectory()){
            dir.allowExt("abc");
            dir.listDir();
            
            //go through and print out all the paths
            for(int i = 0; i < dir.numFiles(); i++){
                abcFile = processAbcPath(dir.getPath(i),i);
                cout << "DIRECTORY>processing:" << abcFile << endl;
            }
        } else {
            for(int i = 0; i < info.files.size(); i++){
                abcFile = processAbcPath(info.files[i], i);
                cout << "FILE>processing:" << abcFile << endl;
            }
            
        }//end dragEvent|if|if
	}// end dragEvent|if
}//end dragEvent()


//--------------------------------------------------------------
string ofApp::processAbcPath(string _filename, int _index){

    vector<string> paths = ofSplitString(_filename, "/");
    bool isABC = false;
    string abcFile;
    
    //loop through the path items till the file.
    for(int i=0; i<paths.size()-1;i++){
        //if "abc" is in the filepath
        if(paths[i] == "abc") {
            isABC = true;
            abcFile += paths[i] + "/";
        } else {
            if(isABC){
                abcFile += paths[i] + "/";
            } else {
                //cout << "select an alembic file within the data/abc/ directory." << endl;
            }
        }
    } //  end for
    //add file at the end.
    if(isABC){
        abcFile += paths[paths.size()-1];
    }

    //Which loader text field did you drop on
    for(int i = 0; i < numOfABC; i++){
        
        //get an temporary pointer to the text field
        ofxUITextInput *text1 = (ofxUITextInput *)gui_loader->getWidget(util::dDigiter(i)+"_TRK_READER");
        ofxUIRectangle *rect2 = text1->getRect();
        
        // is the drop point within the text field
        if(rect2->inside(dragPt)){
            if(i+_index < numOfABC){
                text1 = (ofxUITextInput *)gui_loader->getWidget(util::dDigiter(i+_index)+"_TRK_READER");
                
                if(isABC){
                    cout << "dropped inside " << util::dDigiter(i) << "_TRK_READER" << endl;
                    text1->setTextString(abcFile);
                    
                    //process the audio filename
                    processAbcFileName(paths[paths.size()-1], i+_index);
                    
                } else {
                    //cout << "watch where you're dropping!" << endl;
                }
            }
        }
        
    }//end dragEvent|if|for
    
    return abcFile;
}



//--------------------------------------------------------------
void ofApp::processAbcFileName(string _filename, int _index){
    cout << "filename:" << _filename << endl;
    vector<string> fileNoExt = ofSplitString(_filename, ".");
    vector<string> fileParts = ofSplitString(fileNoExt[0], "_");
    
    
    cout << "frames: " << fileParts[fileParts.size()-1] << endl;
    cout << "segments: " << fileParts[fileParts.size()-2] << endl;
    cout << "prefix:" << fileParts[fileParts.size()-3] << endl;
    
    string abcLength = fileParts[fileParts.size()-1];
    string abcMode = fileParts[fileParts.size()-2];
    string abcPrefix = fileParts[fileParts.size()-3];
    
    //segments and frames
    vector<string> abcLength_split = ofSplitString(abcLength, "-");
    float _segLength = ofToFloat(abcLength_split[1]);
    float _segments = ofToFloat(abcLength_split[0]);
    
    //segments
    ofxUINumberDialer *segDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(_index)+"_TRK_SEGMENTS");
    segDialer->setValue(_segments);
    abcModels[_index].segLength = _segments;
    
    //seg len
    ofxUINumberDialer *segLnDialer = (ofxUINumberDialer *)gui_loader->getWidget(util::dDigiter(_index)+"_TRK_SEGLN");
    segLnDialer->setValue(_segLength);
    abcModels[_index].segments = _segLength;
    
    if(ofIsStringInString(abcMode, "s")){
        //sequence
        ofxUIToggle *togType = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_random");
        togType->setValue(false);
        abcModels[_index].ldrType = 1;
    } else if (ofIsStringInString(abcMode, "r")){
        //random
        ofxUIToggle *togType = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_random");
        togType->setValue(true);
        abcModels[_index].ldrType = 0;
    }
    
    if (ofIsStringInString(abcMode, "n0")){
        ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_ON");
        midiOn->setValue(true);
        ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_OFF");
        midiOff->setValue(false);
        abcModels[_index].trackMode = 0;
    } else if (ofIsStringInString(abcMode, "n1")){
        ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_ON");
        midiOn->setValue(false);
        ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_OFF");
        midiOff->setValue(true);
        abcModels[_index].trackMode = 1;
    } else if (ofIsStringInString(abcMode, "n2")){
        ofxUIToggle *midiOn = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_ON");
        midiOn->setValue(true);
        ofxUIToggle *midiOff = (ofxUIToggle *)gui_loader->getWidget(util::dDigiter(_index)+"_OFF");
        midiOff->setValue(true);
        abcModels[_index].trackMode = 2;
    }
    
    
} // end processAbcFileName()


