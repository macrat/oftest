#ifndef __ITEM_H__
#define __ITEM_H__

#include <memory>

#include <ofMain.h>
#include <ofxBox2d.h>


class Item {
protected:
	const ofColor color;

public:
	Item(ofxBox2d& box2d, const int x, const int y, const float r) : color(ofRandom(50, 150), 0, ofRandom(200, 255)) { }

	virtual void draw() = 0;
	virtual bool shouldRemove() = 0; 


	static std::shared_ptr<Item> generate(ofxBox2d& box2d, const int x, const int y, const float size);
};


class CircleItem : public Item, public ofxBox2dCircle {
public:
	CircleItem(ofxBox2d& box2d, const int x, const int y, const float r) : Item(box2d, x, y, r) {
		setPhysics(pow(r, 2.0), 0.6, 0.1);
		setup(box2d.getWorld(), x, y, r);
	}

	void draw() override {
		ofSetColor(color);
		ofDrawCircle(getPosition(), getRadius());
	}

	bool shouldRemove() override {
		const auto pos = getPosition();
		const float r = getRadius();
		return pos.x < -r || ofGetWidth() + r < pos.x || ofGetHeight() + r < pos.y;
	}
};


class BoxItem : public Item, public ofxBox2dRect {
public:
	BoxItem(ofxBox2d& box2d, const int x, const int y, const float size) : Item(box2d, x, y, size) {
		setPhysics(pow(size, 2.0), 0.6, 0.1);
		setup(box2d.getWorld(), x, y, size, size);
	}

	void draw() override {
		ofSetColor(color);
		ofDrawRectangle(getPosition() - ofVec3f(getWidth()/2, getHeight()/2), getWidth(), getHeight());
	}

	bool shouldRemove() override {
		const auto pos = getPosition();
		const float r = getWidth() * getHeight();
		return pos.x < -r || ofGetWidth() + r < pos.x || ofGetHeight() + r < pos.y;
	}
};


#endif
