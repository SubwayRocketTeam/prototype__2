#include "Unit.h"
#include "AppMacros.h"

using namespace std;
using namespace cocos2d;

Unit::Unit() :
	body(nullptr){
}
Unit::~Unit(){
}

Unit *Unit::create(){
	Unit *u = new Unit();

	if(u && u->init()){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}
Unit *Unit::create(
	const string &image){

	Unit *u = new Unit();

	if(u && u->init(image)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

bool Unit::init(){
    if (!Sprite::init())
        return false;

    return true;
}
bool Unit::init(
	const string &image){

	if(!Sprite::init())
        return false;

	body = Sprite::create(image);
	if(body == nullptr)
		return false;

	if(!initPhysics())
		return false;

	addChild(body);

	return true;
}

bool Unit::initPhysics(){
	cocos2d::log("initPhysics : override me");

	return true;
}