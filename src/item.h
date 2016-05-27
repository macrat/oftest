#ifndef __ITEM_H__
#define __ITEM_H__

#include <memory>

#include <ofMain.h>
#include <ofxBox2d.h>


class Item : public ofxBox2dBaseShape {
protected:
	const ofColor color;
	const float removeRadius;

public:
	Item(const float removeRadius) : color(ofRandom(50, 150), 0, ofRandom(200, 255)), removeRadius(removeRadius) { }

	virtual ~Item() { }

	virtual void draw() = 0;

	virtual bool shouldRemove() {
		const auto pos = getPosition();
		return pos.x < -removeRadius || ofGetWidth() + removeRadius < pos.x || ofGetHeight() + removeRadius < pos.y;
	}


	static std::shared_ptr<Item> generate(ofxBox2d& box2d, const int x, const int y, const float size);
	static std::shared_ptr<Item> generate(ofxBox2d& box2d, const ofPoint pos, const float size) {
		return Item::generate(box2d, pos.x, pos.y, size);
	}
};


class CircleItem : public Item, public ofxBox2dCircle {
public:
	CircleItem(ofxBox2d& box2d, const int x, const int y, const float r) : Item(r) {
		ofxBox2dCircle::setPhysics(pow(r, 2.0), 0.6, 0.1);
		ofxBox2dCircle::setup(box2d.getWorld(), x, y, r);
	}

	void draw() override {
		ofSetColor(color);
		ofDrawCircle(ofxBox2dCircle::getPosition(), ofxBox2dCircle::getRadius());
	}
};


class BoxItem : public Item, public ofxBox2dRect {
public:
	BoxItem(ofxBox2d& box2d, const int x, const int y, const float size) : Item(pow(size, 2.0)) {
		ofxBox2dRect::setPhysics(pow(size, 2.0), 0.6, 0.1);
		ofxBox2dRect::setup(box2d.getWorld(), x, y, size, size);
	}

	void draw() override {
		ofxBox2dRect::draw();
	}
};


#endif
