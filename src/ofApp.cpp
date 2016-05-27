#include "ofApp.h"


void ofApp::setup(){
	box2d.init();
	box2d.setGravity(0, 9.8);
	box2d.createGround();
	box2d.setFPS(60.0);
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
}


void ofApp::draw(){
	ofBackgroundGradient(ofColor::white, ofColor(240, 230, 255));

	for(auto x: items){
		x->draw();
	}
}


void ofApp::keyPressed(const int key){
	if(key == ' '){
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
