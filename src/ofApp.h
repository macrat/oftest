#ifndef __OF_APP_H__
#define __OF_APP_H__

#include <vector>
#include <memory>

#include <ofMain.h>
#include <ofxBox2d.h>

#include "item.h"


class ofApp : public ofBaseApp{
	private:
		ofxBox2d box2d;
		std::vector< std::shared_ptr<Item> > items;
		bool pressed;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
};


#endif
