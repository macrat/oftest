#ifndef __OF_APP_H__
#define __OF_APP_H__

#include <vector>
#include <memory>

#include <ofMain.h>
#include <ofxBox2d.h>
#include <ofxCv.h>

#include "item.h"


class ofApp : public ofBaseApp{
	private:
		ofxBox2d box2d;
		std::vector< std::shared_ptr<Item> > items;
		bool pressed;

		ofColor bgColor;

		ofVideoGrabber cam;
		ofImage img;
		ofxCv::ObjectFinder finder;

		static void makeColor(ofColor& c) {
			c.set(ofRandom(100, 200), 100, ofRandom(220, 255));
		}

	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(const int key) override;
		void mousePressed(const int x, const int y, const int button) override;
		void mouseReleased(const int x, const int y, const int button) override;
		void windowResized(const int w, const int h) override;
};


#endif
