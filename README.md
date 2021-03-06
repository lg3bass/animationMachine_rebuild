Animation Machine (rebuild)
==================
Latest Update: 2014-06-21
* synced old changes from local

Latest Update: 2014-05-20
* Fixed UI overlap
* Added Help (h)
* Started ofxUISlider implementation to control speed(buggy) 

Update: 2014-05-18
* Updated to ofApp
* add code to raise the ofLogLevel. 

Update: 2014-03-05
* Added OSC support (not connected to CameraMove yet!)
* Added Camera Move


Description
--------------

Open Frameworks project to play Alembic(.abc) files in sync with incoming Midi.  

*No .abc files are included in this project yet.  I'll package in some samples shortly.

1. Command+G to view the Materials and Lights GUI

2. Command+L to view the .abc Loader GUI. Drag and drop data/abc/.abc files into the text area. Click "load".

3. Command+(1-6) to load different scenes (the 6 square radio buttons at the top). 

4. ',' or '.' Previous and Next saved camera position, 'n' new camera, 's' save camera.

Compiling
=================

Addons
----------------
* ofxAlembic (use mine: https://github.com/perfume-dev/ofxAlembic)
* ofxSyphon
* ofxXmlSettings
* ofxUI
* ofxMidi
* ofxCameraMove (use mine: https://github.com/lg3bass/ofxCameraMove)
* ofxTweener (for ofxCameraMove)
* ofxOsc

Header Search Paths
--------------------
* ../../../addons/ofxAlembic/libs/alembic/include
* ../../../addons/ofxAlembic/libs/alembic/include/OpenEXR
* ../../../addons/ofxMidi/src
* ../../../addons/ofxMidi/libs/rtmidi
* ../../../addons/ofxOsc/libs
* ../../../addons/ofxOsc/libs/oscpack
* ../../../addons/ofxOsc/libs/oscpack/src
* ../../../addons/ofxOsc/libs/oscpack/src/ip
../../../addons/ofxOsc/libs/oscpack/src/ip/posix
../../../addons/ofxOsc/libs/oscpack/src/ip/win32
../../../addons/ofxOsc/libs/oscpack/src/osc
../../../addons/ofxOsc/src

<TARGET> Build Phases > Copy files
---------------------
GLUT.framework
Syphon.framework


.abc files (data/abc/<myabcfile>.abc)
-----------------

These can be kinda large.  I'll post these somewhere else or include a sampling of .abc file to get started.  I use Maya 2014 to export Alembic.  Exporting normals is tricky and most often involves hardening Normals before output.  OF doesn't seem like soft normals. 

Basic Description
-----------------

.abc files can be played in two modes (TYPE):

<dl>
<dt>Random</dt>
<dd>If you have a number of loaders on the same midi channel each incoming midi note will pick a random loader.</dd>
<dt>Sequence</dt>
<dd>The loaded .abc file has multiple segments within that play linearly.  Currently, each segment length is determined total length (in frames)/number of sequences. i.e. if you create a sequence make sure each segment is the same length.</dd>
</dl>

Triggering can be both Note-on or Note-off.  i.e. A 20 frame animation sequence can animate in on note-on (frames:1-10) and stop.  When the note off message is recieved the .abc file will continue to play out-animation (frames: 10-20)

<dl>
<dt>Note On</dt>
<dd>Only react to Note-On messages.</dd>
<dt>Note Off</dt>
<dd>Play the segment in halves. Play frames 1-10, stop.  On note-off play 11-20, then rewind and stop.</dd>
</dl>

Development TO-DO
-------------------
- [ ] Bug - Unused tracks should have params set to NULL so not to intefere with track calculations.
- [ ] Bug - When switching between shaders and materials the each preset is not stored correctly in the xml.
- [ ] Bug - .abc asset validity check so app doesn't crash when trying to load missing file or invalid abc file. 
- [ ] Bug - Random select in total tracks.  e.g. lots of empty tracks messes up random selection.
- [ ] Bug - Random play is not working. Review algorithm.
- [ ] Bug - Lights refinement. Set default positions.  Point light positioning controls.
- [ ] Bug - Work out world space with blend shapes.  I use an older version of ofAlembic for this project. The newer version messes with the world space coordinates of my blend shape geometry.
- [ ] Enhancement - load/save scene xml via dialog. Store scene xml files
- [ ] Enhancement - Toggle preview for all tracks on and off
- [ ] Enhancement - scrollable track loaders
- [ ] Enhancement - FFT Audio input.
- [ ] Enhancement - Set X,Y,Z world space position per track.
- [ ] Enhancement - Load shaders.
- [ ] Enhancement - preset midi notes from 36-06 bottom to top.
- [ ] Enhancement - load cameras individually by value by passing OSC value or Midi Value
- [ ] Enhancement - Debug incoming messages screen.

Development COMPLETE
------------------
- [x] .abc World-Space translation controls using ofNode().
- [x] Added OSC. 
- [x] Adjust midi in input selector.  Put in a switch for 1. IAC or 2. Network Midi...etc.
- [x] Control camera with OSC.
- [x] Make loader speed mod a ofxUISlider, (un-hooked up)
- [x] Create a Track GUI to tie Materials to midi channels so each can have a different material. 

Future Dev (suspended for now)
------------------
- [ ] VBOMesh expirments. Preload .abc content to <vbomesh> vectors to increase performance and do instancing.
- [ ] Average normals script to calcute normals on meshes that have none.
- [ ] Defered Rendering (Ambient Occulsion, Blur, Depth, etc.)
- [ ] Load a directory of shaders.
- [ ] Maya scripts/Gui to consruct geometry and export Alembic at the same time.
- [ ] Turn this whole thing into a FFGL plugin for Resolume.

Maya Alembic Files
-----------------

I use Maya 2014 to export my alembic files.  After considerable trial and error here are some tips:

1. SetNormalAngle to 90. If that's to much, your geometry looks wrong(e.g. pixelated per face), reduce to 60 or lower. Do not bo below 20 unless you're looking for the faceted look.

2. when modifying a shape in Maya abc files need constant tesselation.  for lofts and extrudes I use general tesselation so my polycount remains constant. 

3. Always check the direction of your normals this matters in this app. 

4. More to come with pictures(don't know where else to put this info :)
