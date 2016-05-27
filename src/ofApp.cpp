#include "ofApp.h"


void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	cam.setup(800, 600);

	box2d.init();
	box2d.setGravity(0, 9.8);
	box2d.createGround();
	box2d.setFPS(60.0);

	makeColor(bgColor);

	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ofxCv::ObjectFinder::Fast);
}


void ofApp::update(){
	if(pressed){
		items.push_back(Item::generate(
			box2d,
			mouseX, mouseY,
			ofRandom(4, 20)
		));
	}

	for(auto itr=items.begin(); itr!=items.end();){
		if((*itr)->shouldRemove()){
			itr = items.erase(itr);
		}else{
			++itr;
		}
	}

	box2d.update();

	cam.update();
	if(cam.isFrameNew()){
		ofxCv::convertColor(cam, img, CV_RGB2GRAY);
		ofxCv::threshold(img, 60);
		img.mirror(false, true);
		img.update();

		finder.update(cam);
	}

	for(int i=0; i<finder.size(); i++){
		const ofRectangle rect(finder.getObjectSmoothed(i));
		ofPoint pos(rect.getCenter());
		pos.x = ofGetWidth() - pos.x * ofGetWidth() / cam.getWidth();
		pos.y *= ofGetHeight() / cam.getHeight();
		const float r = min(rect.getWidth() * ofGetWidth() / cam.getWidth(), rect.getHeight() * ofGetHeight() / cam.getHeight());

		for(int i=0; i<max(1, (int)r/100); i++){
			const float a = ofRandom(2*PI);
			const float l = ofRandom(r/2);
			items.push_back(Item::generate(box2d, pos + ofPoint(cos(a)*l, sin(a)*l), ofRandom(4, 10)));
		}
	}
}


void ofApp::draw(){
	ofSetColor(bgColor);
	img.draw(0, 0, ofGetWidth(), ofGetHeight());

	for(auto x: items){
		x->draw();
	}
}


void ofApp::keyPressed(const int key){
	if(key == ' '){
		makeColor(bgColor);
		items.clear();
	}else if(key == 'z'){
		items.push_back(Item::generate(
			box2d,
			mouseX, mouseY,
			ofRandom(50, 60)
		));
	}
}


void ofApp::mousePressed(const int x, const int y, const int button){
	pressed = true;
}


void ofApp::mouseReleased(const int x, const int y, const int button){
	pressed = false;
}


void ofApp::windowResized(const int w, const int h){
	box2d.createGround();
}
