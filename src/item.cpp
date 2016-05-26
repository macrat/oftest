#include "item.h"


std::shared_ptr<Item> Item::generate(ofxBox2d& box2d, const int x, const int y, const float size){
	if(((int)ofRandom(2)) == 0){
		return std::shared_ptr<Item>((Item*)new CircleItem(box2d, x, y, size));
	}else{
		return std::shared_ptr<Item>((Item*)new BoxItem(box2d, x, y, size*2));
	}
}
